#include "conjured.hpp"
#include "quality.hpp"

std::ostream& operator<<(std::ostream& o, Conjured const& a)
{
  o << "Conjured " << a.name << ", " << a.sellIn << ", " << a.quality;
  return o;
}

Conjured::Conjured(std::string name, int sellIn, int quality)
  : name(name)
  , sellIn(sellIn)
  , quality(quality)
{
}

bool Conjured::operator==(Conjured const& other) const
{
  return (sellIn == other.sellIn) &&
    (quality == other.quality) &&
    (name == other.name);
}

bool Conjured::operator!=(Conjured const& other) const
{
  return !(*this == other);
}

void Conjured::update()
{
  if (sellIn > 0)
    {
      quality -= 2;
    }
  else
    {
      quality -= 4;
    }
  if (quality < Quality::min())
    {
      quality = Quality::min();
    }
  --sellIn;
}
