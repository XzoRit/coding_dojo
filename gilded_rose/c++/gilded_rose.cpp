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
    
void GildedRose::updateQuality() 
{
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (isSulfuras(*it))
	{
	}
      else if (isAgedBrie(*it))
        {
          if (it->quality < Quality::max())
            {
              it->quality = it->quality + 1;
	    }
        }
      else if (isBackstagePass(*it))
        {
	  if (it->sellIn < 6)
	    {
	      it->quality = it->quality + 3;
	    }
	  else if (it->sellIn < 11)
	    {
	      it->quality = it->quality + 2;
	    }
	  else
	    {
	      it->quality = it->quality + 1;
	    }
          if (it->quality > Quality::max())
            {
	      it->quality = Quality::max();
	    }
	}
      else
        {
          if (it->quality > Quality::min())
            {
                  it->quality = it->quality - 1;
	    }
        }

      if (!isSulfuras(*it))
        {
          it->sellIn = it->sellIn - 1;
        }

      if (it->sellIn < 0)
        {
          if (!isAgedBrie(*it))
            {
              if (!isBackstagePass(*it))
                {
                  if (it->quality > Quality::min())
                    {
                      if (!isSulfuras(*it))
                        {
                          it->quality = it->quality - 1;
                        }
                    }
                }
              else
                {
                  it->quality = it->quality - it->quality;
                }
            }
        }
    }
}
