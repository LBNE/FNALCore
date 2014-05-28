# - Build documentation as required

#-----------------------------------------------------------------------
# Doxygen
find_package(Doxygen 1.8 REQUIRED)

configure_file(FNALCore.doxyfile.in FNALCore.doxyfile @ONLY)

add_custom_command(OUTPUT html/index.html
  COMMAND ${DOXYGEN_EXECUTABLE} FNALCore.doxyfile
  MAIN_DEPENDENCY FNALCore.doxyfile
  DEPENDS FNALCore
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Doxygenating FNALCore"
  )
add_custom_target(doc ALL DEPENDS html/index.html)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
  )
