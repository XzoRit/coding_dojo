#include "gilded_rose.hpp"
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

int const MaxQuality = 50;

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

  void updateQuality()
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
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality value is decremented by one")
	    {
	      CHECK(app.itemQuality() == 1);
	    }
	}
      WHEN("sellin value is 0")
	{
	  app.setSellInTo(0);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value is decremented by two")
		{
		  CHECK(app.itemQuality() == 0);
		}
	    }
	}
      WHEN("quality value is 0")
	{
	  app.setQualityTo(0);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value does change")
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
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == 18);
	    }
	}
      WHEN("sellin value is 0")
	{
	  app.setSellInTo(0);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality increases by one")
		{
		  CHECK(app.itemQuality() == 18);
		}
	    }
	}
      WHEN("quality value is set to max")
	{
	  app.setQualityTo(MaxQuality);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value does not change")
		{
		  CHECK(app.itemQuality() == MaxQuality);
		}
	    }
	}
    }
}

SCENARIO("days pass for backstage pass")
{
  GIVEN("a backstage pass with positive sellin value")
    {
      Item const item("Backstage pass for ac/dc", 11, 47);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == 48);
	    }
	}
      WHEN("sellin value is equal to 10")
	{
	  app.setSellInTo(10);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality increaes by two")
		{
		  CHECK(app.itemQuality() == 49);
		}
	    }
	}
      WHEN("sellin value is equal to 5")
	{
	  app.setSellInTo(5);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality increases by 3")
		{
		  CHECK(app.itemQuality() == MaxQuality);
		}
	    }
	}
      WHEN("quality value is set to max")
	{
	  app.setQualityTo(MaxQuality);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value does not change")
		{
		  CHECK(app.itemQuality() == MaxQuality);
		}
	    }
	}
      WHEN("cancert is over")
	{
	  app.setSellInTo(0);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value is 0")
		{
		  CHECK(app.itemQuality() == 0);
		}
	    }
	  AND_WHEN("quality value is 0")
	    {
	      app.setQualityTo(0);
	      AND_WHEN("quality is updated")
		{
		  app.updateQuality();
		  THEN("quality value does not change")
		    {
		      CHECK(app.itemQuality() == 0);
		    }
		}
	    }
	}
    }
}
