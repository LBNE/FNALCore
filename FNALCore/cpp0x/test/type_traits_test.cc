// ======================================================================
//
// test "type_traits" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "type_traits test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/type_traits"

BOOST_AUTO_TEST_SUITE( type_traits )

BOOST_AUTO_TEST_CASE( basic_test )
{

  typedef  std::make_unsigned<int>::type  uint;
  uint u = 0u;
  std::add_lvalue_reference<uint>::type  r = u;
  BOOST_CHECK( r == 0u );
}

BOOST_AUTO_TEST_SUITE_END()
