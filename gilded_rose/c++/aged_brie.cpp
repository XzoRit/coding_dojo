#include "aged_brie.hpp"
#include "quality.hpp"

std::ostream& operator<<(std::ostream& o, AgedBrie const& a)
{
  o << "Aged Brie, " << a.quality;
  return o;
}

AgedBrie::AgedBrie(int quality)
  : quality(quality)
{
}

bool AgedBrie::operator==(AgedBrie const& other) const
{
  return quality == other.quality;
}

bool AgedBrie::operator!=(AgedBrie const& other) const
{
  return !(*this == other);
}

void AgedBrie::update()
{
  if (quality < Quality::max())
    {
      ++quality;
    }
}
