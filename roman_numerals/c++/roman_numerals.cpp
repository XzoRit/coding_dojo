#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/vector_of.hpp>

template<class From, class Map, class Pred, class Order>
auto translate(From toBeTranslated,
	       Map TranslationMap,
	       Pred isTranslationNeeded,
	       Order doTranslation)
{
  return std::accumulate(std::cbegin(TranslationMap),
			 std::cend(TranslationMap),
			 typename Map::value_type{toBeTranslated, {}},
			 [=](auto result, auto order)
			 {
			   if(isTranslationNeeded(result, order))
			     {
			       return doTranslation(result, order);
			     }
			   return result;
			 });
}

class TranslationMap
{
public:
  TranslationMap()
    : map{}
  {
    map.push_back(Value(20, "XX"));
    map.push_back(Value(10, "X"));
    map.push_back(Value(9, "IX"));
    map.push_back(Value(8, "VIII"));
    map.push_back(Value(7, "VII"));
    map.push_back(Value(6, "VI"));
    map.push_back(Value(5, "V"));
    map.push_back(Value(4, "IV"));
    map.push_back(Value(3, "III"));
    map.push_back(Value(2, "II"));
    map.push_back(Value(1, "I"));
  }

  auto arabic_to_roman() const
  {
    return map.left;
  }

  auto roman_to_arabic() const
  {
    return map.right;
  }

private:
  using MapType = boost::bimap<
    boost::bimaps::vector_of<int>,
    boost::bimaps::vector_of<std::string>>;
  using Value = MapType::value_type;
  
  MapType map;
};

std::string arabaic_to_roman(int arabic)
{
  auto isTranslationNeeded = [](auto result, auto order)
    {
      return (result.first == order.first);
    };

  auto doTranslation =[](auto result, auto order)
    {
      result.second += order.second;
      result.first -= order.first;
      return result;
    };

  return translate(arabic,
		   TranslationMap{}.arabic_to_roman(),
		   isTranslationNeeded,
		   doTranslation).second;
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
  auto isTranslationNeeded = [](auto result, auto order)
    {
      return std::equal(std::begin(order.first),
			std::end(order.first),
			std::begin(result.first));
    };

  auto doTranslation = [](auto result, auto order)
    {
      result.second += order.second;
      result.first.erase(0, order.first.size());
      return result;
    };

  return translate(roman,
		   TranslationMap{}.roman_to_arabic(),
		   isTranslationNeeded,
		   doTranslation).second;
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
