// ======================================================================
//
// test "iterator" header
//
// ======================================================================

#define BOOST_TEST_MODULE ( "iterator test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/iterator"

#include <algorithm>
#include <list>
#include <map>
#include <vector>

using std::begin;
using std::end;

BOOST_AUTO_TEST_SUITE( iterator )

BOOST_AUTO_TEST_CASE( empty_range_test )
{
  std::vector<int> v;
  BOOST_CHECK( begin(v) == end(v) );

  std::list<int> l;
  BOOST_CHECK( begin(l) == end(l) );

  std::map<int,int> m;
  BOOST_CHECK( begin(m) == end(m) );
}

BOOST_AUTO_TEST_CASE( array_range_test )
{
  int a[ ] = { 11, 12, 13, 14, 15 };
  BOOST_CHECK( begin(a) != end(a) );
  BOOST_CHECK( begin(a) + 5 == end(a) );

  BOOST_CHECK_EQUAL( *begin(a), 11 );
  *begin(a) += 10;
  BOOST_CHECK_EQUAL( *begin(a), 21 );
}

BOOST_AUTO_TEST_CASE( vector_range_test )
{
  int const a[ ] = { 11, 12, 13, 14, 15 };
  std::vector<int> v(begin(a), end(a));
  BOOST_CHECK( begin(v) == v.begin() );
  BOOST_CHECK( end(v) == v.end() );
  BOOST_CHECK_EQUAL( v.size()
                   , size_t( std::distance(begin(a), end(a)) )
                   );

  BOOST_CHECK( std::equal(begin(v), end(v), begin(a)) );
  BOOST_CHECK( std::equal(begin(a), end(a), begin(v)) );
}

BOOST_AUTO_TEST_SUITE_END()
