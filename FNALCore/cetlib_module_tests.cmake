# ======================================================================
#
# Testing
#
# ======================================================================
set(cetlib_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cetlib/test)

include(CetTest)
#cet_enable_asserts()

# Identify libraries to be linked:
# DEPRECATED IN CMAKE, but use for now, SHOULD use LIBRARIES arg
link_libraries(FNALCore)

cet_test(bit_test SOURCES ${cetlib_TEST_DIR}/bit_test.cc)
cet_test(base_converter_test SOURCES ${cetlib_TEST_DIR}/base_converter_test.cc)
cet_test(canonical_number_test SOURCES ${cetlib_TEST_DIR}/canonical_number_test.cc)
cet_test(canonical_string_test SOURCES ${cetlib_TEST_DIR}/canonical_string_test.cc)
cet_test(coded_exception_test SOURCES ${cetlib_TEST_DIR}/coded_exception_test.cc)
cet_test(column_width_test SOURCES ${cetlib_TEST_DIR}/column_width_test.cc USE_BOOST_UNIT)
cet_test(container_algs_test SOURCES ${cetlib_TEST_DIR}/container_algs_test.cc)
cet_test(cpu_timer_test NO_AUTO SOURCES ${cetlib_TEST_DIR}/cpu_timer_test.cc)
cet_test(crc32_test SOURCES ${cetlib_TEST_DIR}/crc32_test.cc ${cetlib_TEST_DIR}/CRC32Calculator.cc)
cet_test(demangle_t SOURCES ${cetlib_TEST_DIR}/demangle_t.cc USE_BOOST_UNIT)
cet_test(exception_collector_test SOURCES ${cetlib_TEST_DIR}/exception_collector_test.cc)
cet_test(exception_test SOURCES ${cetlib_TEST_DIR}/exception_test.cc)
cet_test(exempt_ptr_test SOURCES ${cetlib_TEST_DIR}/exempt_ptr_test.cc)
cet_test(filesystem_test SOURCES ${cetlib_TEST_DIR}/filesystem_test.cc)
cet_test(getenv_test SOURCES ${cetlib_TEST_DIR}/getenv_test.cc)
cet_test(hypot_test SOURCES ${cetlib_TEST_DIR}/hypot_test.cc USE_BOOST_UNIT)
#cet_test(inc-expand_test.sh PREBUILT DEPENDENCIES inc-expand)
cet_test(include_test SOURCES ${cetlib_TEST_DIR}/include_test.cc)
cet_test(includer_test SOURCES ${cetlib_TEST_DIR}/includer_test.cc USE_BOOST_UNIT)
cet_test(is_absolute_filepath_t SOURCES ${cetlib_TEST_DIR}/is_absolute_filepath_t.cc USE_BOOST_UNIT)
cet_test(lpad_test SOURCES ${cetlib_TEST_DIR}/lpad_test.cc USE_BOOST_UNIT)
cet_test(make_unique_t SOURCES ${cetlib_TEST_DIR}/make_unique_t.cc USE_BOOST_UNIT)
cet_test(map_vector_test SOURCES ${cetlib_TEST_DIR}/map_vector_test.cc USE_BOOST_UNIT)
cet_test(maybe_ref_test SOURCES ${cetlib_TEST_DIR}/maybe_ref_test.cc USE_BOOST_UNIT)
cet_test(md5_test SOURCES ${cetlib_TEST_DIR}/md5_test.cc ${cetlib_TEST_DIR}/md5.cc ${cetlib_TEST_DIR}/Digest.cc)
cet_test(name_of_test SOURCES ${cetlib_TEST_DIR}/name_of_test.cc USE_BOOST_UNIT)
cet_test(ntos_test SOURCES ${cetlib_TEST_DIR}/ntos_test.cc USE_BOOST_UNIT)
cet_test(nybbler_test SOURCES ${cetlib_TEST_DIR}/nybbler_test.cc)
cet_test(pow_test SOURCES ${cetlib_TEST_DIR}/pow_test.cc USE_BOOST_UNIT)
cet_test(registry_test SOURCES ${cetlib_TEST_DIR}/registry_test.cc)
cet_test(registry_via_id_test SOURCES ${cetlib_TEST_DIR}/registry_via_id_test.cc)
cet_test(registry_via_id_test_2 NO_AUTO SOURCES ${cetlib_TEST_DIR}/registry_via_id_test_2.cc) # for now -- see test's source
cet_test(rpad_test SOURCES ${cetlib_TEST_DIR}/rpad_test.cc USE_BOOST_UNIT)
cet_test(search_path_test SOURCES ${cetlib_TEST_DIR}/search_path_test.cc)
cet_test(search_path_test_2 NO_AUTO SOURCES ${cetlib_TEST_DIR}/search_path_test_2.cc)
#cet_test(search_path_test_2.sh PREBUILT DEPENDENCIES search_path_test_2)
cet_test(search_path_test_3 SOURCES ${cetlib_TEST_DIR}/search_path_test_3.cc USE_BOOST_UNIT)
cet_test(sha1_test SOURCES ${cetlib_TEST_DIR}/sha1_test.cc)
cet_test(sha1_test_2 SOURCES ${cetlib_TEST_DIR}/sha1_test_2.cc ${cetlib_TEST_DIR}/sha1.cpp)
cet_test(sha1_test_performance NO_AUTO SOURCES ${cetlib_TEST_DIR}/sha1_test_performance.cc ${cetlib_TEST_DIR}/sha1.cpp)
cet_test(shlib_utils_t USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/shlib_utils_t.cc)
cet_test(simple_stats_t USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/simple_stats_t.cc)
cet_test(split_path_test SOURCES ${cetlib_TEST_DIR}/split_path_test.cc)
cet_test(split_test SOURCES ${cetlib_TEST_DIR}/split_test.cc)
cet_test(ston_test USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/ston_test.cc)
cet_test(trim_test USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/trim_test.cc)
cet_test(value_ptr_test USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/value_ptr_test.cc)
cet_test(value_ptr_test_2 SOURCES ${cetlib_TEST_DIR}/value_ptr_test_2.cc)
cet_test(value_ptr_test_3 SOURCES ${cetlib_TEST_DIR}/value_ptr_test_3.cc)
cet_test(value_ptr_test_4 SOURCES ${cetlib_TEST_DIR}/value_ptr_test_4.cc)
cet_test(value_ptr_test_5 SOURCES ${cetlib_TEST_DIR}/value_ptr_test_5.cc)
cet_test(zero_init_test USE_BOOST_UNIT SOURCES ${cetlib_TEST_DIR}/zero_init_test.cc)

