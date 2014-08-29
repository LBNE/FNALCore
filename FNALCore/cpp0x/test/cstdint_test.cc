// ======================================================================
//
// test "cstdint" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "cstdint test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/cstdint"

BOOST_AUTO_TEST_SUITE( cstdint_test )

BOOST_AUTO_TEST_CASE( basic_test )
{
  BOOST_CHECK( sizeof(std::int8_t)        == sizeof(std::uint8_t) );
  BOOST_CHECK( sizeof(std::int16_t)       == sizeof(std::uint16_t) );
  BOOST_CHECK( sizeof(std::int32_t)       == sizeof(std::uint32_t) );
  BOOST_CHECK( sizeof(std::int64_t)       == sizeof(std::uint64_t) );

  BOOST_CHECK( sizeof(std::int_least8_t)  == sizeof(std::uint_least8_t) );
  BOOST_CHECK( sizeof(std::int_least16_t) == sizeof(std::uint_least16_t) );
  BOOST_CHECK( sizeof(std::int_least32_t) == sizeof(std::uint_least32_t) );
  BOOST_CHECK( sizeof(std::int_least64_t) == sizeof(std::uint_least64_t) );

  BOOST_CHECK( sizeof(std::int_fast8_t)   == sizeof(std::uint_fast8_t) );
  BOOST_CHECK( sizeof(std::int_fast16_t)  == sizeof(std::uint_fast16_t) );
  BOOST_CHECK( sizeof(std::int_fast32_t)  == sizeof(std::uint_fast32_t) );
  BOOST_CHECK( sizeof(std::int_fast64_t)  == sizeof(std::uint_fast64_t) );

  BOOST_CHECK( sizeof(std::intmax_t)      == sizeof(std::uintmax_t) );
}

BOOST_AUTO_TEST_SUITE_END()
