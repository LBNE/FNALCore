// ======================================================================
//
// test "numeric" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "numeric test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/numeric"

template< class T, unsigned N >
void
  do_test( )
{
  T a[N];
  std::iota( a+0, a+N, static_cast<T>(0) );
  for( unsigned k = 0;  k != N;  ++k )
    BOOST_CHECK( a[k] == static_cast<T>(k) );

  T * p[N];
  std::iota( p+0, p+N, a+0 );
  for( unsigned k = 0;  k != N;  ++k )
    BOOST_CHECK( p[k] == &a[k] );
}

BOOST_AUTO_TEST_SUITE( numeric_test )

BOOST_AUTO_TEST_CASE( int_test )
{
  do_test<int,19>();
}

BOOST_AUTO_TEST_CASE( float_test )
{
  do_test<float,13>();
}

BOOST_AUTO_TEST_CASE( long_double_test )
{
  do_test<long double,17>();
}

BOOST_AUTO_TEST_SUITE_END()
