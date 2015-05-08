#include "article.hpp"
#include "item.hpp"
#include "quality.hpp"

Article::Article(Item& it)
  : item(it)
{
}

void Article::update()
{
  if (item.sellIn > 0)
    {
      --item.quality;
    }
  else
    {
      item.quality -= 2;
    }
  if (item.quality < Quality::min())
    {
      item.quality = Quality::min();
    }
  --item.sellIn;
}
