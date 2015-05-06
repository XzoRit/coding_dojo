#include "gilded_rose.hpp"
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

int const MaxQuality = 50;
int const MinQuality = 0;

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
      int const quality = 7;
      Item const item("item", 1, 7);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality value is decremented by one")
	    {
	      CHECK(app.itemQuality() == quality - 1);
	    }
	}
      WHEN("sellin value is 0")
	{
	  app.setSellInTo(MinQuality);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value is decremented by two")
		{
		  CHECK(app.itemQuality() == quality - 2);
		}
	    }
	}
      WHEN("quality value is is set to min")
	{
	  app.setQualityTo(MinQuality);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality value does change")
		{
		  CHECK(app.itemQuality() == MinQuality);
		}
	    }
	}
    }
}

SCENARIO("days pass for aged brie")
{
  GIVEN("an aged brie with positive sellin value")
    {
      int const quality = 28;
      Item const item("Aged Brie", 1, quality);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == quality + 1);
	    }
	}
      WHEN("sellin value is is set to min")
	{
	  app.setSellInTo(0);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality increases by one")
		{
		  CHECK(app.itemQuality() == quality + 1);
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
      int const quality = 41;
      Item const item("Backstage pass for ac/dc", 11, quality);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == quality + 1);
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
		  CHECK(app.itemQuality() == quality + 2);
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
		  CHECK(app.itemQuality() == quality + 3);
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
	      THEN("quality value is is set to min")
		{
		  CHECK(app.itemQuality() == MinQuality);
		}
	    }
	  AND_WHEN("quality value is is set to min")
	    {
	      app.setQualityTo(MinQuality);
	      AND_WHEN("quality is updated")
		{
		  app.updateQuality();
		  THEN("quality value does not change")
		    {
		      CHECK(app.itemQuality() == MinQuality);
		    }
		}
	    }
	}
    }
}
