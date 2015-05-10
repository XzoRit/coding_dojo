#include "backstage_pass.hpp"
#include "quality.hpp"

std::ostream& operator<<(std::ostream& o, BackstagePass const& b)
{
  o << "Backstage pass for " << b.concert << ", " << b.sellIn << ", " << b.quality;
  return o;
}

BackstagePass::BackstagePass(std::string concert, int sellIn, int quality)
  : concert(concert)
  , sellIn(sellIn)
  , quality(quality)
{
}

bool BackstagePass::operator==(BackstagePass const& other) const
{
  return (quality == other.quality) &&
    (sellIn == other.sellIn) &&
    (concert == other.concert);
}

bool BackstagePass::operator!=(BackstagePass const& other) const
{
  return !(*this == other);
}

void BackstagePass::update()
{
  if (sellIn <= 0)
    {
      quality = Quality::min();
    }
  else if (sellIn < 6)
    {
      quality += 3;
    }
  else if (sellIn < 11)
    {
      quality += 2;
    }
  else
    {
      ++quality;
    }
  if (quality > Quality::max())
    {
      quality = Quality::max();
    }
  --sellIn;
}