# - Handbuilt test for LibraryManager
add_library(test_fakePlugin SHARED ${cetlib_TEST_DIR}/moduleType.cc)
add_executable(LibraryManager_t ${cetlib_TEST_DIR}/LibraryManager_t.cc)
set_target_properties(LibraryManager_t
  PROPERTIES
   COMPILE_DEFINITIONS "BOOST_TEST_MAIN;BOOST_TEST_DYN_LINK"
   )
target_link_libraries(LibraryManager_t
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
configure_file(${cetlib_TEST_DIR}/LibraryManager_t.sh.in LibraryManager_t.sh @ONLY)
cet_test(LibraryManager_t HANDBUILT TEST_EXEC ${CMAKE_CURRENT_BINARY_DIR}/LibraryManager_t.sh)

# - Plugin test
# This will fail because unlike the above, it doesn't set LD_LIBRARY_PATH
add_library(test_TestPluginBase SHARED ${cetlib_TEST_DIR}/TestPluginBase.cc)
add_library(TestPlugin_plugin SHARED ${cetlib_TEST_DIR}/TestPlugin_plugin.cc)
target_link_libraries(TestPlugin_plugin test_TestPluginBase)
cet_test(PluginFactory_t SOURCES ${cetlib_TEST_DIR}/PluginFactory_t.cc USE_BOOST_UNIT LIBRARIES test_TestPluginBase)

