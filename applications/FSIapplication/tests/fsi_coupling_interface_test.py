import KratosMultiphysics
import KratosMultiphysics.KratosUnittest as UnitTest
import KratosMultiphysics.FSIApplication as KratosFSI
import KratosMultiphysics.StructuralMechanicsApplication as KratosStructural
import KratosMultiphysics.kratos_utilities as KratosUtilities

import os
import sys
import fsi_coupling_interface
import convergence_accelerator_factory

class FSICouplingInterfaceTest(UnitTest.TestCase):
    def test_fsi_coupling_interface(self):
        self.print_output = False
        self.check_tolerance = 1.0e-10
        self.print_reference_values = False
        self.work_folder = "FSIProblemEmulatorTest"
        self.reference_file = "reference_embedded_symbolic_navier_stokes"
        self.setUp()
        self.runTest()
        self.tearDown()
        self.checkResults()

    def setUp(self):
        # Create a complete model part to retrieve an interface from it
        self.model = KratosMultiphysics.Model()
        model_part = self.model.CreateModelPart("MainModelPart")
        model_part.ProcessInfo[KratosMultiphysics.DOMAIN_SIZE] = 2
        model_part.AddNodalSolutionStepVariable(KratosMultiphysics.DISPLACEMENT)

        # Import model part from mdpa file.
        problem_path = os.getcwd()
        input_filename = 'FSIProblemEmulatorTest/test_FSI_emulator_Structural'
        KratosMultiphysics.ModelPartIO(input_filename).ReadModelPart(model_part)

        # Create the convergence accelerator
        conv_acc_factory = KratosMultiphysics.Parameters("""
        {
            "solver_type": "constant_relaxation",
            "w": 0.5
        }""")
        self.convergence_accelerator = convergence_accelerator_factory.CreateConvergenceAccelerator(conv_acc_factory)

        # Create the FSI coupling interface
        fsi_coupling_int_settings = KratosMultiphysics.Parameters("""
        {
            "model_part_name": "FSICouplingInterfaceStructure",
            "father_model_part_name": "StructureInterface2D_Solid_interface",
            "input_variable_name": "POSITIVE_FACE_PRESSURE",
            "output_variable_name": "DISPLACEMENT"
        }""")
        self.fsi_coupling_interface = fsi_coupling_interface.FSICouplingInterface(
            self.model,
            fsi_coupling_int_settings,
            self.convergence_accelerator)

    def runTest(self):
        # Set a DISPLACEMENT to be updated in the father model part
        for node in self.fsi_coupling_interface.GetFatherModelPart().Nodes:
            node.SetSolutionStepValue(KratosMultiphysics.DISPLACEMENT, [0.01 * node.Id, 0.0, 0.0])

        # Perform the update
        residual = self.fsi_coupling_interface.Update()

    def tearDown(self):
        with UnitTest.WorkFolderScope(self.work_folder, __file__):
            KratosUtilities.DeleteFileIfExisting('FSIProblemEmulatorTest/test_FSI_emulator_Structural.time')

    def checkResults(self):
        pass

if __name__ == '__main__':
    test = FSICouplingInterfaceTest()
    test.test_fsi_coupling_interface()
