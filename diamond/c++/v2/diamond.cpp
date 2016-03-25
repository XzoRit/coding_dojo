#include "diamond.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/reverse.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/iterator_range.hpp>
#include <sstream>
#include <string>
#include <iterator>

namespace v2
{
  using std::string;
  using std::vector;
  using std::back_inserter;
  using std::ostringstream;
  using std::ostream_iterator;
  
  using boost::tuple;
  using boost::tie;
  using boost::irange;
  using boost::transform;
  using boost::reverse;
  using boost::for_each;
  using boost::copy;
  using boost::combine;
  using boost::make_iterator_range;
  
  static string create_whitespaces(int amount)
  {
    return string(amount, ' ');
  }
    
  static string create_line(const tuple<string, char, string>& space_letter_space)
  {
    string before, letter, after;
    tie(before, letter, after) = space_letter_space;
    return before + letter + after;
  }

  static void append_reversed(string& line)
  {
    line += string(line.rbegin() + 1, line.rend());
  }
  
  string Diamond::letters(int amount)
  {
    return string("ABCDEFGHIJKLMNOPQRSTUVWXYZ").substr(0, amount);
  }

  Diamond::Lines Diamond::spaces_after(int amount)
  {
    Lines spaces;
    spaces.reserve(amount);
    transform(irange(0, amount),
	      back_inserter(spaces),
	      &create_whitespaces);
    return spaces;
  }
  
  Diamond::Lines Diamond::spaces_before(int amount)
  {
    Lines spaces = spaces_after(amount);
    return reverse(spaces);
  }

  Diamond::Lines Diamond::lines(int amount)
  {
    Lines lines;
    lines.reserve(amount);
    transform(combine(spaces_before(amount),
		      letters(amount),
		      spaces_after(amount)),
	      back_inserter(lines),
	      &create_line);
    return lines;
  }

  Diamond::Lines Diamond::mirror_vertical(Diamond::Lines lines)
  {
    for_each(lines, &append_reversed);
    return lines;
  }

  Diamond::Lines Diamond::mirror_horizontal(Diamond::Lines lines)
  {
    lines.reserve(2 * lines.size() - 1);
    copy(make_iterator_range(++lines.rbegin(), lines.rend()),
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

  string Diamond::print(char c)
  {
    Lines lines = all_lines(char_to_num(c));
    ostringstream o;
    copy(lines,
	 ostream_iterator<string>(o, "\n"));
    return o.str();
  }
}
