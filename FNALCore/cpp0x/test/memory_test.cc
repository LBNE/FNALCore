// ======================================================================
//
// test "memory" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "memory test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/memory"

BOOST_AUTO_TEST_SUITE( memory_test )

BOOST_AUTO_TEST_CASE( basic_test )
{
  std::shared_ptr<double>  sp = std::make_shared<double>( 3.14 );
  std::unique_ptr<int>     up( new int(0) );

  BOOST_CHECK( (*up) * (*sp) == 0 );
}

BOOST_AUTO_TEST_SUITE_END()
