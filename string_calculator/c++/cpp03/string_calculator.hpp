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
std::pair<std::string, std::string> extractSep(std::string const& parse)
{
    static std::string::size_type const SizeOfSepSection = 4;

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
        return std::make_pair(std::string(parse.begin() + SizeOfSepSection,
                                          parse.end()), std::string(1, parse[2]));
    else
        return std::make_pair(parse, ",\n");
}

int add(std::string const& nums)
{
    if(nums.empty()) return 0;

    std::pair<std::string, std::string> const numsAndSep = extractSep(nums);

    std::vector<std::string> sepNumsAsString;
    StrUtil::split(numsAndSep.first, numsAndSep.second,
                   std::back_inserter(sepNumsAsString));

    std::vector<int> ints(sepNumsAsString.size(), 0);
    std::transform(sepNumsAsString.begin(), sepNumsAsString.end(),
                   ints.begin(), &Convert::String::to<int>);

    std::vector<int>::iterator p = std::partition(ints.begin(), ints.end(),
                                   std::bind2nd(std::less<int>(), 0));

    if(p == ints.begin())
    {
        return std::accumulate(ints.begin(), ints.end(), 0);
    }
    else
    {
        std::vector<int> negNums;
        std::copy(ints.begin(), p, std::back_inserter(negNums));

        std::ostringstream exceptTxt;
        exceptTxt << "Negative numbers not allowed: ";
        std::copy(negNums.begin(), negNums.end(),
                  std::ostream_iterator<int>(exceptTxt, " "));

        throw std::invalid_argument(exceptTxt.str());
    }
}

}

#endif
