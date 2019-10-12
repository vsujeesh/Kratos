from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the base class
from KratosMultiphysics.CoSimulationApplication.base_classes.co_simulation_io import CoSimulationIO

# CoSimulation imports
import KratosMultiphysics.CoSimulationApplication as KratosCoSim
import KratosMultiphysics.CoSimulationApplication.co_simulation_tools as cs_tools

# Other imports
import os

def Create(model, settings, solver_name):
    return DummySolverIO(model, settings, solver_name)

class DummySolverIO(CoSimulationIO):
    """This class is used if a Solver directly uses Kratos as a data-structure
    e.g. Kratos itself or simple-solvers written in Python
    """
    def __init__(self, settings, model, solver_name):
        super(DummySolverIO, self).__init__(settings, model, solver_name)

        self.io = KratosCoSim.CoSimIO(solver_name, ParametersToStringDict(self.settings))

        self.io.Connect()

    def Finalize(self):
        self.io.Disconnect()

    def ImportCouplingInterface(self, interface_config):
        self.io.ImportMesh(self.model[interface_config["model_part_name"]]) # TODO this can also be geometry at some point

    # def ImportData(self, data_config):
    #     data_type = data_config["type"]
    #     if data_type == "coupling_interface_data":
    #         interface_data = data_config["interface_data"]
    #         KratosCoSim.EMPIRE_API.EMPIRE_API_recvDataField(interface_data.GetModelPart(), self.solver_name+"_"+interface_data.name, interface_data.variable)
    #     else:
    #         raise NotImplementedError('Importing interface data of type "{}" is not implemented for this IO: "{}"'.format(data_type, self._ClassName()))

    def ExportData(self, data_config):
        data_type = data_config["type"]
        if data_type == "coupling_interface_data":
            self.io.ExportData(data_config["interface_data"].GetModelPart())
        elif data_type == "control_signal":
            control_signal_key = cs_tools.control_signal_map[data_config["signal"]]
            self.io.SendControlSignal(control_signal_key,"ddd")
        else:
            raise NotImplementedError('Exporting interface data of type "{}" is not implemented for this IO: "{}"'.format(data_type, self._ClassName()))

    def PrintInfo(self):
        print("This is the EMPIRE-IO")

    def Check(self):
        pass


def ParametersToStringDict(param):
    string_dict = {}

    for k,v in param.items():
        if v.IsInt():
            v = v.GetInt()
        elif v.IsBool():
            v = int(v.GetBool())
        elif v.IsDouble():
            v = v.GetDouble()
        elif v.IsString():
            v = v.GetString()
        else:
            raise Exception("Only int, double, bool and string are allowed!")

        string_dict[k] = str(v)

    return string_dict
