#include "diamond.hpp"
#include <boost/range/irange.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/combine.hpp>
#include <iterator>
#include <string>
#include <sstream>

namespace v1
{
  using namespace std::literals::string_literals;
  
  std::string Diamond::letters(int amount)
  {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"s.substr(0, amount);
  }

  Diamond::Lines Diamond::spaces_after(int amount)
  {
    auto spaces = Lines(amount);
    boost::transform(boost::irange(0, amount),
		     begin(spaces),
		     [](const auto& num_of_spaces)
		     { return std::string(num_of_spaces, ' '); });

    return spaces;
  }

  Diamond::Lines Diamond::spaces_before(int amount)
  {
    auto spaces = spaces_after(amount);
    return boost::reverse(spaces);
  }
  
  Diamond::Lines Diamond::lines(int amount)
  {
    Lines lines(amount);
    boost::transform(boost::combine(spaces_before(amount),
				    letters(amount),
				    spaces_after(amount)),
		     begin(lines),
		     [](const auto& space_letter_space)
		     {
		       std::string before, letter, after;
		       boost::tie(before, letter, after) = space_letter_space;
		       return before + letter + after;
		     });
    return lines;
  }
  
  Diamond::Lines Diamond::mirror_vertical(Lines lines)
  {
    for(auto& line : lines) line += std::string(crbegin(line) + 1, crend(line));
    return lines;
  }

  Diamond::Lines Diamond::mirror_horizontal(Lines lines)
  {
    lines.reserve(2 * lines.size() - 1);
    copy(++crbegin(lines), crend(lines),
	 back_inserter(lines));
    return lines;
  }

  Diamond::Lines Diamond::all_lines(int amount)
  {
    return mirror_horizontal(mirror_vertical(lines(amount)));
  }

  int Diamond::char_to_num(char c)
  {
    return c - 'A' + 1;
  }

  std::string Diamond::print(char c)
  {
    const auto lines = all_lines(char_to_num(c));
    return boost::accumulate(lines, ""s,
			     [](const auto& diamond, const auto& line)
			     {
			       return diamond + line + '\n';
			     });
  }
}
