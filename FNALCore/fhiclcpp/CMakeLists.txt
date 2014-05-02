# define contents of interest:
set(PUBLIC_HDRS
  ParameterSet.h
  ParameterSetID.h
  ParameterSetRegistry.h
  coding.h
  exception.h
  extended_value.h
  fwd.h
  intermediate_table.h
  make_ParameterSet.h
  parse.h
  tokens.h
  type_traits.h
)

set(SOURCES
  ParameterSet.cc
  ParameterSetID.cc
  coding.cc
  exception.cc
  extended_value.cc
  intermediate_table.cc
  make_ParameterSet.cc
  parse.cc
)


add_library(fhiclcpp OBJECT ${PUBLIC_HDRS} ${SOURCES})

# TEMP local install of headers
install(FILES ${PUBLIC_HDRS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/fhiclcpp
  COMPONENT Development
  )

#-----------------------------------------------------------------------
# Testing
if(FNALCore_ENABLE_TESTING)
  add_subdirectory(unittests)
endif()


# ======================================================================
