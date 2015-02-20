// ======================================================================
//
// test nullptr and std::nullptr_t
//
// ======================================================================

#define BOOST_TEST_MODULE ( "nullptr test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/cstddef"

struct A
{
  A( std::nullptr_t )  { }
  friend  bool  operator == ( A, A )  { return true; }
};  // A

BOOST_AUTO_TEST_SUITE( nullptr_test )

BOOST_AUTO_TEST_CASE( basic_comparisons_test )
{
  BOOST_CHECK( nullptr == static_cast<void*>(0) );
  BOOST_CHECK( nullptr == nullptr );
  BOOST_CHECK( ! (nullptr != nullptr) );
  BOOST_CHECK( nullptr <= nullptr );
  BOOST_CHECK( ! (nullptr > nullptr) );
  BOOST_CHECK( nullptr >= nullptr );
  BOOST_CHECK( ! (nullptr < nullptr) );
}

BOOST_AUTO_TEST_CASE( basic_conversions_test )
{
  BOOST_CHECK( ! static_cast<bool>(nullptr) );

  int * p(0);
  int * q(nullptr);
  BOOST_CHECK( p == nullptr && nullptr == p );
  BOOST_CHECK( q == nullptr && nullptr == q );
  BOOST_CHECK( p == q );

  int A::* pmd = 0;
  BOOST_CHECK( pmd == nullptr );
  void (A::* pmf)() = 0;
  BOOST_CHECK( pmf == nullptr );
}

BOOST_AUTO_TEST_CASE( other_properties_test )
{
  BOOST_CHECK( sizeof(std::nullptr_t) == sizeof(void*) );
  BOOST_CHECK( std::nullptr_t() == nullptr );
  BOOST_CHECK( A(0) == A(nullptr) );
  char const * s1 = 0;
  char const * s2 = "abc";
  BOOST_CHECK( s1 == nullptr );
  BOOST_CHECK( s2 != nullptr );
}

BOOST_AUTO_TEST_SUITE_END()
