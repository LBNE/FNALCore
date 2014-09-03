# ======================================================================
#
# Testing
#
# ======================================================================

include(CetTest)
#cet_enable_asserts()

# Identify libraries to be linked:
# DEPRECATED IN CMAKE, but use for now, SHOULD use LIBRARIES arg
link_libraries(FNALCore)

cet_test(bit_test)
cet_test(base_converter_test)
cet_test(canonical_number_test)
cet_test(canonical_string_test)
cet_test(coded_exception_test)
cet_test(column_width_test USE_BOOST_UNIT)
cet_test(container_algs_test)
cet_test(cpu_timer_test NO_AUTO)
cet_test(crc32_test SOURCES crc32_test.cc CRC32Calculator.cc)
cet_test(demangle_t USE_BOOST_UNIT)
cet_test(exception_collector_test)
cet_test(exception_test)
cet_test(exempt_ptr_test)
cet_test(filesystem_test)
cet_test(getenv_test)
cet_test(hypot_test USE_BOOST_UNIT)
#cet_test(inc-expand_test.sh PREBUILT DEPENDENCIES inc-expand)
cet_test(include_test)
cet_test(includer_test USE_BOOST_UNIT)
cet_test(is_absolute_filepath_t USE_BOOST_UNIT)
cet_test(lpad_test USE_BOOST_UNIT)
cet_test(make_unique_t USE_BOOST_UNIT)
cet_test(map_vector_test USE_BOOST_UNIT)
cet_test(maybe_ref_test USE_BOOST_UNIT)
cet_test(md5_test SOURCES md5_test.cc md5.cc Digest.cc)
cet_test(name_of_test USE_BOOST_UNIT)
cet_test(ntos_test USE_BOOST_UNIT)
cet_test(nybbler_test)
cet_test(pow_test USE_BOOST_UNIT)
cet_test(registry_test)
cet_test(registry_via_id_test)
cet_test(registry_via_id_test_2 NO_AUTO) # for now -- see test's source
cet_test(rpad_test USE_BOOST_UNIT)
cet_test(search_path_test)
cet_test(search_path_test_2 NO_AUTO)
#cet_test(search_path_test_2.sh PREBUILT DEPENDENCIES search_path_test_2)
cet_test(search_path_test_3 USE_BOOST_UNIT)
cet_test(sha1_test)
cet_test(sha1_test_2 SOURCES sha1_test_2.cc sha1.cpp)
cet_test(sha1_test_performance NO_AUTO SOURCES sha1_test_performance.cc sha1.cpp)
cet_test(shlib_utils_t USE_BOOST_UNIT)
cet_test(simple_stats_t USE_BOOST_UNIT)
cet_test(split_path_test)
cet_test(split_test)
cet_test(ston_test USE_BOOST_UNIT)
cet_test(trim_test USE_BOOST_UNIT)
cet_test(value_ptr_test USE_BOOST_UNIT)
cet_test(value_ptr_test_2)
cet_test(value_ptr_test_3)
cet_test(value_ptr_test_4)
cet_test(value_ptr_test_5)
cet_test(zero_init_test USE_BOOST_UNIT)

# - Handbuilt test for LibraryManager
add_library(test_fakePlugin SHARED moduleType.cc)
add_executable(LibraryManager_t LibraryManager_t.cc)
set_target_properties(LibraryManager_t
  PROPERTIES
   COMPILE_DEFINITIONS "BOOST_TEST_MAIN;BOOST_TEST_DYN_LINK"
   )
target_link_libraries(LibraryManager_t
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
configure_file(LibraryManager_t.sh.in LibraryManager_t.sh @ONLY)
cet_test(LibraryManager_t HANDBUILT TEST_EXEC ${CMAKE_CURRENT_BINARY_DIR}/LibraryManager_t.sh)

# - Plugin test
# This will fail because unlike the above, it doesn't set LD_LIBRARY_PATH
add_library(test_TestPluginBase SHARED TestPluginBase.cc)
add_library(TestPlugin_plugin SHARED TestPlugin_plugin.cc)
target_link_libraries(TestPlugin_plugin test_TestPluginBase)
cet_test(PluginFactory_t USE_BOOST_UNIT LIBRARIES test_TestPluginBase)
