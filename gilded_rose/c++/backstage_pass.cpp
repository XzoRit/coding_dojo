#include "backstage_pass.hpp"
#include "item.hpp"
#include "quality.hpp"

BackstagePass::BackstagePass(Item& it)
  : item(it)
{
}

void BackstagePass::update()
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
