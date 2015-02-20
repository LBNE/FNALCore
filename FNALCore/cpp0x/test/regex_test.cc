// ======================================================================
//
// test "regex" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "regex test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/regex"
#include <string>

BOOST_AUTO_TEST_SUITE( regex )

BOOST_AUTO_TEST_CASE( basic_test )
{
  std::string  str("Hello world");
  std::regex   rx("ello");

  BOOST_CHECK( regex_search(str.begin(), str.end(), rx) );
  BOOST_CHECK( ! std::regex_match(str.begin(), str.end(), rx) );
}

BOOST_AUTO_TEST_SUITE_END()
