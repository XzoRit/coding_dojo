#include <string_calculator.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

namespace
{
using namespace std::string_literals;
using namespace StringCalculator;

TEST_CASE("add with empty string returns 0")
{
  CHECK(StringCalculator::add(""s) == 0);
}

TEST_CASE("add with one number string returns that number")
{
  CHECK(StringCalculator::add("0"s) == 0);
  CHECK(StringCalculator::add("1234567890"s) == 1234567890);
}

TEST_CASE("add with two nubers returns their sum")
{
  CHECK(StringCalculator::add("1,22"s) == 23);
  CHECK(StringCalculator::add("11,2"s) == 13);
}

TEST_CASE("add with many numbers returns their sum")
{
  CHECK(StringCalculator::add("1,22,333"s) == 356);
}

TEST_CASE("add with many numbers and \\n as seperator returns their sum")
{
  CHECK(StringCalculator::add("1\n22\n333"s) == 356);
}

TEST_CASE("add with many numbers and \\n or , as seperator returns their sum")
{
  CHECK(StringCalculator::add("1,22\n333"s) == 356);
}

TEST_CASE("add with seperator specification and many number returns their sum")
{
  CHECK(StringCalculator::add("//-\n1-22-333"s) == 356);
}

TEST_CASE("add with negative numbers throws")
{
  CHECK_THROWS_AS(StringCalculator::add("1,-1,1,-1"s), std::invalid_argument);
}

TEST_CASE(
  "add with negative numbers throws and exception text contains negative "
  "numbers")
{
  CHECK_THROWS_WITH(StringCalculator::add("1,-1,1,-1"s), "negatives not allowed -1 -1");
}
}
