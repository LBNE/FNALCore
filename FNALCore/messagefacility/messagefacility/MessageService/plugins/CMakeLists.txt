# ======================================================================
#
# MessageService/plugins/CMakeLists.txt
#
# ======================================================================

include( BasicPlugin )

cet_make_library(
  LIBRARY_NAME MF_FileFormat
  SOURCE formatFilename.cc
  LIBRARIES MF_MessageLogger ${FHICLCPP}
  )


# ordinary destination plugins
basic_plugin( cout   mfPlugin MF_MessageLogger )
basic_plugin( cerr   mfPlugin MF_MessageLogger )
basic_plugin( file   mfPlugin MF_FileFormat    )
basic_plugin( syslog mfPlugin MF_MessageLogger )

# statistics destination plugins
basic_plugin( cout mfStatsPlugin MF_MessageLogger )
basic_plugin( cerr mfStatsPlugin MF_MessageLogger )
basic_plugin( file mfStatsPlugin MF_FileFormat )

