#include "gilded_rose.hpp"
#include "quality.hpp"
#include "article.hpp"
#include "aged_brie.hpp"
#include "backstage_pass.hpp"
#include "sulfuras.hpp"

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

SCENARIO("aged brie is updated")
{
  GIVEN("an aged brie")
    {
      int const quality = 28;
      AgedBrie a(quality);
      WHEN("it is updated")
	{
	  a.update();
	  THEN("quality increases by 1")
	    {
	      CHECK(a == AgedBrie(quality + 1));
	    }
	}
    }
}

SCENARIO("aged brie with max quality is updated")
{
  GIVEN("an aged brie with max quality")
    {
      AgedBrie a(Quality::max());
      WHEN("it is updated")
	{
	  a.update();
	  THEN("quality does not change")
	    {
	      CHECK(a == AgedBrie(Quality::max()));
	    }
	}
    }
}

SCENARIO("backstage pass with sellin over 10 is updated")
{
  GIVEN("a backstage pass with sellin over 10")
    {
      int const quality = 41;
      int const sellIn = 11;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality increases by 1 and sellin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, quality + 1));
	    }
	}
    }
}

SCENARIO("backstage pass with sellin over 10 and max quality is updated")
{
  GIVEN("a backstage pass with sellin over 10 and max quality")
    {
      int const sellIn = 11;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, Quality::max());
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality increases does not change and sellin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
	    }
	}
    }
}

SCENARIO("backstage pass with sellin of 10 is updated")
{
  GIVEN("a backstage with sellin of 10")
    {
      int const quality = 41;
      int const sellIn = 10;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality increaes by 2 and sellin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, quality + 2));
	    }
	}
    }
}

SCENARIO("backstage pass with sellin of 10 and quality 1 under max is updated")
{
  GIVEN("a backstage pass with sellin of 10 and quality 1 under max")
    {
      int const quality = Quality::max() - 1;
      int const sellIn = 10;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality is set to max and selllin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
	    }
	}
    }
}
SCENARIO("backstage pass with sellin of 5 is updated")
{
  GIVEN("a backstage with sellin of 5")
    {
      int const quality = 41;
      int const sellIn = 5;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality increaes by 3 and sellin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, quality + 3));
	    }
	}
    }
}

SCENARIO("backstage pass with sellin of 5 and quality 1 under max is updated")
{
  GIVEN("a backstage pass with sellin of 5 and quality 1 under max")
    {
      int const quality = Quality::max() - 1;
      int const sellIn = 5;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality is set to max and selllin decreases by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
	    }
	}
    }
}

SCENARIO("backstage pass for a passed concert is updated")
{
  GIVEN("a backstage pass with sellin of 0")
    {  
      int const quality = 41;
      int const sellIn = 0;
      std::string const concert = "x.y.u.";
      BackstagePass b(concert, sellIn, quality);
      WHEN("it is updated")
	{
	  b.update();
	  THEN("quality value is is set to min and sellin is decreased by 1")
	    {
	      CHECK(b == BackstagePass(concert, sellIn - 1, Quality::min()));
	    }
	}
    }
 }

SCENARIO("sulfuras is updated")
{
  GIVEN("sulfuras")
    {
      Sulfuras s;
      WHEN("it is updated")
	{
	  s.update();
	  THEN("neither quality nor sellin change")
	    {
	    }
	}
    }
}
