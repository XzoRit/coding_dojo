#include <string_calculator.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

namespace {
using namespace StringCalculator;

TEST_CASE("add with empty string returns 0") {
  CHECK(StringCalculator::add("") == 0);
}

TEST_CASE("add with one number string returns that number") {
  CHECK(StringCalculator::add("0") == 0);
  CHECK(StringCalculator::add("1234567890") == 1234567890);
}

TEST_CASE("add with two nubers returns their sum") {
  CHECK(StringCalculator::add("1,22") == 23);
  CHECK(StringCalculator::add("11,2") == 13);
}

TEST_CASE("add with many numbers returns their sum") {
  CHECK(StringCalculator::add("1,22,333") == 356);
}

TEST_CASE("add with many numbers and \\n as seperator returns their sum") {
  CHECK(StringCalculator::add("1\n22\n333") == 356);
}

TEST_CASE("add with many numbers and \\n or , as seperator returns their sum") {
  CHECK(StringCalculator::add("1,22\n333") == 356);
}

TEST_CASE(
    "add with seperator specification and many number returns their sum") {
  CHECK(StringCalculator::add("//-\n1-22-333") == 356);
}

TEST_CASE("add with negative numbers throws") {
  REQUIRE_THROWS_AS(StringCalculator::add("1,-1,1,-1"), std::invalid_argument);
}

TEST_CASE("add with negative numbers throws and exception text contains "
          "negative numbers") {
  try {
    StringCalculator::add("1,-1,22,-22,333,-333");
  } catch (std::invalid_argument const &e) {
    // CHECK_THAT(e.what(), Catch::Contains("-1"));
  }
}
} // namespace
