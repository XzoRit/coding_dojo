#include <string_calculator.hpp>
#include <vector>

std::string const numsAsString =
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1,"
"1,1,1,1,1,1,1,1,1,1";

int const length = 1000;

// int main()
// {
//   std::vector<int> results(length, 0);
//   for(int i = 0; i < length; ++i)
//     {
//       results[i] = StringCalculator::add(numsAsString.c_str());
//     }

//   return results[0];
// }

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <iterator>

using namespace StringCalculator;

TEST_CASE("extractSep", "")
{
  CHECK(extractSep("//T\n").second == "T");
  CHECK(extractSep("//;\n").second == ";");
  CHECK(extractSep("//-\n").second == "-");
  CHECK(extractSep("//a\n").second == "a");
  CHECK(extractSep("///\n").second == "/");
  CHECK(extractSep("//\n\n").second == "\n");

  CHECK(extractSep("").second == ",\n");
  CHECK(extractSep("/").second == ",\n");
  CHECK(extractSep("//").second == ",\n");
  CHECK(extractSep("\n").second == ",\n");
  CHECK(extractSep("//\n").second == ",\n");
}

TEST_CASE("add(\"\")", "When called with an empty text returns 0")
{
  CHECK(StringCalculator::add("") == 0);
}

TEST_CASE("add(\"one number\")", "When called with one number returns it")
{
  CHECK(StringCalculator::add("0")     == 0);
  CHECK(StringCalculator::add("1")     == 1);
  CHECK(StringCalculator::add("12")    == 12);
  CHECK(StringCalculator::add("123")   == 123);
  CHECK(StringCalculator::add("1234")  == 1234);
  CHECK(StringCalculator::add("12345") == 12345);
}

TEST_CASE("add(\"1st,2nd\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0,0") == 0);
  CHECK(StringCalculator::add("0,1") == 1);
  CHECK(StringCalculator::add("1,2") == 3);
  CHECK(StringCalculator::add("11,12") == 23);
  CHECK(StringCalculator::add("12,34") == 46);
  CHECK(StringCalculator::add("1000000,1000000") == 2000000);
}

TEST_CASE("add(\"1st,2nd,...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0,0,0,0") == 0);
  CHECK(StringCalculator::add("0,1,0,2") == 3);
  CHECK(StringCalculator::add("1,2,3,4,5,6,7,8,9,0") == 45);
  CHECK(StringCalculator::add("11,12,13,14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000,1000000") == 3000000);
}

TEST_CASE("add(\"1st\\n2nd\\n...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("0\n1\n0\n2") == 3);
  CHECK(StringCalculator::add("1\n2\n3\n4\n5\n6\n7\n8\n9\n0") == 45);
  CHECK(StringCalculator::add("11\n12\n13\n14\n15") == 65);
  CHECK(StringCalculator::add("1000000\n1000000\n1000000") == 3000000);
}

TEST_CASE("add(\"1st(,\\n)2nd(,\\n)...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0\n0,0\n0") == 0);
  CHECK(StringCalculator::add("0,1\n0,2") == 3);
  CHECK(StringCalculator::add("1\n2\n3,4,5\n6\n7,8\n9\n0") == 45);
  CHECK(StringCalculator::add("11,12\n13\n14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000\n1000000") == 3000000);
}

TEST_CASE("add(With Sep Spec line)", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("//\n\n0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("//,\n0,1,22") == 23);
  CHECK(StringCalculator::add("//\\\n11\\2\\3\\4\\5\\6\\7\\8\\9\\0") == 55);
  CHECK(StringCalculator::add("//-\n11-12-13-14-15") == 65);
  CHECK(StringCalculator::add("//:\n1000000:1000000:1000000") == 3000000);
    }

TEST_CASE("add(With Neg Nums)", "When called with two number returns sum")
{
  REQUIRE_THROWS_AS(StringCalculator::add("1,-1,1,-1"), std::invalid_argument);
  try
    {
      StringCalculator::add("1,-1,1,-1");
    }
  catch(std::invalid_argument const& e)
    {
      CHECK(e.what() == std::string("Negative numbers not allowed: -1 -1 "));
    }
}
