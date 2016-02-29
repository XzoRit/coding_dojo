#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/reverse.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/iterator_range.hpp>
#include <iterator>
#include <sstream>
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

namespace v1
{
  using namespace std;
  using namespace std::literals::string_literals;

  class Diamond
  {
  public:
    using Lines = vector<string>;
    
    static auto letters(int amount)
    {
      return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"s.substr(0, amount);
    }
  
    static auto spaces_after(int amount)
    {
      auto spaces = Lines(amount);
      boost::transform(boost::irange(0, amount),
		       begin(spaces),
		       [](const auto& num_of_spaces)
		       { return string(num_of_spaces, ' '); });

      return spaces;
    }
  
    static auto spaces_before(int amount)
    {
      auto spaces = spaces_after(amount);
      return boost::reverse(spaces);
    }

    static auto lines(int amount)
    {
      Lines lines(amount);
      boost::transform(boost::combine(spaces_before(amount),
				      letters(amount),
				      spaces_after(amount)),
		       begin(lines),
		       [](const auto& space_letter_space)
		       {
			 string before, letter, after;
			 boost::tie(before, letter, after) = space_letter_space;
			 return before + letter + after;
		       });
      return lines;
    }

    static auto mirror_vertical(Lines lines)
    {
      for(auto& line : lines) line += string(crbegin(line) + 1, crend(line));
      return lines;
    }

    static auto mirror_horizontal(Lines lines)
    {
      lines.reserve(2 * lines.size() - 1);
      copy(++crbegin(lines), crend(lines),
	   back_inserter(lines));
      return lines;
    }

    static auto all_lines(int amount)
    {
      return mirror_horizontal(mirror_vertical(lines(amount)));
    }

    static auto char_to_num(char c)
    {
      return c - 'A' + 1;
    }

    static auto print(char c)
    {
      const auto lines = all_lines(char_to_num(c));
      return boost::accumulate(lines, ""s,
		      [](const auto& diamond, const auto& line)
		      {
			return diamond + line + '\n';
		      });
    }
  };
  
  TEST_CASE("v1: letters")
  {
    CHECK(Diamond::letters(1) == "A");
    CHECK(Diamond::letters(2) == "AB");
    CHECK(Diamond::letters(3) == "ABC");
  }

  TEST_CASE("v1: spaces_after")
  {
    CHECK(Diamond::spaces_after(1) == (Diamond::Lines{""}));
    CHECK(Diamond::spaces_after(2) == (Diamond::Lines{"", " "}));
    CHECK(Diamond::spaces_after(3) == (Diamond::Lines{"", " ", "  "}));
  }

  TEST_CASE("v1: spaces_before")
  {
    CHECK(Diamond::spaces_before(1) == (Diamond::Lines{""}));
    CHECK(Diamond::spaces_before(2) == (Diamond::Lines{" ", ""}));
    CHECK(Diamond::spaces_before(3) == (Diamond::Lines{"  ", " ", ""}));
  }

  TEST_CASE("v1: lines")
  {
    CHECK(Diamond::lines(1) == (Diamond::Lines{"A"}));
    CHECK(Diamond::lines(2) == (Diamond::Lines{" A", "B "}));
    CHECK(Diamond::lines(3) == (Diamond::Lines{"  A", " B ", "C  "}));
  }

  TEST_CASE("v1: mirror_vertical")
  {
    CHECK(Diamond::mirror_vertical(Diamond::lines(1)) == (Diamond::Lines{"A"}));
    CHECK(Diamond::mirror_vertical(Diamond::lines(2)) == (Diamond::Lines{" A ", "B B"}));
    CHECK(Diamond::mirror_vertical(Diamond::lines(3)) == (Diamond::Lines{"  A  ", " B B ", "C   C"}));
  }

  TEST_CASE("v1: mirror_horizontal")
  {
    CHECK(Diamond::mirror_horizontal(Diamond::lines(1)) == (Diamond::Lines{"A"}));
    CHECK(Diamond::mirror_horizontal(Diamond::lines(2)) == (Diamond::Lines{" A", "B ", " A"}));
    CHECK(Diamond::mirror_horizontal(Diamond::lines(3)) == (Diamond::Lines{"  A", " B ", "C  ", " B ", "  A"}));
  }

  TEST_CASE("v1: all_lines")
  {
    CHECK(Diamond::all_lines(1) == (Diamond::Lines{"A"}));
    CHECK(Diamond::all_lines(2) == (Diamond::Lines{" A ", "B B", " A "}));
    CHECK(Diamond::all_lines(3) == (Diamond::Lines{"  A  ", " B B ", "C   C", " B B ", "  A  "}));
  }

  TEST_CASE("v1: char_to_num")
  {
    CHECK(Diamond::char_to_num('A') == 1);
    CHECK(Diamond::char_to_num('B') == 2);
    CHECK(Diamond::char_to_num('C') == 3);
  }

