#include "gilded_rose.hpp"
#include "articles.hpp"
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <algorithm>

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

class Updater : public boost::static_visitor<>
{
public:
  template<class T>
  void operator()(T& t)
  {
    t.update();
  }
};

GildedRose::GildedRose(vector<Item>& items)
  : items(items)
{}
    
void GildedRose::updateQuality() 
{
  Articles articles;
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (isSulfuras(*it))
	{
	  articles.push_back(Sulfuras());
	}
      else if (isAgedBrie(*it))
	{
	  articles.push_back(AgedBrie(it->quality));
	}
      else if (isBackstagePass(*it))
	{
	  articles.push_back(BackstagePass(it->name, it->sellIn, it->quality));
	}
      else
	{
	  articles.push_back(Article(it->name, it->sellIn, it->quality));
	}
    }
  Updater u;
  std::for_each(articles.begin(), articles.end(), boost::apply_visitor(u));
}
