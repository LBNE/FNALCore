# - Build documentation as required

#-----------------------------------------------------------------------
# Doxygen
find_package(Doxygen 1.8 REQUIRED)

# - Configure
# We create and install a tags file so that clients can cross link to
# or documents.
# TODO: provide path to tag file as a component in the cmake project
# config file.
set(FNALCore_DOXYGEN_TAGFILE "FNALCore.doxytags")
configure_file(FNALCore.doxyfile.in FNALCore.doxyfile @ONLY)

add_custom_command(OUTPUT html/index.html
  COMMAND ${DOXYGEN_EXECUTABLE} FNALCore.doxyfile
  MAIN_DEPENDENCY FNALCore.doxyfile
  DEPENDS FNALCore
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Doxygenating FNALCore"
  )
add_custom_target(doc ALL DEPENDS html/index.html)

# - HTML docs
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
  DESTINATION ${CMAKE_INSTALL_DOCDIR}/doxygen
  COMPONENT Documentation
  )

# - Doxygen tag file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${FNALCore_DOXYGEN_TAGFILE}
  DESTINATION ${CMAKE_INSTALL_DOCDIR}/doxygen
  COMPONENT Documentation
  )
