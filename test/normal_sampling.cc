// ======================================================================
//
// statistically test "random" header's distributions
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
  sample( size_t n = 1000000u )
{
  typedef  typename Distribution::result_type  result_t;

  Distribution    d;//(3.5, 2.0);
  result_t const  min = d.min()
               ,  max = d.max();
  //cout << "Min = " << min << "; Max = " << max << '\n';
  minstd_rand     e(19375);

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
  if( x.mean() != 0.0L )
    BOOST_CHECK_MESSAGE( abs((s.mean()-x.mean()) / x.mean()) < 0.01
      , "mean " << s.mean() << ", expected " << x.mean() );
  if( x.variance() != 0.0L )
    BOOST_CHECK_MESSAGE( abs((s.variance()-x.variance()) / x.variance()) < 0.01
      , "variance " << s.variance() << ", expected " << x.variance() );
  if( x.skew() != 0.0L )
    BOOST_CHECK_MESSAGE( abs(s.skew()-x.skew()) /x.skew() < 0.03
      , "skew " << s.skew() << ", expected " << x.skew() );
  if( x.kurtosis() != 0.0L )
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

  BOOST_AUTO_TEST_CASE( normal_distribution_test )
  {
    sample< normal_distribution<double> >();
    sample< normal_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( lognormal_distribution_test )
  {
    sample< lognormal_distribution<double> >();
    sample< lognormal_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( chi_squared_distribution_test )
  {
    sample< chi_squared_distribution<double> >();
    sample< chi_squared_distribution<float > >();
  }

  #if 0
  BOOST_AUTO_TEST_CASE( cauchy_distribution_test )
  {
    // this distribution's statistics are undefined!
    sample< cauchy_distribution<double> >();
    sample< cauchy_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( fisher_f_distribution_test )
  {
    // this distribution's statistics are poorly defined!
    sample< fisher_f_distribution<double> >();
    sample< fisher_f_distribution<float > >();
  }

  BOOST_AUTO_TEST_CASE( student_t_distribution_test )
  {
    # default distribution has no mean!
    sample< student_t_distribution<double> >();
    sample< student_t_distribution<float > >();
  }
  #endif  // 0

#endif  // CPP0X_HAS_RANDOM_HDR

BOOST_AUTO_TEST_SUITE_END()
