#include "article.hpp"
#include "item.hpp"
#include "quality.hpp"

std::ostream& operator<<(std::ostream& o, Article const& a)
{
  o << a.name << ", " << a.sellIn << ", " << a.quality;
  return o;
}

Article::Article(std::string name, int sellIn, int quality)
  : name(name)
  , sellIn(sellIn)
  , quality(quality)
{
}

bool Article::operator==(Article const& other) const
{
  return (sellIn == other.sellIn) &&
    (quality == other.quality) &&
    (name == other.name);
}

bool Article::operator!=(Article const& other) const
{
  return !(*this == other);
}

void Article::update()
{
  if (sellIn > 0)
    {
      --quality;
    }
  else
    {
      quality -= 2;
    }
  if (quality < Quality::min())
    {
      quality = Quality::min();
    }
  --sellIn;
}
