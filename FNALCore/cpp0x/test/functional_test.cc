// ======================================================================
//
// test "functional" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "functional test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/functional"

BOOST_AUTO_TEST_SUITE( functional_test )

int
  v( int,int j )
{ return j; }

BOOST_AUTO_TEST_CASE( basic_test )
{
  std::function<int(int)>  f( std::bind(v, 1, std::placeholders::_1) );
  BOOST_CHECK( f(0) == 0 );
}

BOOST_AUTO_TEST_SUITE_END()
