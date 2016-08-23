#include "v1/diamond.hpp"
#include "v2/diamond.hpp"
#include "v3/diamond.hpp"
#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_COLOUR_NONE
#include <catch.hpp>
#include <iostream>
#include <string>

namespace v1
{
  namespace test
  {
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
}

#include <boost/assign.hpp>

namespace v2
{
  namespace test
  {
    using boost::assign::list_of;

    TEST_CASE("v2: letters")
    {
      CHECK(Diamond::letters(1) == "A");
      CHECK(Diamond::letters(2) == "AB");
      CHECK(Diamond::letters(3) == "ABC");
    }

    TEST_CASE("v2: spaces_after")
    {
      CHECK(Diamond::spaces_after(1) == list_of(""));
      CHECK(Diamond::spaces_after(2) == list_of("")(" "));
      CHECK(Diamond::spaces_after(3) == list_of("")(" ")("  "));
    }

    TEST_CASE("v2: spaces_before")
    {
      Diamond::Lines expected;
      CHECK(Diamond::spaces_before(1) == list_of(""));
      CHECK(Diamond::spaces_before(2) == list_of(" ")(""));
      CHECK(Diamond::spaces_before(3) == list_of("  ")(" ")(""));
    }

    TEST_CASE("v2: lines")
    {
      CHECK(Diamond::lines(1) == list_of("A"));
      CHECK(Diamond::lines(2) == list_of(" A")("B "));
      CHECK(Diamond::lines(3) == list_of("  A")(" B ")("C  "));
    }

    TEST_CASE("v2: mirror_vertical")
    {
      CHECK(Diamond::mirror_vertical(Diamond::lines(1)) == list_of("A"));
      CHECK(Diamond::mirror_vertical(Diamond::lines(2)) == list_of(" A ")("B B"));
      CHECK(Diamond::mirror_vertical(Diamond::lines(3)) == list_of("  A  ")(" B B ")("C   C"));
    }

    TEST_CASE("v2: mirror_horizontal")
    {
      CHECK(Diamond::mirror_horizontal(Diamond::lines(1)) == list_of("A"));
      CHECK(Diamond::mirror_horizontal(Diamond::lines(2)) == list_of(" A")("B ")(" A"));
      CHECK(Diamond::mirror_horizontal(Diamond::lines(3)) == list_of("  A")(" B ")("C  ")(" B ")("  A"));
    }

    TEST_CASE("v2: all_lines")
    {
      CHECK(Diamond::all_lines(1) == list_of("A"));
      CHECK(Diamond::all_lines(2) == list_of(" A ")("B B")(" A "));
      CHECK(Diamond::all_lines(3) == list_of("  A  ")(" B B ")("C   C")(" B B ")("  A  "));
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
}

namespace v3
{
  namespace test
  {
    TEST_CASE("v3: letters")
    {
      CHECK(Diamond::letters(1) == "A");
      CHECK(Diamond::letters(2) == "AB");
      CHECK(Diamond::letters(3) == "ABC");
    }

    TEST_CASE("v3: spaces_after")
    {
      CHECK(Diamond::spaces_after(1) == (Diamond::Lines{""}));
      CHECK(Diamond::spaces_after(2) == (Diamond::Lines{"", " "}));
      CHECK(Diamond::spaces_after(3) == (Diamond::Lines{"", " ", "  "}));
    }

    TEST_CASE("v3: spaces_before")
    {
      CHECK(Diamond::spaces_before(1) == (Diamond::Lines{""}));
      CHECK(Diamond::spaces_before(2) == (Diamond::Lines{" ", ""}));
      CHECK(Diamond::spaces_before(3) == (Diamond::Lines{"  ", " ", ""}));
    }

    TEST_CASE("v3: lines")
    {
      CHECK(Diamond::lines(1) == (Diamond::Lines{"A"}));
      CHECK(Diamond::lines(2) == (Diamond::Lines{" A", "B "}));
      CHECK(Diamond::lines(3) == (Diamond::Lines{"  A", " B ", "C  "}));
    }

    TEST_CASE("v3: mirror_vertical")
    {
      CHECK(Diamond::mirror_vertical(Diamond::lines(1)) == (Diamond::Lines{"A"}));
      CHECK(Diamond::mirror_vertical(Diamond::lines(2)) == (Diamond::Lines{" A ", "B B"}));
      CHECK(Diamond::mirror_vertical(Diamond::lines(3)) == (Diamond::Lines{"  A  ", " B B ", "C   C"}));
    }

    TEST_CASE("v3: mirror_horizontal")
    {
      CHECK(Diamond::mirror_horizontal(Diamond::lines(1)) == (Diamond::Lines{"A"}));
      CHECK(Diamond::mirror_horizontal(Diamond::lines(2)) == (Diamond::Lines{" A", "B ", " A"}));
      CHECK(Diamond::mirror_horizontal(Diamond::lines(3)) == (Diamond::Lines{"  A", " B ", "C  ", " B ", "  A"}));
    }

    TEST_CASE("v3: all_lines")
    {
      CHECK(Diamond::all_lines(1) == (Diamond::Lines{"A"}));
      CHECK(Diamond::all_lines(2) == (Diamond::Lines{" A ", "B B", " A "}));
      CHECK(Diamond::all_lines(3) == (Diamond::Lines{"  A  ", " B B ", "C   C", " B B ", "  A  "}));
    }

    TEST_CASE("v3: char_to_num")
    {
      CHECK(Diamond::char_to_num('A') == 1);
      CHECK(Diamond::char_to_num('B') == 2);
      CHECK(Diamond::char_to_num('C') == 3);
    }

    TEST_CASE("v3: print")
    {
      CHECK(Diamond::print('A') == "A\n");
      CHECK(Diamond::print('B') == " A \nB B\n A \n");
      CHECK(Diamond::print('C') == "  A  \n B B \nC   C\n B B \n  A  \n");
    }
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
      	  // cout << v1::Diamond::print(c) << '\n';
      	  // cout << v2::Diamond::print(c) << '\n';
      	  // cout << v3::Diamond::print(c) << '\n';
      	}
    }

  return result;
}
