#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/numeric.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iterator>

namespace StringCalculator
{
template<typename IterOut>
auto make_ints_from_str(std::string const& numsAsString, std::string const& sep,
                        IterOut out) -> void
{
    using boost::algorithm::split;
    using boost::algorithm::is_any_of;

    using boost::range::transform;
    using boost::range::copy;
    using boost::range::find_if;
    using boost::adaptors::filtered;

    if(numsAsString.empty()) return;

    std::vector<std::string> sepNumsAsString{};
    split(sepNumsAsString, numsAsString, is_any_of(sep));

    std::vector<int> ints(sepNumsAsString.size(), 0);
    transform(sepNumsAsString, std::begin(ints), [](std::string const & str)
    {
        return std::stoi(str);
    });

    auto checkForNegNums = [](int i)
    {
        return i < 0;
    };
    if(find_if(ints, checkForNegNums) == std::end(ints))
    {
        copy(ints, out);
    }
    else
    {
        std::vector<int> negNums{};
        copy(ints | filtered(checkForNegNums), std::back_inserter(negNums));

        std::ostringstream exceptTxt{};
        exceptTxt << "Negative numbers not allowed: ";
        copy(negNums, std::ostream_iterator<int>(exceptTxt, " "));
        throw std::invalid_argument{exceptTxt.str()};
    }
}

auto extractSep(std::string const& parse) -> std::pair<std::string, std::string>
{
    static auto const SizeOfSepSection = std::string::size_type{4};

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
        return std::make_pair(std::string(parse.begin() + SizeOfSepSection, parse.end()), std::string(1, parse[2]));
    else
        return std::make_pair(parse, ",\n");
}

auto add(std::string const& nums) -> int
{
    auto const numsAndSep = extractSep(nums);

    std::vector<int> ints{};
    make_ints_from_str(numsAndSep.first, numsAndSep.second, std::back_inserter(ints));

    return boost::accumulate(ints, 0);
}

}

#endif
