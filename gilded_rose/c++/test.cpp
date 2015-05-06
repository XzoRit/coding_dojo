#include "gilded_rose.hpp"
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

class AppHolder
{
public:
  AppHolder(Item it)
    : items(1, it)
    , app(items)
  {
  }

  int itemQuality() const
  {
    return items.front().quality;
  }

  int itemSellIn() const
  {
    return items.front().sellIn;
  }

  void oneDayPassed()
  {
    app.updateQuality();
  }

private:
  std::vector<Item> items;
  GildedRose app;
};

SCENARIO("days pass for an item")
{
  GIVEN("an item with sellin value of 1")
    {
      Item const item("item", 1, 3);
      AppHolder app(item);
      WHEN("one day passes")
	{
	  app.oneDayPassed();
	  THEN("sellin and quality values are decremented by one")
	    {
	      CHECK(app.itemSellIn() == 0);
	      CHECK(app.itemQuality() == 2);
	    }
	  AND_WHEN("a second day passes")
	    {
	      app.oneDayPassed();
	      THEN("quality value is decremented by two")
		{
		  CHECK(app.itemQuality() == 0);
		}
	      AND_WHEN("a third day passes")
		{
		  app.oneDayPassed();
		  THEN("quality value does not become negativ")
		    {
		      CHECK(app.itemQuality() == 0);
		    }
		}
	    }
	}
    }
}
