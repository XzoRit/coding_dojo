#define CATCH_CONFIG_MAIN
#include <catch.hpp>

std::string arabaic_to_roman(int arabic)
{
  const std::vector<std::pair<int, std::string>> roman_chars
  {
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
  };
  std::string roman;

  for(const auto it : roman_chars)
    {
      while(arabic >= it.first)
	{
	  roman += it.second;
	  arabic -= it.first;
	}
    }

  return roman;
}

TEST_CASE("1 equals I")
{
  CHECK(arabaic_to_roman(1) == "I");
}

TEST_CASE("2 equals II")
{
  CHECK(arabaic_to_roman(2) == "II");
}

TEST_CASE("3 equals III")
{
  CHECK(arabaic_to_roman(3) == "III");
}

TEST_CASE("5 equals V")
{
  CHECK(arabaic_to_roman(5) == "V");
}

TEST_CASE("6 equals VI")
{
  CHECK(arabaic_to_roman(6) == "VI");
}

TEST_CASE("7 equals VII")
{
  CHECK(arabaic_to_roman(7) == "VII");
}

TEST_CASE("10 equals X")
{
  CHECK(arabaic_to_roman(10) == "X");
}

TEST_CASE("20 equals XX")
{
  CHECK(arabaic_to_roman(20) == "XX");
}

TEST_CASE("4 equals IV")
{
  CHECK(arabaic_to_roman(4) == "IV");
}

TEST_CASE("9 equals IX")
{
  CHECK(arabaic_to_roman(9) == "IX");
}