  TEST_CASE("v1: print")
  {
    CHECK(Diamond::print('A') == "A\n");
    CHECK(Diamond::print('B') == " A \nB B\n A \n");
    CHECK(Diamond::print('C') == "  A  \n B B \nC   C\n B B \n  A  \n");
  }
}

namespace v2
{
  using std::string;
  using std::vector;
  using std::ostringstream;
  using std::ostream_iterator;
  using boost::tuple;
  using boost::tie;
  using boost::combine;
  using boost::irange;
  using boost::transform;
  using boost::reverse;
  using boost::copy;
  using boost::for_each;
  
  class Diamond
  {
  public:
    typedef vector<string> Lines;
    static string letters(int amount);
    static Lines spaces_after(int amount);
    static Lines spaces_before(int amount);
    static Lines lines(int amount);
    static Lines mirror_vertical(Lines lines);
    static Lines mirror_horizontal(Lines lines);
    static Lines all_lines(int amount);
    static int char_to_num(char c);
    static string print(char c);
  };
  
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
    Lines spaces = Lines(amount);
    transform(irange(0, amount),
	      spaces.begin(),
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
    Lines lines(amount);
    transform(combine(spaces_before(amount),
		      letters(amount),
		      spaces_after(amount)),
	      lines.begin(),
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
    copy(++lines.rbegin(), lines.rend(),
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

  TEST_CASE("v2: letters")
  {
    CHECK(Diamond::letters(1) == "A");
    CHECK(Diamond::letters(2) == "AB");
    CHECK(Diamond::letters(3) == "ABC");
  }

  TEST_CASE("v2: spaces_after")
  {
    CHECK(Diamond::spaces_after(1) == (Diamond::Lines{""}));
    CHECK(Diamond::spaces_after(2) == (Diamond::Lines{"", " "}));
    CHECK(Diamond::spaces_after(3) == (Diamond::Lines{"", " ", "  "}));
  }

  TEST_CASE("v2: spaces_before")
  {
    CHECK(Diamond::spaces_before(1) == (Diamond::Lines{""}));
    CHECK(Diamond::spaces_before(2) == (Diamond::Lines{" ", ""}));
    CHECK(Diamond::spaces_before(3) == (Diamond::Lines{"  ", " ", ""}));
  }

  TEST_CASE("v2: lines")
  {
    CHECK(Diamond::lines(1) == (Diamond::Lines{"A"}));
    CHECK(Diamond::lines(2) == (Diamond::Lines{" A", "B "}));
    CHECK(Diamond::lines(3) == (Diamond::Lines{"  A", " B ", "C  "}));
  }

  TEST_CASE("v2: mirror_vertical")
  {
    CHECK(Diamond::mirror_vertical(Diamond::lines(1)) == (Diamond::Lines{"A"}));
    CHECK(Diamond::mirror_vertical(Diamond::lines(2)) == (Diamond::Lines{" A ", "B B"}));
    CHECK(Diamond::mirror_vertical(Diamond::lines(3)) == (Diamond::Lines{"  A  ", " B B ", "C   C"}));
  }

  TEST_CASE("v2: mirror_horizontal")
  {
    CHECK(Diamond::mirror_horizontal(Diamond::lines(1)) == (Diamond::Lines{"A"}));
    CHECK(Diamond::mirror_horizontal(Diamond::lines(2)) == (Diamond::Lines{" A", "B ", " A"}));
    CHECK(Diamond::mirror_horizontal(Diamond::lines(3)) == (Diamond::Lines{"  A", " B ", "C  ", " B ", "  A"}));
  }

  TEST_CASE("v2: all_lines")
  {
    CHECK(Diamond::all_lines(1) == (Diamond::Lines{"A"}));
    CHECK(Diamond::all_lines(2) == (Diamond::Lines{" A ", "B B", " A "}));
    CHECK(Diamond::all_lines(3) == (Diamond::Lines{"  A  ", " B B ", "C   C", " B B ", "  A  "}));
  }

  TEST_CASE("v2: char_to_num")
  {
    CHECK(Diamond::char_to_num('A') == 1);
    CHECK(Diamond::char_to_num('B') == 2);
    CHECK(Diamond::char_to_num('C') == 3);
  }

  TEST_CASE("v2: print")
  {
    CHECK(Diamond::print('A') == "A\n");
    CHECK(Diamond::print('B') == " A \nB B\n A \n");
    CHECK(Diamond::print('C') == "  A  \n B B \nC   C\n B B \n  A  \n");
  }
}

int main(int argc, char *argv[])
{
  int result = Catch::Session().run(argc, argv);

  if(!result)
    {
      using std::cout;
      using namespace std::literals::string_literals;
      
      for(const auto& c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ"s)
	{
	  cout << v1::Diamond::print(c) << '\n';
	  cout << v2::Diamond::print(c) << '\n';
	}
    }

  return result;
}
