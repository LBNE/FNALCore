// ======================================================================
//
// test "random" header's distributions
//
// ======================================================================

#define BOOST_TEST_MODULE ( "random test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/random"
#include <iostream>
#include <sstream>

using namespace std;

template< class Distribution >
void
  test_equality( )
{
  { Distribution d1, d2;      BOOST_CHECK_EQUAL( d1, d2 );
  }
  { Distribution c1, c2(c1);  BOOST_CHECK_EQUAL( c1, c2 );
  }
  { Distribution i1, i2;      BOOST_CHECK_EQUAL( i1, i2 );
    ostringstream os;
    os << i1;
    istringstream is(os.str());
    is >> i2;                 BOOST_CHECK_EQUAL( i1, i2 );
  }
}

BOOST_AUTO_TEST_SUITE( random_test )

#if defined CPP0X_HAS_RANDOM_HDR

  BOOST_AUTO_TEST_CASE( no_need_to_test )
  {
    BOOST_CHECK( true );
  }

#else

  BOOST_AUTO_TEST_CASE( uniform_int_distribution_test )
  {
    test_equality< uniform_int_distribution<int     > >();
    test_equality< uniform_int_distribution<long    > >();
    test_equality< uniform_int_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( uniform_real_distribution_test )
  {
    test_equality< uniform_real_distribution<double> >();
    test_equality< uniform_real_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( bernoulli_distribution_test )
  {
    test_equality< bernoulli_distribution >();
  }

  BOOST_AUTO_TEST_CASE( binomial_distribution_test )
  {
    test_equality< binomial_distribution<int     > >();
    test_equality< binomial_distribution<long    > >();
    test_equality< binomial_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( geometric_distribution_test )
  {
    test_equality< geometric_distribution<int     > >();
    test_equality< geometric_distribution<long    > >();
    test_equality< geometric_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( negative_binomial_distribution_test )
  {
    test_equality< negative_binomial_distribution<int     > >();
    test_equality< negative_binomial_distribution<long    > >();
    test_equality< negative_binomial_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( poisson_distribution_test )
  {
    test_equality< poisson_distribution<int     > >();
    test_equality< poisson_distribution<long    > >();
    test_equality< poisson_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( exponential_distribution_test )
  {
    test_equality< exponential_distribution<double> >();
    test_equality< exponential_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( gamma_distribution_test )
  {
    test_equality< gamma_distribution<double> >();
    test_equality< gamma_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( weibull_distribution_test )
  {
    test_equality< weibull_distribution<double> >();
    test_equality< weibull_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( extreme_value_distribution_test )
  {
    test_equality< extreme_value_distribution<double> >();
    test_equality< extreme_value_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( normal_distribution_test )
  {
    test_equality< normal_distribution<double> >();
    test_equality< normal_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( lognormal_distribution_test )
  {
    test_equality< lognormal_distribution<double> >();
    test_equality< lognormal_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( chi_squared_distribution_test )
  {
    test_equality< chi_squared_distribution<double> >();
    test_equality< chi_squared_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( cauchy_distribution_test )
  {
    test_equality< cauchy_distribution<double> >();
    test_equality< cauchy_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( fisher_f_distribution_test )
  {
    test_equality< fisher_f_distribution<double> >();
    test_equality< fisher_f_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( student_t_distribution_test )
  {
    test_equality< student_t_distribution<double> >();
    test_equality< student_t_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( discrete_distribution_test )
  {
    test_equality< discrete_distribution<int     > >();
    test_equality< discrete_distribution<long    > >();
    test_equality< discrete_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( piecewise_constant_distribution_test )
  {
    test_equality< piecewise_constant_distribution<double> >();
    test_equality< piecewise_constant_distribution<float > >();
  }

#endif  // CPP0X_HAS_RANDOM_HDR

BOOST_AUTO_TEST_SUITE_END()
