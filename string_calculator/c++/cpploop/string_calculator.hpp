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
  std::vector<int> make_ints_from_str(std::string const& numsAsString, std::string const& sep)
  {
    std::vector<int> out;
    if(numsAsString.empty()) return out;

    std::vector<std::string> sepNumsAsString;
    StrUtil::split(numsAsString, sep, std::back_inserter(sepNumsAsString));

    std::vector<int> ints;
    for(std::vector<std::string>::iterator it = sepNumsAsString.begin();
	it != sepNumsAsString.end(); it++)
      {
	int num = Convert::String::to<int>(*it);
	ints.push_back(num);
      }

    std::vector<int>::iterator i = ints.begin();
    for(i; i != ints.end(); i++)
      {
	if((*i) < 0) break;
      }
    if(ints.end() == i)
      {
	for(std::vector<int>::iterator it = ints.begin();
	    it != ints.end(); it++)
	  {
	    out.push_back(*it);
	  }
      }
    else
      {
        std::vector<int> negNums;
	for(std::vector<int>::iterator it = ints.begin();
	    it != ints.end(); it++)
	  {
	    if((*it) < 0) negNums.push_back(*it);
	  }

	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
	for(std::vector<int>::iterator it = negNums.begin();
	    it != negNums.end(); it++)
	  {
	    exceptTxt << (*it) << " ";
	  }

	throw std::invalid_argument(exceptTxt.str());
      }

    return out;
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

    std::vector<int> ints = make_ints_from_str(numsAndSep.first, numsAndSep.second);

    int sum = 0;
    for(std::vector<int>::iterator it = ints.begin();
	it != ints.end(); it++)
      {
	sum += (*it);
      }

    return sum;
  }

}

#endif
