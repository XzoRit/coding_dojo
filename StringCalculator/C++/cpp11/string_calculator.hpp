#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/numeric.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace StringCalculator
{
  template<typename IterOut>
  void make_ints_from_str(std::string const& numsAsString, std::string const& sep, IterOut out)
  {
    using boost::algorithm::split;
    using boost::algorithm::is_any_of;

    using boost::range::transform;
    using boost::range::copy;
    using boost::adaptors::filtered;
    
    if(numsAsString.empty()) return;

    std::vector<std::string> sepNumsAsString;
    split(sepNumsAsString, numsAsString, is_any_of(sep));

    std::vector<int> ints(sepNumsAsString.size(), 0);
    transform(sepNumsAsString, ints.begin(), [](std::string const& str){ return std::stoi(str); });

    std::vector<int> negNums;
    copy(ints | filtered([](int i){ return i < 0; }), std::back_inserter(negNums));
    if(negNums.empty())
      {
        copy(ints, out);
      }
    else
      {
	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
        transform(negNums, std::ostream_iterator<std::string>(exceptTxt, " "), [](int i){ return std::to_string(i); });
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

    return boost::accumulate(ints, 0);
  }

}

#endif
