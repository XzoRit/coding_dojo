#include "gilded_rose.hpp"
#include "quality.hpp"
#include "article.hpp"
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

int const MaxQuality = Quality::max();
int const MinQuality = Quality::min();
int const SulfurasQuality = Quality::sulfuras();

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

SCENARIO("article with positive sellin is updated")
{
  GIVEN("an article with positive sellin")
    {
      int const quality = 7;
      int const sellIn = 16;
      std::string const name = "article";
      Article a(name, sellIn, quality);
      WHEN("it is updated")
	{
	  a.update();
	  THEN("quality and sellin are decremented by 1")
	    {
	      CHECK(a == Article(name, sellIn - 1, quality - 1));
	    }
	}
    }
}

SCENARIO("article with sellin of 0 is updated")
{
  GIVEN("an aritcle with a sellin value of 0")
    {
      int const quality = 7;
      int const sellIn = 0;
      std::string const name = "article";
      Article a(name, sellIn, quality);
      WHEN("it is updated")
	{
	  a.update();
	  THEN("quality is decremented by 2 and sellin is decremented by 1")
	    {
	      CHECK(a == Article(name, sellIn - 1, quality - 2));
	    }
	}
    }
}

SCENARIO("article with min quality is updated")
{
  GIVEN("an article with min quality")
    {
      int const sellIn = 0;
      std::string const name = "article";
      Article a(name, sellIn, Quality::min());
      WHEN("it is updated")
	{
	  a.update();
	  THEN("quality does not change and sellin is decremented by 1")
	    {
	      CHECK(a == Article(name, sellIn - 1, Quality::min()));
	    }
	}
    }
}

SCENARIO("days pass for aged brie")
{
  GIVEN("an aged brie with positive sellin value")
    {
      int const quality = 28;
      Item const item("Aged Brie", 11, quality);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality increases by one")
	    {
	      CHECK(app.itemQuality() == quality + 1);
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
	  AND_WHEN("quality is one under max")
	    {
	      app.setQualityTo(MaxQuality - 1);
	      AND_WHEN("quality is updated")
		{
		  app.updateQuality();
		  THEN("quality is not greater than max")
		    {
		      CHECK(app.itemQuality() == MaxQuality);
		    }
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
	  AND_WHEN("quality is one under max")
	    {
	      app.setQualityTo(MaxQuality - 1);
	      AND_WHEN("quality is updated")
		{
		  app.updateQuality();
		  THEN("quality is not greater than max")
		    {
		      CHECK(app.itemQuality() == MaxQuality);
		    }
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
      WHEN("concert is over")
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

SCENARIO("days pass for sulfuras")
{
  GIVEN("sulfuras with positive sellin value")
    {
      int const sellIn = 23;
      Item const item("Sulfuras, some strange stuff", sellIn, SulfurasQuality);
      AppHolder app(item);
      WHEN("quality is updated")
	{
	  app.updateQuality();
	  THEN("quality and sellin do not change")
	    {
	      CHECK(app.itemQuality() == SulfurasQuality);
	      CHECK(app.itemSellIn() == sellIn);
	    }
	}
      WHEN("sellin value is 0")
	{
	  int const sellIn = 0;
	  app.setSellInTo(sellIn);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality and sellin do not change")
		{
		  CHECK(app.itemQuality() == SulfurasQuality);
		  CHECK(app.itemSellIn() == sellIn);
		}
	    }
	}
      WHEN("sellin value is negative")
	{
	  int const sellIn = -5;
	  app.setSellInTo(sellIn);
	  AND_WHEN("quality is updated")
	    {
	      app.updateQuality();
	      THEN("quality and sellin do not change")
		{
		  CHECK(app.itemQuality() == SulfurasQuality);
		  CHECK(app.itemSellIn() == sellIn);
		}
	    }
	}
    }
}
