#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <lib/convert.hpp>
#include <lib/str_utils.hpp>

#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iterator>

namespace StringCalculator
{
  template<typename IterOut>
  void make_ints_from_str(std::string const& numsAsString, std::string const& sep, IterOut out)
  {
    if(numsAsString.empty()) return;

    std::vector<std::string> sepNumsAsString;
    StrUtil::split(numsAsString, sep, std::back_inserter(sepNumsAsString));

    std::vector<int> ints(sepNumsAsString.size(), 0);
    std::transform(sepNumsAsString.begin(), sepNumsAsString.end(),
		   ints.begin(), &Convert::String::to<int>);

    if(ints.end() == std::find_if(ints.begin(), ints.end(), std::bind2nd(std::less<int>(), 0)))
      {
	std::copy(ints.begin(), ints.end(), out);
      }
    else
      {
        std::vector<int> negNums;
        std::remove_copy_if(ints.begin(), ints.end(),
			    std::back_inserter(negNums), std::bind2nd(std::greater_equal<int>(), 0));

	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
	std::copy(negNums.begin(), negNums.end(),
		  std::ostream_iterator<int>(exceptTxt, " "));

	throw std::invalid_argument(exceptTxt.str());
      }
  }

  std::pair<std::string, std::string> extractSep(std::string const& parse)
  {
    static std::string::size_type const SizeOfSepSection = 4;

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
      return std::make_pair(std::string(parse.begin() + SizeOfSepSection, parse.end()), std::string(1, parse[2]));
    else
      return std::make_pair(parse, ",\n");
  }

  int add(std::string const& nums)
  {
    std::pair<std::string, std::string> const numsAndSep = extractSep(nums);

    std::vector<int> ints;
    make_ints_from_str(numsAndSep.first, numsAndSep.second, std::back_inserter(ints));

    return std::accumulate(ints.begin(), ints.end(), 0);
  }

}

#endif
