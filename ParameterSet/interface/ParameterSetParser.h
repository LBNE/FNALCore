#ifndef MessageFacility_ParameterSet_ParameterSetParser_h
#define MessageFacility_ParameterSet_ParameterSetParser_h

///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include "ParameterSet/interface/ParameterSet.h"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/any.hpp>

#include <string>
#include <list>

namespace mf 
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

typedef BOOST_TYPEOF(ascii::space 
    | qi::lit('#') >>*(qi::char_ - boost::spirit::eol) >> boost::spirit::eol 
    | qi::lit("//")>>*(qi::char_ - boost::spirit::eol) >> boost::spirit::eol
) skipper_type;


template <typename Iterator>
struct PSetParser 
: qi::grammar<Iterator, skipper_type>
{

  PSetParser();

  ParameterSet getPSet(std::string const & name = "");
  void print();

private:

  boost::any findPrimaryEntry(std::string const &);
  boost::any findPrimaryEntryVer(std::pair<std::string, int> const &);
  boost::any findPSetEntry(boost::any const &, std::string const &);
  boost::any findArrayElement(boost::any const &, int);

  boost::any * findPrimaryPtr(std::string const &);
  boost::any * findPSetPtr(boost::any *, std::string const &);
  boost::any * findArrayElementPtr(boost::any *, int);

  void replaceObj(boost::any *, boost::any &);

  void insertPSetEntry(ParameterSet &, std::pair<std::string, boost::any> const&);

  // data structure for primary entries
  std::vector<std::pair<std::string, boost::any> > PrimaryValues;

  // Qi parser rules
  qi::rule<Iterator, skipper_type> doc;
  qi::rule<Iterator, ParameterSet(), skipper_type> pset;
  qi::rule<Iterator, std::string() , skipper_type> key;
  qi::rule<Iterator, std::string() , skipper_type> str;
  qi::rule<Iterator, boost::any()  , skipper_type> expr;
  qi::rule<Iterator, boost::any()  , skipper_type> reference;
  qi::rule<Iterator, std::vector<boost::any>(), skipper_type> array;
  qi::rule<Iterator, std::pair<std::string, boost::any>(), skipper_type> assign;
  qi::rule<Iterator, std::pair<std::string, boost::any>(), skipper_type> unnamed_assign;
  qi::rule<Iterator, void(), qi::locals<boost::any *>, skipper_type> re_assign;
  qi::rule<Iterator, std::pair<std::string, int>(), skipper_type> primary_key;
  qi::rule<Iterator, std::string() , skipper_type> double_literal;
  qi::rule<Iterator, std::string() , skipper_type> int_literal;
  qi::rule<Iterator, int() , skipper_type> last_literal;
  qi::rule<Iterator> space;

  boost::any empty_obj;
};

class ParameterSetParser
{
private:
  ParameterSetParser() {}

public:
  static bool Parse(std::string const & fname, ParameterSet & pset);
};

}// namespace mf

#endif