#define CATCH_CONFIG_MAIN
#include <catch.hpp>

bool isLeapYear(int year)
{
  if(!(year % 400)) return true;
  if(!(year % 100)) return false;
  return !(year % 4);
}

TEST_CASE("2000 is a leap year", "")
{
  REQUIRE(isLeapYear(2000));
}

TEST_CASE("1999 is not a leap year", "")
{
  REQUIRE_FALSE(isLeapYear(1999));
}

TEST_CASE("1996 is a leap year", "")
{
  REQUIRE(isLeapYear(1996));
}

TEST_CASE("1992 is a leap year", "")
{
  REQUIRE(isLeapYear(1992));
}

TEST_CASE("1900 is not a leap year", "")
{
  REQUIRE_FALSE(isLeapYear(1900));
}

TEST_CASE("1800 is not a leap year", "")
{
  REQUIRE_FALSE(isLeapYear(1800));
}

TEST_CASE("1700 is not a leap year", "")
{
  REQUIRE_FALSE(isLeapYear(1700));
}

TEST_CASE("1600 is a leap year", "")
{
  REQUIRE(isLeapYear(1600));
}

TEST_CASE("1200 is a leap year", "")
{
  REQUIRE(isLeapYear(1200));
}

TEST_CASE("800 is a leap year", "")
{
  REQUIRE(isLeapYear(800));
}
