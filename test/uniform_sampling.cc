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
  sample( size_t n = 100000u )
{
  typedef  typename Distribution::result_type  result_t;

  Distribution    d;
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
  BOOST_CHECK_MESSAGE( abs((s.mean()-x.mean()) / x.mean()) < 0.01
    , "mean " << s.mean() << ", expected " << x.mean() );
  BOOST_CHECK_MESSAGE( abs((s.variance()-x.variance()) / x.variance()) < 0.01
    , "variance " << s.variance() << ", expected " << x.variance() );
  BOOST_CHECK_MESSAGE( abs(s.skew()-x.skew()) < 0.01
    , "skew " << s.skew() << ", expected " << x.skew() );
  BOOST_CHECK_MESSAGE( abs((s.kurtosis()-x.kurtosis()) / x.kurtosis()) < 0.01
    , "kurtosis " << s.kurtosis() << ", expected " << x.kurtosis() );
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
    sample< uniform_int_distribution<int     > >();
    sample< uniform_int_distribution<long    > >();
    sample< uniform_int_distribution<unsigned> >();
  }

  BOOST_AUTO_TEST_CASE( uniform_real_distribution_test )
  {
    sample< uniform_real_distribution<double> >();
    sample< uniform_real_distribution<float > >();
  }

#endif  // CPP0X_HAS_RANDOM_HDR

BOOST_AUTO_TEST_SUITE_END()
