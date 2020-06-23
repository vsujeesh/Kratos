//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

#include "rans_application_variables.h"

namespace Kratos
{
    // residual based flux corrected stabilization variables
    KRATOS_CREATE_VARIABLE( double, RANS_STABILIZATION_DISCRETE_UPWIND_OPERATOR_COEFFICIENT )
    KRATOS_CREATE_VARIABLE( double, RANS_STABILIZATION_DIAGONAL_POSITIVITY_PRESERVING_COEFFICIENT )

    // k-epsilon-high-re turbulence modelling variables
    KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_RATE )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE_2 )
    KRATOS_CREATE_VARIABLE( double, RANS_AUXILIARY_VARIABLE_1 )
    KRATOS_CREATE_VARIABLE( double, RANS_AUXILIARY_VARIABLE_2 )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_SIGMA )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C_MU )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C1 )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C2 )

    // k-omega turbulence modelling specific additional variables
    KRATOS_CREATE_VARIABLE( double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_2 )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_BETA )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_GAMMA )

    // k-omega-sst turbulence modelling specific additional variables
    KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_SIGMA_1 )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_SIGMA_2 )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA_1 )
    KRATOS_CREATE_VARIABLE( double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA_2 )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_BETA_1 )
    KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_BETA_2 )
    KRATOS_CREATE_VARIABLE( double, WALL_VON_KARMAN )
}