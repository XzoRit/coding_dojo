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
    
static void updateSulfuras(Item& it)
{
}

static void updateAgedBrie(Item& it)
{
  if (it.quality < Quality::max())
    {
      ++it.quality;
    }
  --it.sellIn;
}

static void updateBackstagePass(Item& it)
{
  if (it.sellIn <= 0)
    {
      it.quality = Quality::min();
    }
  else if (it.sellIn < 6)
    {
      it.quality += 3;
    }
  else if (it.sellIn < 11)
    {
      it.quality += 2;
    }
  else
    {
      ++it.quality;
    }
  if (it.quality > Quality::max())
    {
      it.quality = Quality::max();
    }
  --it.sellIn;
}

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
	  updateAgedBrie(*it);
	}
      else if (isBackstagePass(*it))
	{
	  updateBackstagePass(*it);
	}
      else
	{
	  Article(*it).update();
	}
    }
}
