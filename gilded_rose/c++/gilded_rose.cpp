#include "gilded_rose.hpp"
#include "quality.hpp"

using namespace std;

GildedRose::GildedRose(vector<Item>& items)
  : items(items)
{}
    
void GildedRose::updateQuality() 
{
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (it->name != "Aged Brie" && it->name.substr(0, 14) != "Backstage pass")
        {
          if (it->quality > Quality::min())
            {
              if (it->name.substr(0, 8) != "Sulfuras")
                {
                  it->quality = it->quality - 1;
                }
            }
        }
      else
        {
          if (it->quality < Quality::max())
            {
              it->quality = it->quality + 1;

              if (it->name.substr(0, 14) == "Backstage pass")
                {
                  if (it->sellIn < 11)
                    {
                      if (it->quality < Quality::max())
                        {
                          it->quality = it->quality + 1;
                        }
                    }

                  if (it->sellIn < 6)
                    {
                      if (it->quality < Quality::max())
                        {
                          it->quality = it->quality + 1;
                        }
                    }
                }
            }
        }

      if (it->name.substr(0, 8) != "Sulfuras")
        {
          it->sellIn = it->sellIn - 1;
        }

      if (it->sellIn < 0)
        {
          if (it->name != "Aged Brie")
            {
              if (it->name.substr(0, 14) != "Backstage pass")
                {
                  if (it->quality > Quality::min())
                    {
                      if (it->name.substr(0, 8) != "Sulfuras")
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
