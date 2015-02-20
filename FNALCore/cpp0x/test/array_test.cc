// ======================================================================
//
// test "array" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "array test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/array"
#include <algorithm>

BOOST_AUTO_TEST_SUITE( array_test )

BOOST_AUTO_TEST_CASE( basic_test )
{
  unsigned const  N = 10;
  std::array<int,N>  a;
  int const  value = 15;
  std::fill( a.begin(), a.end(), value );

  for( unsigned k = 0;  k != N;  ++k )  {
    BOOST_CHECK( a[k] == value );
    BOOST_CHECK( *(a.data()+k) == value );
    BOOST_CHECK( a.begin()[k] == value );
  }

  for( std::array<int,N>::const_iterator it = a.begin()
                                       , e  = a.end();  it != e;  ++it )
    BOOST_CHECK( *it == value );
}

BOOST_AUTO_TEST_SUITE_END()
