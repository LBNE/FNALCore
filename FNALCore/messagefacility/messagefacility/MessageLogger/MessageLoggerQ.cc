#include "messagefacility/MessageLogger/MessageLoggerQ.h"
#include "messagefacility/MessageLogger/AbstractMLscribe.h"
#include "messagefacility/MessageLogger/ConfigurationHandshake.h"
#include "messagefacility/Utilities/exception.h"
#include "messagefacility/MessageLogger/ErrorObj.h"

#include <cstring>
#include <iostream>

//////////////////////////////////////////////////////////////////////
//
// DO NOT replace the internal memcpy() calls by assignment or by
// any other form of copying unless you first understand in depth
// all of the alignment issues involved
//
//////////////////////////////////////////////////////////////////////

// Change Log
//
// 1 - 3/9/07 mf
//      Addition of JOB command, to be used by --jobreport
// 2 - 6/19/07 mf
//      Addition of MOD command, to be used by --mode
// 3 - 7/24/07 mf
//      Addition of SHT command, to be used when no .cfg file was given
// 4 - 7/25/07 mf
//      Change of each mommand function to start with MLq, e.g. MLqLOG
// 5 - 8/7/07 mf
//      Addition of FLS command, to be used by FlushMessageLog
// 6 - 8/16/07 mf
//      Addition of GRP command, to be used by GroupLogStatistics
// 7 - 6/18/08 mf
//      Addition of JRS command, to be used by SummarizeInJobReport
// 8 - 10/24/08 mf
//      Support for singleThread
// 9 - 8/6/09  mf
//      handshaked() method to support cleaner abstraction of scribes
// 10 - 8/7/09  mf, crj
//      major down-functioning:  the actual dealing with buffer of the
//      SingleConsumerQ is moved off into MainThreadMLscribe.
// 11 - 8/10/09 mf, cdj
//      StandAloneScribe - a class that gets installed as the scribe if
//      no presence is created at all.  Enables easy stand-alone use of the
//      logger
// 12 - 8/10/09 mf, cdj
//      Removal of use of singleThread from this class - does not need it any
//      longer
// 13 - 8/10/09 mf
//      Special control of standAlone message logging
// 14 - 8/12/09 mf, cdj
//      Better ownership management of standAlone or other scribe
// 15 - 05/12/10 ql
//      Addition of SWC command, to be used by SwithChannel

using namespace mf;

// ChangeLog 11
namespace {
   class StandAloneScribe : public mf::service::AbstractMLscribe {

   public:
      StandAloneScribe() {}

      // ---------- member functions ---------------------------
      virtual
      void  runCommand(mf::MessageLoggerQ::OpCode  opcode, void * operand);

   private:
      StandAloneScribe(const StandAloneScribe&); // stop default

      const StandAloneScribe& operator=(const StandAloneScribe&); // stop default

      // ---------- member data --------------------------------

   };

   void
   StandAloneScribe::runCommand(mf::MessageLoggerQ::OpCode  opcode, void * operand) {
      //even though we don't print, have to clean up memory
      switch (opcode) {
         case mf::MessageLoggerQ::LOG_A_MESSAGE: {
            mf::ErrorObj *  errorobj_p = static_cast<mf::ErrorObj *>(operand);
            if ( MessageLoggerQ::ignore                         // ChangeLog 13
                        (errorobj_p->xid().severity, errorobj_p->xid().id) ) {
              delete errorobj_p;
              break;
            }
            if (errorobj_p->is_verbatim()) {
              std::cerr<< errorobj_p->fullText() << std::endl;
            } else {
              std::cerr<< "%MSG" << errorobj_p->xid().severity.getSymbol()
                       << " " << errorobj_p->xid().id << ": \n"
                       << errorobj_p->fullText() << "\n"
                       << "%MSG"
                       << std::endl;
            }
            delete errorobj_p;
            break;
         }
         case mf::MessageLoggerQ::JOBREPORT:
         case mf::MessageLoggerQ::JOBMODE:
         case mf::MessageLoggerQ::GROUP_STATS:
         {
            std::string* string_p = static_cast<std::string*> (operand);
            delete string_p;
            break;
         }
         default:
            break;
      }
   }

  std::shared_ptr<StandAloneScribe> & obtainStandAloneScribePtr() {
    static auto standAloneScribe_ptr = std::make_shared<StandAloneScribe>();
    return standAloneScribe_ptr;
  }


} // end of anonymous namespace

std::shared_ptr<mf::service::AbstractMLscribe>
  MessageLoggerQ::mlscribe_ptr = obtainStandAloneScribePtr();
                                // changeLog 8, 11, 14

MessageLoggerQ::MessageLoggerQ()
{ }


MessageLoggerQ::~MessageLoggerQ()
{ }


