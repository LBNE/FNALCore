#ifndef MessageFacility_MessageService_NamedDestination_h
#define MessageFacility_MessageService_NamedDestination_h 1

#include "messagefacility/MessageService/ELdestination.h"

#include <string>
#include <memory>

class ELdestination;

namespace mf  {
namespace service {

  class NamedDestination {
  public:
    NamedDestination( std::string const & n, ELdestination* dp ) :
        name_(n)
      , dest_p_(dp)
      {}
    std::string const & name() const {return name_;}
    std::unique_ptr<ELdestination> & dest_p() {return dest_p_;}
  private:
    std::string name_;
    std::unique_ptr<ELdestination> dest_p_;
  };
}        // end of namespace service
}       // end of namespace mf

#endif // MessageFacility_MessageService_NamedDestination_h