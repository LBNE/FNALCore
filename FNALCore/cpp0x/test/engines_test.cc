// ======================================================================
//
// test "random" header's engines
//
// ======================================================================

#define BOOST_TEST_MODULE ( "random test" )
#include "boost/test/auto_unit_test.hpp"

#include "cpp0x/random"
#include <sstream>

using namespace std;

template< class Engine >
void
  test_10000th( typename Engine::result_type value )
{
  Engine e;
  e.discard( 9999 );
  BOOST_CHECK_EQUAL( e(), value );
}

template< class Engine >
void
  test_equality( )
{
  { Engine d1, d2;         BOOST_CHECK_EQUAL( d1, d2 );
    d1();                  BOOST_CHECK_MESSAGE( d1 != d2, "d1() failed!" );
    d2.discard(1);         BOOST_CHECK_EQUAL( d1, d2 );
  }
  { Engine c1, c2(c1);     BOOST_CHECK_EQUAL( c1, c2 );
  }
  { Engine a1, a2(13579);  BOOST_CHECK_MESSAGE( a1 != a2, "a2 failed init!" );
    a2 = a1;               BOOST_CHECK_EQUAL( a1, a2 );
    a1.discard(137);       BOOST_CHECK_MESSAGE( a1 != a2, "a1.discard failed!" );
    a2.discard(9753);      BOOST_CHECK_MESSAGE( a1 != a2, "a2.discard failed!" );
    a1 = a2;               BOOST_CHECK_EQUAL( a1, a2 );
  }
  { Engine s1, s2;         BOOST_CHECK_EQUAL( s1, s2 );
    s2.discard(807);       BOOST_CHECK_MESSAGE( s1 != s2, "s2.discard failed" );
    s2.seed();             BOOST_CHECK_EQUAL( s1, s2 );
    for( int s = 97; s != 121; ++s ) {
     Engine s1(s);
     s2.seed(s);           BOOST_CHECK_EQUAL( s1, s2 );
    }
  }
  { Engine i1, i2;         BOOST_CHECK_EQUAL( i1, i2 );
    i1.discard(311);       BOOST_CHECK_MESSAGE( i1 != i2, "i1.discard failed" );
    ostringstream os;
    os << i1;
    istringstream is(os.str());
    is >> i2;              BOOST_CHECK_EQUAL( i1, i2 );
  }
}

BOOST_AUTO_TEST_SUITE( random_test )

#if defined CPP0X_HAS_RANDOM_HDR

  BOOST_AUTO_TEST_CASE( no_need_to_test )
  {
    BOOST_CHECK( true );
  }

#else

  BOOST_AUTO_TEST_CASE( linear_congruential_engine_test )
  {
    test_equality<minstd_rand0>();
    test_equality<minstd_rand >();
  }

  BOOST_AUTO_TEST_CASE( mersenne_twister_engine_test )
  {
    test_equality<mt19937   >();
    test_equality<mt19937_64>();
  }

  BOOST_AUTO_TEST_CASE( subtract_with_carry_test )
  {
    test_equality<ranlux24_base>();
    test_equality<ranlux48_base>();
  }

  BOOST_AUTO_TEST_CASE( discard_block_test )
  {
    test_equality<ranlux24>();
    test_equality<ranlux48>();
  }

  BOOST_AUTO_TEST_CASE( independent_bits_test )
  {
    typedef  independent_bits_engine<std::minstd_rand,24u,unsigned>
             ibe1_t;
    test_equality<ibe1_t>();
  }

  BOOST_AUTO_TEST_CASE( shuffle_order_test )
  {
    typedef  shuffle_order_engine<std::minstd_rand,24u>
             soe1_t;
    test_equality<soe1_t>();
  }

  BOOST_AUTO_TEST_CASE( predefined_engines_test )
  {
    test_10000th<minstd_rand0 >(         1043618065u);
    test_10000th<minstd_rand  >(          399268537u);
    test_10000th<mt19937      >(         4123659995u);
    test_10000th<mt19937_64   >(9981545732273789042u);
    test_10000th<ranlux24_base>(            7937952u);
    test_10000th<ranlux48_base>(     61839128582725u);
    test_10000th<ranlux24     >(            9901578u);
    test_10000th<ranlux48     >(    249142670248501u);
  }

#endif  // CPP0X_HAS_RANDOM_HDR

BOOST_AUTO_TEST_SUITE_END()
