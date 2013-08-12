#ifndef CONVERT_H
#define CONVERT_H

#include <string>
#include <sstream>

namespace Convert
{
  namespace String
  {
    template<typename Ret>
    Ret to(std::string const& numInStr)
    {
      std::istringstream numInStream(numInStr);
      numInStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
      int number = 0;

      numInStream >> number;
      return number;
    }
  }

  namespace Int
  {
    template<typename Ret>
    Ret to(int i)
    {
      std::ostringstream iInStream;
      iInStream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
      iInStream << i;

      return iInStream.str();
    }
  }
}

#endif
