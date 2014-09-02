#include <map>

int main()
{
  typedef std::map<int, int> ContainerType;
  typedef std::pair<bool, ContainerType::iterator> EmplaceReturnType;

  ContainerType m;

  // pair move constructor
  EmplaceReturnType aResult = m.emplace(std::make_pair(int(1), int(2)));
  bool aValid = (aResult.first) && ((*(aResult.second)).second == 2);

  // pair converting move constructor
  EmplaceReturnType bResult = m.emplace(std::make_pair(2, 4));
  bool bValid = (bResult.first) && ((*(bResult.second)).second == 4);

  // pair template constructor
  EmplaceReturnType cResult = m.emplace(3, 6);
  bool cValid = (cResult.first) && ((*(cResult.second)).second == 6);

  return (aValid && bValid && cValid) ? 0 : 1;
}
