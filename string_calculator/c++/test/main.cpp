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


#include <lib/convert.hpp>

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <vector>
#include <iterator>
#include <limits>

int main(int argc, char* const argv[])
{
  int result = Catch::Session().run(argc, argv);
  
  return result;
}

using namespace StringCalculator;

TEST_CASE("calculate the sum from a long string pretty often", "[performance]")
{
  int const length = 1000;
  std::vector<int> results(length, 0);
  for(int i = 0; i < length; ++i)
    {
      results[i] = add(numsAsString);
    }
  CAPTURE(results[0]);
}

TEST_CASE("extractSep", "[extractSep]")
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

SCENARIO("add with empty string returns 0", "[add]")
{
  GIVEN("an empty string")
    {
      std::string const empty("");
      WHEN("passed to add")
	{
	  int const result = add(empty);
	  THEN("zero shall be returned")
	    {
	      REQUIRE(result == 0);
	    }
	}
    }
}

TEST_CASE("add with one number string returns that number", "[add]")
{
  CHECK(StringCalculator::add("0")            == 0);
  CHECK(StringCalculator::add("1234567890")   == 1234567890);

  int const max = std::numeric_limits<int>::max();
  std::string const maxStr = Convert::Int::to<std::string>(max);
  CHECK(StringCalculator::add(maxStr) == max);
}

TEST_CASE("add with two nubers returns their sum", "[add]")
{
  CHECK(StringCalculator::add("0,0") == 0);
  CHECK(StringCalculator::add("0,1") == 1);
  CHECK(StringCalculator::add("1,1") == 2);
  CHECK(StringCalculator::add("1,2") == 3);

  int const max = std::numeric_limits<int>::max() - 1;
  int const halfMax = max/2;
  std::string halfMaxStr = Convert::Int::to<std::string>(halfMax);
  std::string halfAndhalf = halfMaxStr + "," + halfMaxStr;

  CHECK(StringCalculator::add(halfAndhalf) == max);
}

TEST_CASE("add with many numbers returns their sum", "[add]")
{
  CHECK(StringCalculator::add("0,0,0,0") == 0);
  CHECK(StringCalculator::add("0,1,0,2") == 3);
  CHECK(StringCalculator::add("1,2,3,4,5,6,7,8,9,0") == 45);
  CHECK(StringCalculator::add("11,12,13,14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000,1000000") == 3000000);
}

TEST_CASE("add with many numbers and \\n as seperator returns their sum", "[add]")
{
  CHECK(StringCalculator::add("0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("0\n1\n0\n2") == 3);
  CHECK(StringCalculator::add("1\n2\n3\n4\n5\n6\n7\n8\n9\n0") == 45);
  CHECK(StringCalculator::add("11\n12\n13\n14\n15") == 65);
  CHECK(StringCalculator::add("1000000\n1000000\n1000000") == 3000000);
}

TEST_CASE("add with many numbers and \\n or , as seperator returns their sum", "[add]")
{
  CHECK(StringCalculator::add("0\n0,0\n0") == 0);
  CHECK(StringCalculator::add("0,1\n0,2") == 3);
  CHECK(StringCalculator::add("1\n2\n3,4,5\n6\n7,8\n9\n0") == 45);
  CHECK(StringCalculator::add("11,12\n13\n14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000\n1000000") == 3000000);
}

TEST_CASE("add with seperator specification and many number returns their sum", "[add]")
{
  CHECK(StringCalculator::add("//\n\n0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("//,\n0,1,22") == 23);
  CHECK(StringCalculator::add("//\\\n11\\2\\3\\4\\5\\6\\7\\8\\9\\0") == 55);
  CHECK(StringCalculator::add("//-\n11-12-13-14-15") == 65);
  CHECK(StringCalculator::add("//:\n1000000:1000000:1000000") == 3000000);
}

TEST_CASE("add with negative numbers throws", "[add]")
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
