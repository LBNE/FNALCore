# - Build messagefacility component
# This is a real mess, and we leave extensions out because it's not
# clear this is even used. Same for the classes_def.xml file
# Also not obvious if there is any split between public/private headers
# Some direct use of C++11 headers as well.

#-----------------------------------------------------------------------
# Utilities
#
set(MessageFacility_Utilities_HEADERS
  Utilities/DebugMacros.h
  Utilities/do_nothing_deleter.h
  Utilities/exception.h
  Utilities/FormatTime.h
  Utilities/JobMode.h
  Utilities/SingleConsumerQ.h
  Utilities/tinystr.h
  Utilities/tinyxml.h
  Utilities/UnixSignalHandlers.h
  )
set(MessageFacility_Utilities_SOURCES
  Utilities/DebugMacros.cc
  Utilities/exception.cc
  Utilities/FormatTime.cc
  Utilities/SingleConsumerQ.cc
  Utilities/tinyxml.cc
  Utilities/tinyxmlerror.cc
  Utilities/tinyxmlparser.cc
  Utilities/UnixSignalHandlers.cc
  )

#-----------------------------------------------------------------------
# Logger/Service
#
set(MessageService_HEADERS
  MessageService/ELadministrator.h
  MessageService/ELassertN.h
  MessageService/ELcollected.h
  MessageService/ELcontextSupplier.h
  MessageService/ELdestControl.h
  MessageService/ELdestination.h
  MessageService/ELdestMakerMacros.h
  MessageService/ELerrorList.h
  MessageService/ELfwkJobReport.h
  MessageService/ELlimitsTable.h
  MessageService/ELoutput.h
  MessageService/ELrecv.h
  MessageService/ELsender.h
  MessageService/ELset.h
  MessageService/ELstatistics.h
  MessageService/ELtsErrorLog.h
  MessageService/ELtsErrorLog.icc
  MessageService/ErrorLog.h
  MessageService/ErrorLog.icc
  MessageService/MainThreadMLscribe.h
  MessageService/MessageLoggerDefaults.h
  MessageService/MessageLogger.h
  MessageService/MessageLoggerScribe.h
  MessageService/MessageServicePresence.h
  MessageService/MsgContext.h
  MessageService/NamedDestination.h
  MessageService/Presence.h
  MessageService/SingleThreadMSPresence.h
  MessageService/ThreadQueue.h
  MessageService/ThreadSafeErrorLog.h
  )
set(MessageLogger_HEADERS
  MessageLogger/AbstractMLscribe.h
  MessageLogger/classes.h
  MessageLogger/ConfigurationHandshake.h
  MessageLogger/ELextendedID.h
  MessageLogger/ELlist.h
  MessageLogger/ELmap.h
  MessageLogger/ELseverityLevel.h
  MessageLogger/ELseverityLevel.icc
  MessageLogger/ELstring.h
  MessageLogger/ErrorObj.h
  MessageLogger/ErrorObj.icc
  MessageLogger/ErrorSummaryEntry.h
  MessageLogger/ExceptionMessages.h
  MessageLogger/JobReport.h
  MessageLogger/LoggedErrorsSummary.h
  MessageLogger/MessageDrop.h
  MessageLogger/MessageFacilityMsg.h
  MessageLogger/MessageLogger.h
  MessageLogger/MessageLoggerQ.h
  MessageLogger/MessageSender.h
  MessageLogger/SilentMLscribe.h
  MessageLogger/ThreadSafeErrorLog.icc
  )
set(MessageFacility_HEADERS ${MessageService_HEADERS} ${MessageLogger_HEADERS})

set(MessageFacility_SOURCES
  MessageService/ELadministrator.cc
  MessageService/ELcollected.cc
  MessageService/ELdestControl.cc
  MessageService/ELdestination.cc
  MessageService/ELerrorList.cc
  MessageService/ELfwkJobReport.cc
  MessageService/ELlimitsTable.cc
  MessageService/ELoutput.cc
  MessageService/ELrecv.cc
  MessageService/ELstatistics.cc
  MessageService/ELtsErrorLog.cc
  MessageService/ErrorLog.cc
  MessageService/HardwiredDefaults.cc
  MessageService/MainThreadMLscribe.cc
  MessageService/MessageLogger.cc
  MessageService/MessageLoggerDefaults.cc
  MessageService/MessageLoggerScribe.cc
  MessageService/MessageServicePresence.cc
  MessageService/MsgContext.cc
  MessageService/Presence.cc
  MessageService/SingleThreadMSPresence.cc
  MessageService/ThreadQueue.cc
  MessageLogger/AbstractMLscribe.cc
  MessageLogger/ELextendedID.cc
  MessageLogger/ELmap.cc
  MessageLogger/ELseverityLevel.cc
  MessageLogger/ELstring.cc
  MessageLogger/ErrorObj.cc
  MessageLogger/ExceptionMessages.cc
  MessageLogger/JobReport.cc
  MessageLogger/LoggedErrorsSummary.cc
  MessageLogger/MessageDrop.cc
  MessageLogger/MessageFacilityMsg.cc
  MessageLogger/MessageLogger.cc
  MessageLogger/MessageLoggerQ.cc
  MessageLogger/MessageSender.cc
  MessageLogger/SilentMLscribe.cc
  )

set_source_files_properties(${MessageFacility_HEADERS}
  PROPERTIES
    HEADER_FILE_ONLY TRUE
  )

add_library(messagefacility OBJECT
  ${MessageFacility_HEADERS}
  ${MessageFacility_SOURCES}
  ${MessageFacility_Utilities_HEADERS}
  ${MessageFacility_Utilities_SOURCES}
  )

# TEMP local install of headers
install(FILES ${MessageFacility_Utilities_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/messagefacility/Utilities
  COMPONENT Development
  )
install(FILES ${MessageService_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/messagefacility/MessageService
  COMPONENT Development
  )
install(FILES ${MessageLogger_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/FNALCore/messagefacility/MessageLogger
  COMPONENT Development
  )

#-----------------------------------------------------------------------
# Testing
if(FNALCore_ENABLE_TESTING)
  add_subdirectory(unittests)
endif()


