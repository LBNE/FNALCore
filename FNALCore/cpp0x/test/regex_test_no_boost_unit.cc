// ======================================================================
//
// test "regex" header
//
// ======================================================================

#include "boost/regex.hpp"
#include <string>

int main(int, char **)
{
  std::string  str("Hello world");
  boost::regex   rx("ello");

  assert( boost::regex_search(str.begin(), str.end(), rx) );
  assert( ! boost::regex_match(str.begin(), str.end(), rx) );
}
