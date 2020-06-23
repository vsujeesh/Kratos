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

#if !defined(KRATOS_RANS_APPLICATION_VARIABLES_H_INCLUDED)
#define KRATOS_RANS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes

// Project includes
#include "containers/variable.h"
#include "includes/define.h"

namespace Kratos
{
    // residual based flux corrected stabilization variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, RANS_STABILIZATION_DISCRETE_UPWIND_OPERATOR_COEFFICIENT )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, RANS_STABILIZATION_DIAGONAL_POSITIVITY_PRESERVING_COEFFICIENT )

    // k-epsilon-high-re turbulence modelling variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_KINETIC_ENERGY )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_ENERGY_DISSIPATION_RATE )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_KINETIC_ENERGY_RATE )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_ENERGY_DISSIPATION_RATE_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, RANS_AUXILIARY_VARIABLE_1 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, RANS_AUXILIARY_VARIABLE_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_C_MU )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_KINETIC_ENERGY_SIGMA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_C1 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_C2 )

    // k-omega turbulence modelling specific additional variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_BETA )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_GAMMA )

    // k-omega-sst turbulence modelling specific additional variables
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_KINETIC_ENERGY_SIGMA_1 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_KINETIC_ENERGY_SIGMA_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA_1 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENT_SPECIFIC_ENERGY_DISSIPATION_RATE_SIGMA_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_BETA_1 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, TURBULENCE_RANS_BETA_2 )
    KRATOS_DEFINE_APPLICATION_VARIABLE( RANS_APPLICATION, double, WALL_VON_KARMAN )

} // namespace Kratos

#endif /* KRATOS_RANS_APPLICATION_VARIABLES_H_INCLUDED */
