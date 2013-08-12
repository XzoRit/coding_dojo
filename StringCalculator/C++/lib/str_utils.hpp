#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <string>
#include <algorithm>

namespace StrUtil
{
  template<typename IterIn1, typename IterIn2, typename IterOut>
  void split(IterIn1 begin, IterIn1 end, IterIn2 sepBegin, IterIn2 sepEnd, IterOut out)
  {
    typedef typename IterOut::container_type::value_type value_type;

    IterIn1 sepIt = std::find_first_of(begin, end, sepBegin, sepEnd);
    if(sepIt == end)
      {
        *out = value_type(begin, end);
        return;
      }

    IterIn1 startIt = begin;
    do
      {
        *out++ = value_type(startIt, sepIt);
	std::advance(sepIt, 1);
        startIt = sepIt;
        sepIt = std::find_first_of(startIt, end, sepBegin, sepEnd);
      } while(sepIt != end);
    *out = value_type(startIt, end);
  }

  template<typename IterOut>
  void split(std::string const& txt, std::string const& sep, IterOut out)
  {
    split(txt.begin(), txt.end(), sep.begin(), sep.end(), out);
  }

}

#endif
