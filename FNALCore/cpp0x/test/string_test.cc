// ======================================================================
//
// test "string" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "string test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/string"

BOOST_AUTO_TEST_SUITE( string_test )

BOOST_AUTO_TEST_CASE( stoi_test )
{
  BOOST_CHECK_EQUAL( std::stoi("123"), 123 );
  BOOST_CHECK_EQUAL( std::stoi("  123"), 123 );
  BOOST_CHECK_EQUAL( std::stoi("123xyz"), 123 );

  size_t next;
  BOOST_CHECK_EQUAL( std::stoi("123", &next), 123 );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoi("  123", &next), 123 );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoi("123xyz", &next), 123 );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_EQUAL( std::stoi("123", &next, 8), 83 );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoi("  123", &next, 8), 83 );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoi("123xyz", &next, 8), 83 );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_THROW( std::stoi( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stoi( "999999999999999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stol_test )
{
  BOOST_CHECK_EQUAL( std::stol("123"), 123L );
  BOOST_CHECK_EQUAL( std::stol("  123"), 123L );
  BOOST_CHECK_EQUAL( std::stol("123xyz"), 123L );

  size_t next;
  BOOST_CHECK_EQUAL( std::stol("123", &next), 123L );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stol("  123", &next), 123L );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stol("123xyz", &next), 123L );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_EQUAL( std::stol("123", &next, 8), 83L );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stol("  123", &next, 8), 83L );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stol("123xyz", &next, 8), 83L );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_THROW( std::stol( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stol( "999999999999999999999999999999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stoll_test )
{
  BOOST_CHECK_EQUAL( std::stoll("123"), 123LL );
  BOOST_CHECK_EQUAL( std::stoll("  123"), 123LL );
  BOOST_CHECK_EQUAL( std::stoll("123xyz"), 123LL );

  size_t next;
  BOOST_CHECK_EQUAL( std::stoll("123", &next), 123LL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoll("  123", &next), 123LL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoll("123xyz", &next), 123LL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_EQUAL( std::stoll("123", &next, 8), 83LL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoll("  123", &next, 8), 83LL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoll("123xyz", &next, 8), 83LL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_THROW( std::stoll( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stoll( "999999999999999999999999999999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stoul_test )
{
  BOOST_CHECK_EQUAL( std::stoul("123"), 123UL );
  BOOST_CHECK_EQUAL( std::stoul("  123"), 123UL );
  BOOST_CHECK_EQUAL( std::stoul("123xyz"), 123UL );

  size_t next;
  BOOST_CHECK_EQUAL( std::stoul("123", &next), 123UL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoul("  123", &next), 123UL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoul("123xyz", &next), 123UL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_EQUAL( std::stoul("123", &next, 8), 83UL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoul("  123", &next, 8), 83UL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoul("123xyz", &next, 8), 83UL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_THROW( std::stoul( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stoul( "999999999999999999999999999999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stoull_test )
{
  BOOST_CHECK_EQUAL( std::stoull("123"), 123ULL );
  BOOST_CHECK_EQUAL( std::stoull("  123"), 123ULL );
  BOOST_CHECK_EQUAL( std::stoull("123xyz"), 123ULL );

  size_t next;
  BOOST_CHECK_EQUAL( std::stoull("123", &next), 123ULL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoull("  123", &next), 123ULL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoull("123xyz", &next), 123ULL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_EQUAL( std::stoull("123", &next, 8), 83ULL );
  BOOST_CHECK_EQUAL( next, 3u );
  BOOST_CHECK_EQUAL( std::stoull("  123", &next, 8), 83ULL );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stoull("123xyz", &next, 8), 83ULL );
  BOOST_CHECK_EQUAL( next, 3u );

  BOOST_CHECK_THROW( std::stoull( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stoull( "999999999999999999999999999999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stof_test )
{
  BOOST_CHECK_EQUAL( std::stof("123.0"), 123.0F );
  BOOST_CHECK_EQUAL( std::stof("  123.0"), 123.0F );
  BOOST_CHECK_EQUAL( std::stof("123.0xyz"), 123.0F );

  size_t next;
  BOOST_CHECK_EQUAL( std::stof("123.0", &next), 123.0F );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stof("  123.0", &next), 123.0F );
  BOOST_CHECK_EQUAL( next, 7u );
  BOOST_CHECK_EQUAL( std::stof("123.0xyz", &next), 123.0F );
  BOOST_CHECK_EQUAL( next, 5u );

  BOOST_CHECK_THROW( std::stof( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stof( "999.e-99999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stod_test )
{
  BOOST_CHECK_EQUAL( std::stod("123.0"), 123.0 );
  BOOST_CHECK_EQUAL( std::stod("  123.0"), 123.0 );
  BOOST_CHECK_EQUAL( std::stod("123.0xyz"), 123.0 );

  size_t next;
  BOOST_CHECK_EQUAL( std::stod("123.0", &next), 123.0 );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stod("  123.0", &next), 123.0 );
  BOOST_CHECK_EQUAL( next, 7u );
  BOOST_CHECK_EQUAL( std::stod("123.0xyz", &next), 123.0 );
  BOOST_CHECK_EQUAL( next, 5u );

  BOOST_CHECK_THROW( std::stod( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stod( "999.e-99999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( stold_test )
{
  BOOST_CHECK_EQUAL( std::stold("123.0"), 123.0L );
  BOOST_CHECK_EQUAL( std::stold("  123.0"), 123.0L );
  BOOST_CHECK_EQUAL( std::stold("123.0xyz"), 123.0L );

  size_t next;
  BOOST_CHECK_EQUAL( std::stold("123.0", &next), 123.0L );
  BOOST_CHECK_EQUAL( next, 5u );
  BOOST_CHECK_EQUAL( std::stold("  123.0", &next), 123.0L );
  BOOST_CHECK_EQUAL( next, 7u );
  BOOST_CHECK_EQUAL( std::stold("123.0xyz", &next), 123.0L );
  BOOST_CHECK_EQUAL( next, 5u );

  BOOST_CHECK_THROW( std::stold( "m"), std::invalid_argument );
  BOOST_CHECK_THROW( std::stold( "999.e-99999"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( to_string_test )
{
  BOOST_CHECK_EQUAL( std::to_string(12345), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345U), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345L), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345UL), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345LL), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345ULL), std::string("12345") );
  BOOST_CHECK_EQUAL( std::to_string(12345.0F), std::string("12345.000000") );
  BOOST_CHECK_EQUAL( std::to_string(12345.0), std::string("12345.000000") );
  BOOST_CHECK_EQUAL( std::to_string(12345.0L), std::string("12345.000000") );
}

BOOST_AUTO_TEST_SUITE_END()
