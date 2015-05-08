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

static void updateItem(Item& it)
{
  if (it.sellIn > 0)
    {
      --it.quality;
    }
  else
    {
      it.quality -= 2;
    }
  if (it.quality < Quality::min())
    {
      it.quality = Quality::min();
    }
  --it.sellIn;
}

void GildedRose::updateQuality() 
{
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (isSulfuras(*it))
        {
	  updateSulfuras(*it);
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
	  updateItem(*it);
        }
    }
}
