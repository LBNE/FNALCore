// ======================================================================
//
// test internal "_config_" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "config test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/detail/config"

BOOST_AUTO_TEST_SUITE( config_test )

BOOST_AUTO_TEST_CASE( basic_test )
{
  BOOST_CHECK( GCC_IS_AT_LEAST(4,2,0) );
}

BOOST_AUTO_TEST_SUITE_END()
