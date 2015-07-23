#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template<class From, class Map, class Advice>
auto translate(From toBeTranslated,
	       Map TranslationMap,
	       Advice advice)
{
  return std::get<1>(std::accumulate(std::cbegin(TranslationMap),
				     std::cend(TranslationMap),
				     typename Map::value_type{toBeTranslated, {}},
				     advice));
}

std::string arabaic_to_roman(int arabic)
{
  const std::vector<std::pair<int, std::string>> translation_map
  {
    {20, "XX"},
    {10, "X"},
    {9, "IX"},
    {8, "VIII"},
    {7, "VII"},
    {6, "VI"},
    {5, "V"},
    {4, "IV"},
    {3, "III"},
    {2, "II"},
    {1, "I"}
  };

  return translate(arabic,
		   translation_map,
		   [](auto acc, auto it)
		   {
		     if(acc.first >= it.first)
		       {
			 acc.second += it.second;
			 acc.first -= it.first;
		       }
		     return acc;
		   });
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
  const std::vector<std::pair<std::string, int>> translation_map
  {
    {"XX", 20},
    {"X", 10},
    {"IX", 9},
    {"VIII", 8},
    {"VII", 7},
    {"VI", 6},
    {"V", 5},
    {"IV", 4},
    {"III", 3},
    {"II", 2},
    {"I", 1}
  };

  return translate(roman,
		   translation_map,
		   [](auto acc, auto it)
		   {
		     if(std::equal(std::begin(it.first),
				   std::end(it.first),
				   std::begin(acc.first)))
		       {
			 acc.second += it.second;
			 acc.first.erase(0, it.first.size());
		       }
		     return acc;
		   });
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
