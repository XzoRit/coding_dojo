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

  void oneDayPassed()
  {
    app.updateQuality();
  }

  void setSellInTo(int newValue)
  {
    items.front().sellIn = newValue;
  }

  void setQualityTo(int newValue)
  {
    items.front().quality = newValue;
  }

private:
  std::vector<Item> items;
  GildedRose app;
};

SCENARIO("days pass for an item")
{
  GIVEN("an item with positve sellin value")
    {
      Item const item("item", 1, 2);
      AppHolder app(item);
      WHEN("one day passes")
	{
	  app.oneDayPassed();
	  THEN("quality value is decremented by one")
	    {
	      CHECK(app.itemQuality() == 1);
	    }
	}
      WHEN("sellin value is 0")
	{
	  app.setSellInTo(0);
	  app.oneDayPassed();
	  THEN("quality value is decremented by two")
	    {
	      CHECK(app.itemQuality() == 0);
	    }
	  AND_WHEN("another day passes")
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

SCENARIO("days pass for aged brie")
{
  GIVEN("an aged brie with positive sellin value")
    {
      Item const item("Aged Brie", 1, 17);
      AppHolder app(item);
      WHEN("one day passes")
	{
	  app.oneDayPassed();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == 18);
	    }
	}
      WHEN("sellin value is 0")
	{
	  app.setSellInTo(0);
	  CAPTURE(app.itemQuality());
	  app.oneDayPassed();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == 18);
	    }
	}
      WHEN("quality value is 50")
	{
	  app.setQualityTo(50);
	  AND_WHEN("quality is updated")
	    {
	      app.oneDayPassed();
	      THEN("quality value does not change")
		{
		  CHECK(app.itemQuality() == 50);
		}
	    }
	}
    }
}

SCENARIO("days pass for backstage pass")
{
  GIVEN("a backstage pass")
    {
      Item const item("Backstage pass for ac/dc", 11, 47);
      AppHolder app(item);
      WHEN("one day passes")
	{
	  app.oneDayPassed();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == 48);
	    }
	}
      WHEN("sellin value is equal to 10")
	{
	  app.setSellInTo(10);
	  app.oneDayPassed();
	  THEN("quality increaes by two")
	    {
	      CHECK(app.itemQuality() == 49);
	    }
	}
      WHEN("sellin value is equal to 5")
	{
	  app.setSellInTo(5);
	  app.oneDayPassed();
	  THEN("quality increases by 3")
	    {
	      CHECK(app.itemQuality() == 50);
	    }
	  AND_WHEN("another day passes")
	    {
	      app.oneDayPassed();
	      THEN("quality value does not become greater than 50")
		{
		  CHECK(app.itemQuality() == 50);
		}
	    }
	}
      WHEN("cancert is over")
	{
	  app.setSellInTo(0);
	  app.oneDayPassed();
	  THEN("quality value is 0")
	    {
	      CHECK(app.itemQuality() == 0);
	    }
	  AND_WHEN("another day passes")
	    {
	      app.oneDayPassed();
	      THEN("quality value does not become negative")
		{
		  CHECK(app.itemQuality() == 0);
		}
	    }
	}
    }
}
