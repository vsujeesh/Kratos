//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Vicente Mataix Ferrandiz
//

// System includes
#include <limits>

// External includes

// Project includes
#include "testing/testing.h"
#include "containers/model.h"

// Utility includes
#include "includes/define.h"
#include "includes/model_part.h"
#include "factories/register_factories.h"
#include "spaces/ublas_space.h"

namespace Kratos
{
    namespace Testing
    {
        /// Tests

        // Spaces
        using SparseSpaceType = UblasSpace<double, CompressedMatrix, Vector>;
        using LocalSpaceType = UblasSpace<double, Matrix, Vector>;

        /// The definition of the strategy
        using ExplicitSolvingStrategyType = ExplicitSolvingStrategy<SparseSpaceType,LocalSpaceType>;

        /// The definition of the factory
        using ExplicitStrategyFactoryType = Factory<ExplicitSolvingStrategyType>;

        /**
         * Checks if the ExplicitSolvingStrategyRungeKutta4 performs correctly the Factory
         */
        KRATOS_TEST_CASE_IN_SUITE(ExplicitSolvingStrategyRungeKutta4Factory, KratosCoreFastSuite)
        {
            Model this_model;
            auto& r_model_part = this_model.CreateModelPart("Main");
            Parameters this_parameters = Parameters(R"({"name" : "explicit_solving_strategy_runge_kutta_4",
                                                        "explicit_builder_settings" : {
                                                            "name" : "explicit_builder"
                                                        }
                                                        })");
            ExplicitSolvingStrategyType::Pointer p_strategy = ExplicitStrategyFactoryType().Create(r_model_part, this_parameters);
            KRATOS_CHECK_STRING_EQUAL(p_strategy->Info(), "ExplicitSolvingStrategyRungeKutta4");
        }
    } // namespace Testing
}  // namespace Kratos.

