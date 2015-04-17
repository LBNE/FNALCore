// ======================================================================
//
// test "cmath" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "cmath test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/cmath"
#include <limits>

long n = 0L;

// Temporarily work around a known bug with the intel compiler
#if defined (__ICC) && __INTEL_COMPILER_BUILD_DATE <= 20140120
#define NANINF_CONST
#else
#define NANINF_CONST const
#endif

template< class T >
void
  count( T )  { ++n; }

BOOST_AUTO_TEST_SUITE( cmath_test )

BOOST_AUTO_TEST_CASE( inf_test )
{
  double NANINF_CONST d = std::numeric_limits<double>::infinity();
  BOOST_CHECK( std::isinf(d) );
  BOOST_CHECK( ! std::isnan(d) );
  BOOST_CHECK( ! std::isnormal(d) );
}

BOOST_AUTO_TEST_CASE( nan_test )
{
  double NANINF_CONST d = 0.0 / 0.0;
  BOOST_CHECK( std::isnan(d) );
  BOOST_CHECK( ! std::isinf(d) );
  BOOST_CHECK( ! std::isnormal(d) );
}

BOOST_AUTO_TEST_CASE( hypot_test ) {
  BOOST_CHECK_EQUAL( std::hypot(5, 12), 13 );
  BOOST_CHECK_CLOSE( std::hypot(.5, 1.2), 1.3, 0.0001 );
  BOOST_CHECK_CLOSE( std::hypot(.05L, .12L), .13L, 0.0001L );
}

BOOST_AUTO_TEST_CASE( hyperbolic_fctns_test ) {
  double const d = 0.5;
  count( std::asinh(d) );
  count( std::acosh(d) );
  count( std::atanh(d) );
}

BOOST_AUTO_TEST_CASE( power_fctns_test ) {
  double const d = 0.5;

  count( std::cbrt(d) );

  count( std::exp2(d) );
  count( std::expm1(d) );

  count( std::ilogb(d) );
  count( std::log1p(d) );
  count( std::log2(d) );
  count( std::logb(d) );
}

BOOST_AUTO_TEST_CASE( spec_fctns_test ) {
  double const d = 0.5;
  count( std::erf(d) );
  count( std::erfc(d) );
  count( std::lgamma(d) );
  count( std::tgamma(d) );
}

BOOST_AUTO_TEST_CASE( normalization_fctns_test ) {
  double const d = 0.5;
  count( std::scalbln(d, 3L) );
  count( std::scalbn(d, 3) );
}

BOOST_AUTO_TEST_CASE( rounding_fctns_test ) {
  double const d = 0.5;
  count( std::llrint(d) );
  count( std::llround(d) );
  count( std::lrint(d) );
  count( std::lround(d) );
  count( std::nearbyint(d) );
  count( std::rint(d) );
  count( std::round(d) );
  count( std::trunc(d) );
}

BOOST_AUTO_TEST_CASE( remainder_fctns_test ) {
  double const d = 0.5;
  int quo;
  count( std::remainder(d,d) );
  count( std::remquo(d,d,&quo) );
}

BOOST_AUTO_TEST_CASE( single_bit_fctns_test ) {
  double const d = 0.5;
  char NaN_rep [] = "0123456789";
  count( std::copysign(d,d) );
  count( std::nextafter(d,d) );
  count( std::nexttoward(d,d) );
  count( std::nan(NaN_rep) );
}

BOOST_AUTO_TEST_CASE( misc_fctns_test ) {
  double const d = 0.5;
  count( std::fmax(d,d) );
  count( std::fmin(d,d) );
  count( std::fdim(d,d) );
  count( std::fma(d,d,d) );
}


BOOST_AUTO_TEST_SUITE_END()
