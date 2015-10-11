#define CATCH_CONFIG_MAIN
#include <catch.hpp>

namespace v2
{
  using Digits = std::vector<int>;
  
  auto digits_of(int arabic)
  {
    const auto num_of_digits{4};
    auto digits = Digits(num_of_digits, 0);
    std::generate_n(std::rbegin(digits), num_of_digits, [arabic]() mutable
		    {
		      const auto digit = arabic % 10;
		      arabic /= 10;
		      return digit;
		    });
    return digits;
  }
  
  TEST_CASE("digits of 0 returns {0, 0, 0, 0}")
  {
    CHECK((digits_of(0) == Digits{0, 0, 0, 0}));
  }

  TEST_CASE("digits of 1 returns {0, 0, 0, 1}")
  {
    CHECK((digits_of(1) == Digits{0, 0, 0, 1}));
  }

  TEST_CASE("digits of 2 returns {0, 0, 0, 2}")
  {
    CHECK((digits_of(2) == Digits{0, 0, 0, 2}));
  }

  TEST_CASE("digits of 30 returns {0, 0, 3, 0}")
  {
    CHECK((digits_of(30) == Digits{0, 0, 3, 0}));
  }

  TEST_CASE("digits of 37 returns {0, 0, 3, 7}")
  {
    CHECK((digits_of(37) == Digits{0, 0, 3, 7}));
  }

  TEST_CASE("digits of 739 returns {0, 7, 3, 9}")
  {
    CHECK((digits_of(739) == Digits{0, 7, 3, 9}));
  }

  TEST_CASE("digits of 7395 returns {7, 3, 9, 5}")
  {
    CHECK((digits_of(7395) == Digits{7, 3, 9, 5}));
  }

  using RomanSymbols = std::vector<std::string>;
  
  auto to_roman_symbols(Digits digits)
  {
    const auto thousands = RomanSymbols{"", "M", "MM", "MMM"};
    const auto hundreds = RomanSymbols{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const auto tens = RomanSymbols{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const auto ones = RomanSymbols{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    auto symbols = RomanSymbols(4, "");

    symbols[0] = thousands[digits[0]];
    symbols[1] = hundreds[digits[1]];
    symbols[2] = tens[digits[2]];
    symbols[3] = ones[digits[3]];
    
    return symbols;
  }
  
  TEST_CASE("roman symbols of 0 is \"\"")
  {
    CHECK((to_roman_symbols({0, 0, 0, 0}) == RomanSymbols{"", "", "", ""}));
  }

  TEST_CASE("roman symbols of {1, 1, 1, 1} is {M, C, X, I}")
  {
    CHECK((to_roman_symbols({1, 1, 1, 1}) == RomanSymbols{"M", "C", "X", "I"}));
  }

  TEST_CASE("roman symbols of {2, 2, 2, 2} is {MM, CC, XX, II}")
  {
    CHECK((to_roman_symbols({2, 2, 2, 2}) == RomanSymbols{"MM", "CC", "XX", "II"}));
  }

  TEST_CASE("roman symbols of {0, 4, 4, 4} is {, CD, XL, IV}")
  {
    CHECK((to_roman_symbols({0, 4, 4, 4}) == RomanSymbols{"", "CD", "XL", "IV"}));
  }

  TEST_CASE("roman symbols of {0, 5, 5, 5} is {, D, L, V}")
  {
    CHECK((to_roman_symbols({0, 5, 5, 5}) == RomanSymbols{"", "D", "L", "V"}));
  }

  TEST_CASE("roman symbols of {0, 7, 7, 7} is {, DCC, LXX, VII}")
  {
    CHECK((to_roman_symbols({0, 7, 7, 7}) == RomanSymbols{"", "DCC", "LXX", "VII"}));
  }

  TEST_CASE("roman symbols of {0, 9, 9, 9} is {, CM, XC, IX}")
  {
    CHECK((to_roman_symbols({0, 9, 9, 9}) == RomanSymbols{"", "CM", "XC", "IX"}));
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
