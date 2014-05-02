# - Collect/Build all sources
# Yes, it's quick and dirty
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# cpp0x
add_subdirectory(cpp0x)

#-----------------------------------------------------------------------
# cetlib
add_subdirectory(cetlib)

#-----------------------------------------------------------------------
# fhiclcpp
add_subdirectory(fhiclcpp)

#-----------------------------------------------------------------------
# messagefacility
add_subdirectory(messagefacility)


#-----------------------------------------------------------------------
# Compose FNALCore
set(FNALCore_MODULES cpp0x cetlib fhiclcpp messagefacility)

# PIC needed for shared libs, needs thought for static
set_target_properties(${FNALCore_MODULES} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)


add_library(FNALCore SHARED
  $<TARGET_OBJECTS:cpp0x>
  $<TARGET_OBJECTS:cetlib>
  $<TARGET_OBJECTS:fhiclcpp>
  $<TARGET_OBJECTS:messagefacility>
  )

target_link_libraries(FNALCore
  ${Boost_REGEX_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${CMAKE_DL_LIBS}
  )

target_include_directories(FNALCore
  INTERFACE ${Boost_INCLUDE_DIRS}
  )

#-----------------------------------------------------------------------
# Installation
# - Runtime
install(TARGETS FNALCore
  EXPORT FNALCoreExports
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT Runtime
  )

# - Development
# FOR NOW, headers are installed by their modules, because of the nested
# hierarchy. This is for the sake of getting things running and needs more
# thought.

# - Create export file
install(EXPORT FNALCoreExports
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FNALCore-${FNALCore_VERSION}
  NAMESPACE FNALCore::
  COMPONENT Development
  )

