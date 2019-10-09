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

using boost::algorithm::is_any_of;
using boost::algorithm::split;

inline const auto sum_positives = [](const auto& ints) {
  auto negs = ranges::filter_view(ints, [](auto i) { return i < 0; });
  if (negs.empty())
    return ranges::accumulate(ints, 0);
  auto negs_str = ranges::accumulate(
    negs, ""s, [](auto s, auto i) { return s + " " + std::to_string(i); });
  throw std::invalid_argument{ "negatives not allowed"s + negs_str };
};

inline const auto str_to_int = [](const auto& str) {
  if (str.empty())
    return 0;
  return std::stoi(str);
};

inline const auto to_ints = [](const auto& nums) {
  return ranges::views::transform(nums, str_to_int);
};

inline const auto split_nums_by_seps = [](const auto& nums_and_seps) {
  const auto& [nums, seps] = nums_and_seps;
  std::vector<std::string> separated_nums{};
  split(separated_nums, nums, is_any_of(seps));
  return separated_nums;
};

inline const auto split_into_nums_and_seps = [](const auto& parse) -> std::pair<std::string, std::string> {
  constexpr auto size_of_seps_section{ 4 };

  if (parse.size() >= size_of_seps_section && parse[0] == '/')
    return { { begin(parse) + size_of_seps_section, end(parse) }, { 1, parse[2] } };
  else
    return { parse, ",\n"s };
};

inline const auto add = [](const auto& add_str) {
  return sum_positives(to_ints(split_nums_by_seps(split_into_nums_and_seps(add_str))));
};
}
