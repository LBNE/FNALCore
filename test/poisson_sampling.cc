// ======================================================================
//
// statistically test "random" header's Poisson distributions
//
// ======================================================================

#define BOOST_TEST_MODULE ( "random test" )
#include "boost/test/auto_unit_test.hpp"
#include "boost/test/floating_point_comparison.hpp"

#include "cpp0x/random"

#include "cpp0x/cstddef"
#include "cpp0x/detail/stats"
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
typedef  long double  ldbl;

ldbl
  sqr( ldbl x )  { return x * x; }

template< class Distribution >
void
  sample( size_t n = 300000u )
{
  typedef  typename Distribution::result_type  result_t;

  Distribution    d;
  result_t const  min = d.min()
               ,  max = d.max();
  //cout << "Min = " << min << "; Max = " << max << '\n';
  minstd_rand0    e(19375);

  // generate sample:
  vector<result_t>  results;
  for( size_t k = 0u; k != n; ++k )  {
    result_t const  var = d(e);
    //cout << var << '\n';
    BOOST_CHECK( min <= var ); BOOST_CHECK( var <= max );
    results.push_back(var);
  }

  // analyze sample and compare against expected values:
  _::stats s(results.begin(), n);
  _::stats x(d.param().expected());
  BOOST_CHECK_MESSAGE( abs((s.mean()-x.mean()) / x.mean()) < 0.01
    , "mean " << s.mean() << ", expected " << x.mean() );
  BOOST_CHECK_MESSAGE( abs((s.variance()-x.variance()) / x.variance()) < 0.01
    , "variance " << s.variance() << ", expected " << x.variance() );
  BOOST_CHECK_MESSAGE( abs(s.skew()-x.skew()) < 0.01
    , "skew " << s.skew() << ", expected " << x.skew() );
  BOOST_CHECK_MESSAGE( abs((s.kurtosis()-x.kurtosis()) / x.kurtosis()) < 0.03
    , "kurtosis " << s.kurtosis() << ", expected " << x.kurtosis() );
}

BOOST_AUTO_TEST_SUITE( random_test )

#if defined CPP0X_HAS_RANDOM_HDR

  BOOST_AUTO_TEST_CASE( no_need_to_test )
  {
    BOOST_CHECK( true );
  }

#else

  BOOST_AUTO_TEST_CASE( poisson_distribution_test )
  {
    sample< poisson_distribution<int     > >();
    sample< poisson_distribution<long    > >();
    sample< poisson_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( exponential_distribution_test )
  {
    sample< exponential_distribution<float       > >();
    sample< exponential_distribution<double      > >();
  }

  BOOST_AUTO_TEST_CASE( gamma_distribution_test )
  {
    sample< gamma_distribution<double> >();
    sample< gamma_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( weibull_distribution_test )
  {
    sample< weibull_distribution<double> >();
    sample< weibull_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( extreme_value_distribution_test )
  {
    sample< extreme_value_distribution<double> >();
    sample< extreme_value_distribution<float > >();
  }

#endif  // CPP0X_HAS_RANDOM_HDR

BOOST_AUTO_TEST_SUITE_END()
