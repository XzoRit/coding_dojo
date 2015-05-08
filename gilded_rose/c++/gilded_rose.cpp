#include "gilded_rose.hpp"
#include "quality.hpp"

using namespace std;

static bool isAgedBrie(Item const& it)
{
  return it.name == "Aged Brie";
}

static bool isBackstagePass(Item const& it)
{
  return it.name.substr(0, 14) == "Backstage pass";
}

static bool isSulfuras(Item const& it)
{
  return it.name.substr(0, 8) == "Sulfuras";
}

GildedRose::GildedRose(vector<Item>& items)
  : items(items)
{}
    
class Article
{
public:
  explicit Article(Item& it)
    : item(it)
  {
  }

  void update()
  {
    if (item.sellIn > 0)
      {
	--item.quality;
      }
    else
      {
	item.quality -= 2;
      }
    if (item.quality < Quality::min())
      {
	item.quality = Quality::min();
      }
    --item.sellIn;
  }

private:
  Item& item;
};

class Sulfuras
{
public:
  explicit Sulfuras(Item& it)
    : item(it)
  {
  }

  void update()
  {
  }

private:
  Item& item;
};

class AgedBrie
{
public:
  explicit AgedBrie(Item& it)
    : item(it)
  {
  }

  void update()
  {
    if (item.quality < Quality::max())
      {
	++item.quality;
      }
    --item.sellIn;
  }

private:
  Item& item;
};

class BackstagePass
{
public:
  explicit BackstagePass(Item& it)
    : item(it)
  {
  }

  void update()
  {
    if (item.sellIn <= 0)
      {
	item.quality = Quality::min();
      }
    else if (item.sellIn < 6)
      {
	item.quality += 3;
      }
    else if (item.sellIn < 11)
      {
	item.quality += 2;
      }
    else
      {
	++item.quality;
      }
    if (item.quality > Quality::max())
      {
	item.quality = Quality::max();
      }
    --item.sellIn;
  }

private:
  Item& item;
};

void GildedRose::updateQuality() 
{
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (isSulfuras(*it))
	{
	  Sulfuras(*it).update();
	}
      else if (isAgedBrie(*it))
	{
	  AgedBrie(*it).update();
	}
      else if (isBackstagePass(*it))
	{
	  BackstagePass(*it).update();
	}
      else
	{
	  Article(*it).update();
	}
    }
}
