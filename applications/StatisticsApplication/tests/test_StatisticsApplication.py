# import Kratos
import KratosMultiphysics
import KratosMultiphysics.StatisticsApplication

# Import Kratos "wrapper" for unittests
import KratosMultiphysics.KratosUnittest as KratosUnittest

# Import the tests o test_classes to create the suits
from test_norms import NormTests
from test_spatial_methods import SpatialMethodTests
from test_temporal_sum_method import TemporalSumMethodTests
from test_temporal_mean_method import TemporalMeanMethodTests
from test_temporal_variance_method import TemporalVarianceMethodTests
from test_temporal_min_method import TemporalMinMethodTests
from test_temporal_max_method import TemporalMaxMethodTests
from test_temporal_rms_method import TemporalRootMeanSquareMethodTests

def AssembleTestSuites():
    ''' Populates the test suites to run.

    Populates the test suites to run. At least, it should pupulate the suites:
    "small", "nighlty" and "all"

    Return
    ------

    suites: A dictionary of suites
        The set of suites with its test_cases added.
    '''

    suites = KratosUnittest.KratosSuites

    # Create a test suit with the selected tests (Small tests):
    # smallSuite will contain the following tests:
    # - testSmallExample
    smallSuite = suites['small']
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([NormTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([SpatialMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalSumMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalMeanMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalVarianceMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalMinMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalMaxMethodTests]))
    smallSuite.addTests(KratosUnittest.TestLoader().loadTestsFromTestCases([TemporalRootMeanSquareMethodTests]))

    nightSuite = suites['nightly']
    nightSuite.addTests(smallSuite)

    allSuite = suites['all']
    allSuite.addTests(nightSuite)

    return suites


if __name__ == '__main__':
    KratosUnittest.runTests(AssembleTestSuites())
