#pragma once

#include <range/v3/all.hpp>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace StringCalculator
{
using namespace std::string_literals;

// template<typename IterOut>
// auto make_ints_from_str(std::string const& numsAsString, std::string const&
// sep,
//                         IterOut out) -> void
// {
//     using boost::algorithm::split;
//     using boost::algorithm::is_any_of;

//     using boost::range::transform;
//     using boost::range::copy;
//     using boost::range::find_if;
//     using boost::adaptors::filtered;

//     if(numsAsString.empty()) return;

//     std::vector<std::string> sepNumsAsString{};
//     split(sepNumsAsString, numsAsString, is_any_of(sep));

//     std::vector<int> ints(sepNumsAsString.size(), 0);
//     transform(sepNumsAsString, std::begin(ints), [](std::string const & str)
//     {
//         return std::stoi(str);
//     });

//     auto checkForNegNums = [](int i)
//     {
//         return i < 0;
//     };
//     if(find_if(ints, checkForNegNums) == std::end(ints))
//     {
//         copy(ints, out);
//     }
//     else
//     {
//         std::vector<int> negNums{};
//         copy(ints | filtered(checkForNegNums), std::back_inserter(negNums));

//         std::ostringstream exceptTxt{};
//         exceptTxt << "Negative numbers not allowed: ";
//         copy(negNums, std::ostream_iterator<int>(exceptTxt, " "));
//         throw std::invalid_argument{exceptTxt.str()};
//     }
// }

using boost::algorithm::is_any_of;
using boost::algorithm::split;

inline const auto sumNonNegatives = [](const auto& ints) {
    auto negs = ranges::filter_view(ints, [](auto i){ return i < 0; });
    if (negs.empty()) return ranges::accumulate(ints, 0);
    auto s = ranges::accumulate(negs, ""s, [](auto s, auto i){ return s + " " + std::to_string(i); });
    throw std::invalid_argument{"negatives not allowed"s + s};
};

inline const auto extractNumsAndSep = [](const auto& parse) -> std::pair<std::string, std::string> {
  constexpr auto SizeOfSepSection{ 4 };

  if (parse.size() >= SizeOfSepSection && parse[0] == '/')
    return { { begin(parse) + SizeOfSepSection, end(parse) }, { 1, parse[2] } };
  else
    return { parse, ",\n"s };
};

inline const auto add = [](const auto& addStr) {
  if (addStr.empty())
    return 0;

  auto [nums, sep] = extractNumsAndSep(addStr);

  std::vector<std::string> separatedNums{};
  split(separatedNums, nums, is_any_of(sep));

  auto ints = ranges::views::transform(
    separatedNums, [](const auto& a) { return std::stoi(a); });

  return sumNonNegatives(ints);
};
}
