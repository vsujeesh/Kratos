from __future__ import absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics
import KratosMultiphysics.FluidDynamicsApplication as KratosFluid

import KratosMultiphysics.python_linear_solver_factory as python_linear_solver_factory

if KratosMultiphysics.DataCommunicator.GetDefault().IsDistributed():
    import KratosMultiphysics.TrilinosApplication as KratosTrilinos
    import KratosMultiphysics.TrilinosApplication.trilinos_linear_solver_factory as trilinos_linear_solver_factory

def Factory(settings, Model):
    if( not isinstance(settings, KratosMultiphysics.Parameters) ):
        raise Exception("expected input shall be a Parameters object, encapsulating a json string")
    return ApplyMassConservationCheckProcess( Model, settings["Parameters"] )

class ApplyMassConservationCheckProcess(KratosMultiphysics.Process):

    def __init__(self, Model, settings):

        KratosMultiphysics.Process.__init__(self)

        default_parameters = KratosMultiphysics.Parameters( """
        {
            "model_part_name"                    : "",
            "mass_correction_setttings"          : {},
            "perform_local_corrections"          : true,
            "perform_global_corrections"         : false,
            "write_to_log_file"                  : false,
            "log_file_name"                      : "mass_conservation.log",
            "convector_settings"                 : {},
            "correction_frequency_in_time_steps" : 1,
            "check_volume_loss_at_the_end"       : false
        }""" )

        settings.ValidateAndAssignDefaults(default_parameters)
        convector_settings = KratosMultiphysics.Parameters( """{
            "linear_solver_settings": {
                "solver_type": "amgcl"
            },
            "max_cfl" : 1.0,
            "cross_wind_stabilization_factor" : 0.7,
            "max_substeps" : 0
        }""")
        settings["convector_settings"].ValidateAndAssignDefaults(convector_settings)
        self.settings = settings

        if ( self.settings["model_part_name"].GetString() == "" ):
            KratosMultiphysics.Logger.PrintInfo("ApplyMassConservationCheckProcess","The value (string) of the parameter 'model_part_name' must not be empty.")

        self._fluid_model_part = Model[self.settings["model_part_name"].GetString()]
        self._write_to_log = self.settings["write_to_log_file"].GetBool()
        self._my_log_file = self.settings["log_file_name"].GetString()
        self._correct_frequency = self.settings["correction_frequency_in_time_steps"].GetInt()
        self._check_volume_loss_at_the_end = self.settings["check_volume_loss_at_the_end"].GetBool()

        self._perform_local_corr  = self.settings["perform_local_corrections"].GetBool()
        self._perform_global_corr = self.settings["perform_global_corrections"].GetBool()

        self.mass_conservation_utility = KratosFluid.MassConservationUtility(self._fluid_model_part, self.settings["mass_correction_setttings"])

        KratosMultiphysics.Logger.PrintInfo("ApplyMassConservationCheckProcess","Construction finished.")


    def ExecuteInitialize(self):
        self.forward_convection_process = self._set_levelset_convection_process()

        # calling C++ initalization
        first_lines_string = self.mass_conservation_utility.Initialize()

        # writing first line in file
        if self._write_to_log:
            with open(self._my_log_file, "w") as logFile:
                logFile.write( first_lines_string )

        KratosMultiphysics.Logger.PrintInfo("ApplyMassConservationCheckProcess","Initialization finished (initial volumes calculated).")

    def Execute(self):
        self.ExecuteFinalizeSolutionStep()

    def ExecuteFinalizeSolutionStep(self):
        ### always necessary to keep track of the balanced volume
        log_line_string = self.mass_conservation_utility.ComputeBalancedVolume()

        ### writing first line in file
        if self._fluid_model_part.ProcessInfo[KratosMultiphysics.STEP] % self._correct_frequency == 0:
            if self._write_to_log:
                with open(self._my_log_file, "a+") as logFile:
                    logFile.write( log_line_string )

            # (1) #
            if self._perform_local_corr:
                ### perform the local conservation procedure
                # REMARK: The pseudo time step dt has no meaning as a physical time step and is NOT accounted as such.
                # Instead, it as purely used for an artificial convection that helps to conserve the mass.
                # Accordingly, dt depends on the currently necessary mass convection.
                dt = self.mass_conservation_utility.ComputeDtForConvection()

                # REMARK: The distance field is artificially convected to extrapolate the interface motion into the future.
                # The time step considered for this artificial "forward convection" is dt.
                # The previous distance field is saved in an auxiliary variable
                prev_dt = self._fluid_model_part.ProcessInfo[KratosMultiphysics.DELTA_TIME]
                self._fluid_model_part.ProcessInfo[KratosMultiphysics.DELTA_TIME] = dt
                KratosMultiphysics.VariableUtils().SaveScalarVar(
                    KratosMultiphysics.DISTANCE,
                    KratosFluid.AUX_DISTANCE,
                    self._fluid_model_part.GetCommunicator().LocalMesh().Nodes)
                self.forward_convection_process.Execute()
                self._fluid_model_part.ProcessInfo[KratosMultiphysics.DELTA_TIME] = prev_dt

                # REMARK: A comparison between the "forward_convected" distance field and the current distance field is made.
                # Depending on the current mass balance, one of the following options i chosen:
                # - taking min() of both fields = adding to fluid_1 ("more water")
                # - taking max() of both fields = adding to fluid_2 ("more air")
                self.mass_conservation_utility.ApplyLocalCorrection( KratosFluid.AUX_DISTANCE )

            # (2) #
            if self._perform_local_corr and self._perform_global_corr:
                ### check how much work has already been done by the local correction process
                self.mass_conservation_utility.ReCheckTheMassConservation()

            # (3) #
            if self._perform_global_corr:
                ### perform the global correction
                # without any consideration of the velocity field, volume is added by a global slight shift of the distance field
                self.mass_conservation_utility.ApplyGlobalCorrection()

            # (4) #
            if self._check_volume_loss_at_the_end:
                self.mass_conservation_utility.ReCheckTheMassConservation()


    def _set_levelset_convection_process(self):
        if self._fluid_model_part.IsDistributed():
            self.EpetraCommunicator = KratosTrilinos.CreateCommunicator()
            self.trilinos_linear_solver = trilinos_linear_solver_factory.ConstructSolver(self.settings["convector_settings"]["linear_solver_settings"])

            if self._fluid_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE] == 2:
                level_set_convection_process = KratosTrilinos.TrilinosLevelSetConvectionProcess2D(
                    self.EpetraCommunicator,
                    KratosMultiphysics.DISTANCE,
                    self._fluid_model_part,
                    self.trilinos_linear_solver,
                    self.settings["convector_settings"]["max_cfl"].GetDouble(),
                    self.settings["convector_settings"]["cross_wind_stabilization_factor"].GetDouble(),
                    self.settings["convector_settings"]["max_substeps"].GetInt())
            else:
                level_set_convection_process = KratosTrilinos.TrilinosLevelSetConvectionProcess3D(
                    self.EpetraCommunicator,
                    KratosMultiphysics.DISTANCE,
                    self._fluid_model_part,
                    self.trilinos_linear_solver,
                    self.settings["convector_settings"]["max_cfl"].GetDouble(),
                    self.settings["convector_settings"]["cross_wind_stabilization_factor"].GetDouble(),
                    self.settings["convector_settings"]["max_substeps"].GetInt())
        else:
            self.linear_solver = python_linear_solver_factory.ConstructSolver(self.settings["convector_settings"]["linear_solver_settings"])

            if self._fluid_model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE] == 2:
                level_set_convection_process = KratosMultiphysics.LevelSetConvectionProcess2D(
                    KratosMultiphysics.DISTANCE,
                    self._fluid_model_part,
                    self.linear_solver,
                    self.settings["convector_settings"]["max_cfl"].GetDouble(),
                    self.settings["convector_settings"]["cross_wind_stabilization_factor"].GetDouble(),
                    self.settings["convector_settings"]["max_substeps"].GetInt())
            else:
                level_set_convection_process = KratosMultiphysics.LevelSetConvectionProcess3D(
                    KratosMultiphysics.DISTANCE,
                    self._fluid_model_part,
                    self.linear_solver,
                    self.settings["convector_settings"]["max_cfl"].GetDouble(),
                    self.settings["convector_settings"]["cross_wind_stabilization_factor"].GetDouble(),
                    self.settings["convector_settings"]["max_substeps"].GetInt())

        return level_set_convection_process