#include "cetlib/PluginTypeDeducer.h"
#include "fhiclcpp/ParameterSet.h"

#include "messagefacility/MessageService/ELdestination.h"
#include "messagefacility/MessageService/ELstatistics.h"

#include <iostream>
#include <memory>

using mf::service::ELstatistics;
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

extern "C" {

  std::unique_ptr<ELstatistics> makePlugin( const std::string&,
                   const fhicl::ParameterSet& pset) {

    return ::make_unique<ELstatistics>( pset, std::cout );

  }

}

DEFINE_BASIC_PLUGINTYPE_FUNC(mf::service::ELdestination)
