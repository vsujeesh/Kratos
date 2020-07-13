//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Ilaria Iaconeta, Bodhinanda Chandra
//
//

// System includes

#if defined(KRATOS_PYTHON)
// External includes

// Project includes
#include "includes/define.h"
#include "includes/define_python.h"

#include "custom_python/add_custom_strategies_to_python.h"
#include "custom_python/add_custom_utilities_to_python.h"
#include "custom_python/add_custom_constitutive_laws_to_python.h"
#include "custom_python/add_custom_processes_to_python.h"

#include "particle_mechanics_application.h"

namespace Kratos{
namespace Python{

    namespace py = pybind11;

    PYBIND11_MODULE(KratosParticleMechanicsApplication, m)
    {
        py::class_<KratosParticleMechanicsApplication,
            KratosParticleMechanicsApplication::Pointer,
            KratosApplication >(m, "KratosParticleMechanicsApplication")
            .def(py::init<>())
            ;

        AddCustomStrategiesToPython(m);
        AddCustomUtilitiesToPython(m);
        AddCustomConstitutiveLawsToPython(m);
        AddCustomProcessesToPython(m);

        // Registering variables in python
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MP_COORD);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_MASS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_DENSITY);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_VOLUME);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_POTENTIAL_ENERGY);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_KINETIC_ENERGY);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_STRAIN_ENERGY);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_TOTAL_ENERGY);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_PRESSURE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_EQUIVALENT_STRESS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_DELTA_PLASTIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_DELTA_PLASTIC_VOLUMETRIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_DELTA_PLASTIC_DEVIATORIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_EQUIVALENT_PLASTIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_EQUIVALENT_PLASTIC_STRAIN_RATE );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_ACCUMULATED_PLASTIC_VOLUMETRIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_ACCUMULATED_PLASTIC_DEVIATORIC_STRAIN );
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_TEMPERATURE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_DAMAGE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_COMPACTION_RATIO);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_HARDENING_RATIO);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_MATERIAL_ID);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, PARTICLES_PER_ELEMENT);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_SUB_POINTS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IGNORE_GEOMETRIC_STIFFNESS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_AXISYMMETRIC);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_COMPRESSIBLE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_PQMPM);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_MAKE_NORMAL_MP_IF_PQMPM_FAILS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, PQMPM_SUBPOINT_MIN_VOLUME_FRACTION);

        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_COORD);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MPC_CONDITION_ID);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MPC_IS_NEUMANN);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MPC_AREA);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_NORMAL);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_DISPLACEMENT);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_IMPOSED_DISPLACEMENT);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_VELOCITY);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_IMPOSED_VELOCITY);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_ACCELERATION);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_IMPOSED_ACCELERATION);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MPC_CONTACT_FORCE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, PARTICLES_PER_CONDITION);

        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MP_DISPLACEMENT);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MP_VELOCITY);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MP_ACCELERATION);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, MP_VOLUME_ACCELERATION);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, NODAL_INTERNAL_FORCE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_CAUCHY_STRESS_VECTOR);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, MP_ALMANSI_STRAIN_VECTOR);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, NODAL_MOMENTUM);
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, NODAL_INERTIA);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, NODAL_MPRESSURE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, PRESSURE_REACTION);

        // Essential Boundary variables
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, PENALTY_FACTOR);

        // Nodal load variables
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, POINT_LOAD )
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, LINE_LOAD )
        KRATOS_REGISTER_IN_PYTHON_3D_VARIABLE_WITH_COMPONENTS(m, SURFACE_LOAD )

        // Explicit time integration variables
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, CALCULATE_MUSL_VELOCITY_FIELD);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_EXPLICIT);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_EXPLICIT_CENTRAL_DIFFERENCE);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, EXPLICIT_STRESS_UPDATE_OPTION);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, CALCULATE_EXPLICIT_MP_STRESS);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, EXPLICIT_MAP_GRID_TO_MP);
        KRATOS_REGISTER_IN_PYTHON_VARIABLE(m, IS_FIX_EXPLICIT_MP_ON_GRID_EDGE);
    }

}  // namespace Python.
}  // namespace Kratos.

#endif // KRATOS_PYTHON defined
