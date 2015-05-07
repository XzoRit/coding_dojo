#include "gilded_rose.hpp"
#include "quality.hpp"

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}
    
void GildedRose::updateQuality() 
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].name != "Aged Brie" && items[i].name.substr(0, 14) != "Backstage pass")
        {
            if (items[i].quality > Quality::min())
            {
                if (items[i].name.substr(0, 8) != "Sulfuras")
                {
                    items[i].quality = items[i].quality - 1;
                }
            }
        }
        else
        {
            if (items[i].quality < Quality::max())
            {
                items[i].quality = items[i].quality + 1;

                if (items[i].name.substr(0, 14) == "Backstage pass")
                {
                    if (items[i].sellIn < 11)
                    {
                        if (items[i].quality < Quality::max())
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }

                    if (items[i].sellIn < 6)
                    {
                        if (items[i].quality < Quality::max())
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (items[i].name.substr(0, 8) != "Sulfuras")
        {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0)
        {
            if (items[i].name != "Aged Brie")
            {
                if (items[i].name.substr(0, 14) != "Backstage pass")
                {
		    if (items[i].quality > Quality::min())
                    {
                        if (items[i].name.substr(0, 8) != "Sulfuras")
                        {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                }
                else
                {
                    items[i].quality = items[i].quality - items[i].quality;
                }
            }
        }
    }
}
