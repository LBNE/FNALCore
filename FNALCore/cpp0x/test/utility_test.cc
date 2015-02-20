// ======================================================================
//
// test "utility" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "utility test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/utility"

BOOST_AUTO_TEST_SUITE( utility )

typedef  char (& yes_t)[1];
typedef  char (& no_t )[2];
yes_t
  is_int( int );
template< class T >
no_t
  is_int( T );

BOOST_AUTO_TEST_CASE( basic_test )
{
  BOOST_CHECK( sizeof( is_int(std::declval<int  >()) ) == sizeof(yes_t) );
  BOOST_CHECK( sizeof( is_int(std::declval<char >()) ) == sizeof(no_t) );
  BOOST_CHECK( sizeof( is_int(std::declval<float>()) ) == sizeof(no_t) );
}

BOOST_AUTO_TEST_SUITE_END()