MessageLoggerQ *
  MessageLoggerQ::instance()
{
  static MessageLoggerQ queue;
  return &queue;
}  // MessageLoggerQ::instance()

void
  MessageLoggerQ::setMLscribe_ptr
        (std::shared_ptr<mf::service::AbstractMLscribe> const & m) // changeLog 8, 14
{
  if (!m) {
    mlscribe_ptr = obtainStandAloneScribePtr();
  } else {
    mlscribe_ptr = m;
  }
}  // MessageLoggerQ::setMLscribe_ptr(m)

void
  MessageLoggerQ::simpleCommand(OpCode opcode, void * operand)// changeLog 8, 10
{
  mlscribe_ptr->runCommand(opcode, operand);
} // simpleCommand

void
  MessageLoggerQ::handshakedCommand(
        OpCode opcode,
        void * operand,
        std::string const & commandMnemonic )
{                                                               // Change Log 10
  try {
    mlscribe_ptr->runCommand(opcode, operand);
  }
  catch(mf::Exception& ex)
  {
    ex << "\n The preceding exception was thrown in MessageLoggerScribe\n";
    ex << "and forwarded to the main thread from the Messages thread.";
    std::cerr << "exception from MessageLoggerQ::"
              << commandMnemonic << " - exception what() is \n"
              << ex.what();
    // TODO - get the above text into the what itself
    throw ex;
  }
}  // handshakedCommand

void
  MessageLoggerQ::MLqEND()
{
  simpleCommand (END_THREAD, (void *)0);
}  // MessageLoggerQ::END()

void
  MessageLoggerQ::MLqSHT()
{
  simpleCommand (SHUT_UP, (void *)0);
}  // MessageLoggerQ::SHT()

void
  MessageLoggerQ::MLqLOG( ErrorObj * p )
{
  simpleCommand (LOG_A_MESSAGE, static_cast<void *>(p));
}  // MessageLoggerQ::LOG()


void
  MessageLoggerQ::MLqCFG( fhicl::ParameterSet * p )
{
  handshakedCommand(CONFIGURE, p, "CFG" );
}  // MessageLoggerQ::CFG()

void
MessageLoggerQ::MLqEXT( service::NamedDestination* p )
{
  simpleCommand (EXTERN_DEST, static_cast<void *>(p));
}

void
  MessageLoggerQ::MLqSUM( )
{
  simpleCommand (SUMMARIZE, 0);
}  // MessageLoggerQ::SUM()

void
  MessageLoggerQ::MLqJOB( std::string * j )
{
  simpleCommand (JOBREPORT, static_cast<void *>(j));
}  // MessageLoggerQ::JOB()

void
  MessageLoggerQ::MLqMOD( std::string * jm )
{
  simpleCommand (JOBMODE, static_cast<void *>(jm));
}  // MessageLoggerQ::MOD()


void
  MessageLoggerQ::MLqFLS(  )                    // Change Log 5
{
  // The ConfigurationHandshake, developed for synchronous CFG, contains a
  // place to convey exception information.  FLS does not need this, nor does
  // it need the parameter set, but we are reusing ConfigurationHandshake
  // rather than reinventing the mechanism.
  handshakedCommand(FLUSH_LOG_Q, 0, "FLS" );
}  // MessageLoggerQ::FLS()

void
  MessageLoggerQ::MLqGRP( std::string * cat_p )         // Change Log 6
{
  simpleCommand (GROUP_STATS, static_cast<void *>(cat_p));
}  // MessageLoggerQ::GRP()

void
  MessageLoggerQ::MLqJRS( std::map<std::string, double> * sum_p )
{
  handshakedCommand(FJR_SUMMARY, sum_p, "JRS" );
}  // MessageLoggerQ::CFG()

void
  MessageLoggerQ::MLqSWC( std::string * chanl_p )
{
  handshakedCommand(SWITCH_CHANNEL, static_cast<void *>(chanl_p), "SWC");
}  // MessageLoggerQ::SWC()

bool
  MessageLoggerQ::handshaked(MessageLoggerQ::OpCode const & op)  // changeLog 9
{
   return ( (op == CONFIGURE) || (op == FLUSH_LOG_Q) || (op == FJR_SUMMARY) );
}  // MessageLoggerQ::handshaked(op)

// change Log 13:
mf::ELseverityLevel MessageLoggerQ::threshold ("WARNING");
std::set<std::string> MessageLoggerQ::squelchSet;
void MessageLoggerQ::standAloneThreshold(std::string const & severity) {
  threshold = mf::ELseverityLevel(severity);
}
void MessageLoggerQ::squelch(std::string const & category) {
  squelchSet.insert(category);
}
bool MessageLoggerQ::ignore ( mf::ELseverityLevel const & severity,
                               std::string const & category ) {
  if ( severity < threshold ) return true;
  if ( squelchSet.count(category) > 0 ) return true;
  return false;
}
