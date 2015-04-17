// ======================================================================
//
// test "tuple" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "tuple test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/tuple"

BOOST_AUTO_TEST_SUITE( tuple_test )

BOOST_AUTO_TEST_CASE( basic_test )
{
  std::tuple<bool,int,double>  t;
  BOOST_CHECK( true );
}

BOOST_AUTO_TEST_SUITE_END()
