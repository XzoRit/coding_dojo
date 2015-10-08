#define CATCH_CONFIG_MAIN
#include <catch.hpp>

namespace v2
{
  auto digits_of(int arabic)
  {
    auto result = std::vector<int>{0, 0, 0, 0};
    if(arabic >= 10)
      {
	const auto rem = arabic / 10;
	result[2] = rem;
	arabic -= 10 * rem;
      }
    if(arabic) result[3] = arabic;
    return result;
  }
  
  TEST_CASE("digits of 0 returns {0, 0, 0, 0}")
  {
    CHECK((digits_of(0) == std::vector<int>{0, 0, 0, 0}));
  }

  TEST_CASE("digits of 1 returns {0, 0, 0, 1}")
  {
    CHECK((digits_of(1) == std::vector<int>{0, 0, 0, 1}));
  }

  TEST_CASE("digits of 2 returns {0, 0, 0, 2}")
  {
    CHECK((digits_of(2) == std::vector<int>{0, 0, 0, 2}));
  }

  TEST_CASE("digits of 30 returns {0, 0, 3, 0}")
  {
    CHECK((digits_of(30) == std::vector<int>{0, 0, 3, 0}));
  }

  TEST_CASE("digits of 37 returns {0, 0, 3, 7}")
  {
    CHECK((digits_of(37) == std::vector<int>{0, 0, 3, 7}));
  }
}

namespace v1
{
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
  
  int roman_to_arabic(std::string roman)
  {
    const std::vector<std::pair<std::string, int>> roman_chars
    {
      {"X", 10},
      {"IX", 9},
      {"V", 5},
      {"IV", 4},
      {"I", 1}
    };
    int arabic{};
  
    for(const auto it : roman_chars)
      {
        while(std::equal(std::begin(it.first), std::end(it.first), std::begin(roman)))
  	{
  	  arabic += it.second;
  	  roman.erase(0, it.first.size());
  	}
      }
  
    return arabic;
  }
  
  
  TEST_CASE("I equals 1")
  {
    CHECK(roman_to_arabic("I") == 1);
  }
  
  TEST_CASE("II equals 2")
  {
    CHECK(roman_to_arabic("II") == 2);
  }
  
  TEST_CASE("III equals 3")
  {
    CHECK(roman_to_arabic("III") == 3);
  }
  
  TEST_CASE("V equals 5")
  {
    CHECK(roman_to_arabic("V") == 5);
  }
  
  TEST_CASE("VI equals 6")
  {
    CHECK(roman_to_arabic("VI") == 6);
  }
  
  TEST_CASE("VII equals 7")
  {
    CHECK(roman_to_arabic("VII") == 7);
  }
  
  TEST_CASE("X equals 10")
  {
    CHECK(roman_to_arabic("X") == 10);
  }
  
  TEST_CASE("XX equals 20")
  {
    CHECK(roman_to_arabic("XX") == 20);
  }
  
  TEST_CASE("IV equals 4")
  {
    CHECK(roman_to_arabic("IV") == 4);
  }
  
  TEST_CASE("IX equals 9")
  {
    CHECK(roman_to_arabic("IX") == 9);
  }
}
