//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Riccardo Rossi
//

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "custom_python/add_custom_processes_to_python.h"
#include "custom_processes/kutta_condition_process.h"
#include "custom_processes/move_model_part_process.h"
#include "custom_processes/compute_embedded_lift_process.h"
#include "custom_processes/project_sensitivity_to_skin_process.cpp"


namespace Kratos {
namespace Python {

void  AddCustomProcessesToPython(pybind11::module& m)
{
	namespace py = pybind11;

    py::class_<KuttaConditionProcess, KuttaConditionProcess::Pointer, Process >
        (m, "KuttaConditionProcess")
        .def(py::init<ModelPart&>())
        ;

    py::class_<MoveModelPartProcess, MoveModelPartProcess::Pointer, Process >
        (m, "MoveModelPartProcess")
        .def(py::init<ModelPart&, Parameters>())
        ;

    py::class_<ComputeEmbeddedLiftProcess, ComputeEmbeddedLiftProcess::Pointer, Process >
        (m, "ComputeEmbeddedLiftProcess")
        .def(py::init<ModelPart&, Vector&>())
        ;

    py::class_<ProjectSensitivityToSkinProcess, ProjectSensitivityToSkinProcess::Pointer, Process >
        (m, "ProjectSensitivityToSkinProcess")
        .def(py::init<ModelPart&, ModelPart&>())
        ;

}

}
} // Namespace Kratos
