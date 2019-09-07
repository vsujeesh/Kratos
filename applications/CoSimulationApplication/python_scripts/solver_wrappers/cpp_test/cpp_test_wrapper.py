from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import subprocess
import sys

# Importing the Kratos Library
import KratosMultiphysics as KM

# Importing the base class
from KratosMultiphysics.CoSimulationApplication.base_classes.co_simulation_solver_wrapper import CoSimulationSolverWrapper

# Other imports
import KratosMultiphysics.CoSimulationApplication.co_simulation_tools as cs_tools

def Create(settings, solver_name):
    return TestCppWrapper(settings, solver_name)

class TestCppWrapper(CoSimulationSolverWrapper):
    """This class serves as wrapper for the cpp test solvers
    """
    def __init__(self, settings, solver_name):
        super(TestCppWrapper, self).__init__(settings, solver_name)

        settings_defaults = KM.Parameters("""{
            "main_model_part_name" : "",
            "domain_size" : 2,                    
            "executable_name"  : ""
        }""")

        self.settings["solver_wrapper_settings"].ValidateAndAssignDefaults(settings_defaults)
        model_part_name = self.settings["solver_wrapper_settings"]["main_model_part_name"].GetString()
        cs_tools.CreateMainModelPartsFromCouplingData(self.data_dict.values(), self.model, self.name)
        cs_tools.AllocateHistoricalVariablesFromCouplingData(self.data_dict.values(), self.model, self.name)        
        self.mp = self.model[model_part_name]
        self.mp.CreateNewNode(1,0,0,0)

    def Initialize(self):
        super(TestCppWrapper, self).Initialize()

    def Finalize(self):
        super(TestCppWrapper, self).Finalize()
        with self.rv.stdout, open(self.name +'.log', 'w') as file:
            for line in self.rv.stdout:
                #print("Finalze :: ",self.name)
                #print (line)
                file.write(line.decode("utf-8"))

    def AdvanceInTime(self, current_time):
        return 1.0

    def SolveSolutionStep(self):
        super(TestCppWrapper, self).SolveSolutionStep()
        self.__RunExecutable()      

    def PrintInfo(self):
        cs_tools.cs_print_info(self._ClassName(), "printing info...")
        ## TODO print additional stuff with higher echo-level

    def _GetIOType(self):
        return self.settings["io_settings"]["type"].GetString()

    def __RunExecutable(self):
        command_txt = self.settings["solver_wrapper_settings"]["executable_name"].GetString()
        print("Running : ", command_txt)
        self.rv = subprocess.Popen(command_txt, stdout = subprocess.PIPE, stderr = subprocess.PIPE, shell=True, start_new_session=True)     
        #subprocess.Popen(command_txt)     