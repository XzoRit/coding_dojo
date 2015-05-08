#include "aged_brie.hpp"
#include "item.hpp"
#include "quality.hpp"

AgedBrie::AgedBrie(Item& it)
  : item(it)
{
}

void AgedBrie::update()
{
  if (item.quality < Quality::max())
    {
      ++item.quality;
    }
  --item.sellIn;
}
