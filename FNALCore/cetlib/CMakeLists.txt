# ======================================================================
#
# Build/install script
#
# ======================================================================
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shlib_utils.cc.in
  ${CMAKE_CURRENT_BINARY_DIR}/shlib_utils.cc @ONLY
  )

set(cetlib_PUBLIC_HDRS
  base_converter.h
  bit_manipulation.h
  canonical_number.h
  canonical_string.h
  coded_exception.h
  column_width.h
  container_algorithms.h
  cpu_timer.h
  crc32.h
  demangle.h
  exception_collector.h
  exception.h
  exempt_ptr.h
  filepath_maker.h
  filesystem.h
  getenv.h
  hypot.h
  include.h
  includer.h
  lpad.h
  make_unique.h
  map_vector.h
  maybe_ref.h
  md5.h
  name_of.h
  ntos.h
  nybbler.h
  pow.h
  registry.h
  registry_via_id.h
  rpad.h
  search_path.h
  sha1.h
  shlib_utils.h
  simple_stats.h
  split.h
  split_path.h
  ston.h
  trim.h
  value_ptr.h
  zero_init.h
  )

set(cetlib_SSL_HDRS
  polarssl/config.h
  polarssl/md5.h
  polarssl/sha1.h
  polarssl/version.h
  )

set(cetlib_SRCS
  ${CMAKE_CURRENT_BINARY_DIR}/shlib_utils.cc
  polarssl/md5.cc
  polarssl/sha1.cc
  base_converter.cc
  canonical_number.cc
  canonical_string.cc
  cpu_timer.cc
  crc32.cc
  demangle.cc
  exception.cc
  exception_collector.cc
  filepath_maker.cc
  filesystem.cc
  getenv.cc
  include.cc
  includer.cc
  lpad.cc
  nybbler.cc
  rpad.cc
  search_path.cc
  simple_stats.cc
  split_path.cc
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(cetlib OBJECT ${cetlib_PUBLIC_HDRS} ${cetlib_SSL_HDRS} ${cetlib_SRCS})

# TEMP local install of headers
install(FILES ${cetlib_PUBLIC_HDRS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/cetlib
  COMPONENT Development
  )
install(FILES ${cetlib_SSL_HDRS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/cetlib/polarssl
  COMPONENT Development
  )

