# ======================================================================
#
# Testing script
#
# ======================================================================

link_libraries( MF_Utilities )

cet_test_env(CLEAR "FHICL_FILE_PATH=${CMAKE_CURRENT_SOURCE_DIR}")

cet_test( Exception_t )
cet_test( ExceptionDerived_t )
cet_test( Simple_t )

#add_executable( sha1_test_performance sha1_test_performance.cc sha1.cpp )
#target_link_libraries( sha1_test_performance cetlib )

# ----------------------------------------------------------------------
# Run tests:

foreach ( test ${TEST_LIST} ${ALSO_RUN} )
  add_test (NAME ${test} COMMAND ${test} )
endforeach ( test ${TEST_LIST} )

# Non-standard tests:

# ======================================================================

