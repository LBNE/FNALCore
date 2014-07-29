# - Collect/Build all sources
# Yes, it's quick and dirty
# We *could* use target_include_directories here, but it's not clear
# yet how to propagate these correctly from an object library to
# the target adding the object library - hence the "quick and dirty"!
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

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

# PIC needed for shared libs, as OBJECT type libs are built without
# it. We always build FNALCore as a shared lib at the moment. PIC
# *should* be o.k. for static libs, but needs further study
set_target_properties(${FNALCore_MODULES}
  PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
  )

# - Create library from modules
add_library(FNALCore SHARED
  $<TARGET_OBJECTS:cpp0x>
  $<TARGET_OBJECTS:cetlib>
  $<TARGET_OBJECTS:fhiclcpp>
  $<TARGET_OBJECTS:messagefacility>
  )

# - Set core properties
set_target_properties(FNALCore
  PROPERTIES
    VERSION "${FNALCore_VERSION}"
    SOVERSION "${FNALCore_SOVERSION}"
#    DEBUG_POSTFIX "${FNALCore_DEBUG_POSTFIX}"
  )

# - Set custom properties
# Just an example - but should mean consuming targets need same property
# set
set_property(TARGET FNALCore
  APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING CXX_STANDARD
  )
set_property(TARGET FNALCore
  PROPERTY INTERFACE_CXX_STANDARD 11
  )

# - Describe link interface
# Know that filesystem/system are private, needs investigation on the
# others
target_link_libraries(FNALCore
  LINK_PUBLIC
    ${Boost_REGEX_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${CMAKE_DL_LIBS}
  LINK_PRIVATE
    ${Boost_FILESYSTEM_LIBRARY}
    ${BOOST_SYSTEM_LIBRARY}
  )

# - Describe API interface
# As noted above, we'd ideally like to pick this up from the composite
# OBJECT modules.
target_include_directories(FNALCore
  INTERFACE
    # Build interface applies if a client uses find_package against builddir
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR};${CMAKE_CURRENT_SOURCE_DIR}>"
    # Install interface applies if client uses find_package against installdir
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/FNALCore>"

    # Because we don't have Boost libs as imported targets (yet)
    # this directory gets hardcoded in (for now...). Imported targets
    # should allow relocatability, *but* then require an additional
    # find_package call to refind (in this case) Boost. Where Boost
    # was found when building FNALCore can be used as a HINT argument,
    # and COMPATIBLE_INTERFACE properties can be used to ensure
    # a compatible ABI.
    "${Boost_INCLUDE_DIRS}"
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

# - Create export file(s)
# 1) For direct use from the build directory
export(TARGETS FNALCore
  NAMESPACE FNALCore::
  FILE ${PROJECT_BINARY_DIR}/FNALCoreExports.cmake
  )

# 2) For use when installed
install(EXPORT FNALCoreExports
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FNALCore-${FNALCore_VERSION}
  NAMESPACE FNALCore::
  COMPONENT Development
  )

