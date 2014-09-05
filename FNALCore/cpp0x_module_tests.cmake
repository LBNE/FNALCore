# ======================================================================
#
# Testing script
#
# ======================================================================

#-----------------------------------------------------------------------
# For now, build by hand as proof of principle
set(cpp0x_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp0x/test)

include(CetTest)
#cet_enable_asserts()
cet_test(algorithm_test SOURCES ${cpp0x_TEST_DIR}/algorithm_test.cc USE_BOOST_UNIT)
cet_test(array_test SOURCES ${cpp0x_TEST_DIR}/array_test.cc USE_BOOST_UNIT)
cet_test(cmath_test SOURCES ${cpp0x_TEST_DIR}/cmath_test.cc USE_BOOST_UNIT)
cet_test(config_test SOURCES ${cpp0x_TEST_DIR}/config_test.cc USE_BOOST_UNIT)
cet_test(cstdint_test SOURCES ${cpp0x_TEST_DIR}/cstdint_test.cc USE_BOOST_UNIT)
cet_test(device_test SOURCES ${cpp0x_TEST_DIR}/device_test.cc USE_BOOST_UNIT)
cet_test(distribs_test SOURCES ${cpp0x_TEST_DIR}/distribs_test.cc USE_BOOST_UNIT)
cet_test(engines_test SOURCES ${cpp0x_TEST_DIR}/engines_test.cc USE_BOOST_UNIT)
cet_test(functional_test SOURCES ${cpp0x_TEST_DIR}/functional_test.cc USE_BOOST_UNIT)
cet_test(iterator_test SOURCES ${cpp0x_TEST_DIR}/iterator_test.cc USE_BOOST_UNIT)
cet_test(memory_test SOURCES ${cpp0x_TEST_DIR}/memory_test.cc USE_BOOST_UNIT)
cet_test(nullptr_test SOURCES ${cpp0x_TEST_DIR}/nullptr_test.cc USE_BOOST_UNIT)
cet_test(numeric_test SOURCES ${cpp0x_TEST_DIR}/numeric_test.cc USE_BOOST_UNIT)
cet_test(regex_test SOURCES ${cpp0x_TEST_DIR}/regex_test.cc USE_BOOST_UNIT LIBRARIES ${Boost_REGEX_LIBRARY})
cet_test(regex_test_no_boost_unit SOURCES ${cpp0x_TEST_DIR}/regex_test_no_boost_unit.cc LIBRARIES ${Boost_REGEX_LIBRARY})
cet_test(string_test SOURCES ${cpp0x_TEST_DIR}/string_test.cc USE_BOOST_UNIT)
cet_test(system_error_test SOURCES ${cpp0x_TEST_DIR}/system_error_test.cc)
cet_test(tuple_test SOURCES ${cpp0x_TEST_DIR}/tuple_test.cc USE_BOOST_UNIT)
cet_test(type_traits_test SOURCES ${cpp0x_TEST_DIR}/type_traits_test.cc USE_BOOST_UNIT)
cet_test(utility_test SOURCES ${cpp0x_TEST_DIR}/utility_test.cc USE_BOOST_UNIT)
cet_test(uniform_sampling SOURCES ${cpp0x_TEST_DIR}/uniform_sampling.cc USE_BOOST_UNIT)
cet_test(bernoulli_sampling SOURCES ${cpp0x_TEST_DIR}/bernoulli_sampling.cc USE_BOOST_UNIT)
cet_test(poisson_sampling SOURCES ${cpp0x_TEST_DIR}/poisson_sampling.cc USE_BOOST_UNIT
  OPTIONAL_GROUPS LONG RELEASE
  )
cet_test(normal_sampling SOURCES ${cpp0x_TEST_DIR}/normal_sampling.cc USE_BOOST_UNIT
  OPTIONAL_GROUPS LONG RELEASE
  )
