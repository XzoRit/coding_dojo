#include "gilded_rose.hpp"
#include "quality.hpp"
#include "article.hpp"
#include "aged_brie.hpp"
#include "backstage_pass.hpp"

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

GildedRose::GildedRose(vector<Item>& items)
  : items(items)
{}
    
class Sulfuras
{
public:
  explicit Sulfuras(Item& it)
    : item(it)
  {
  }

  void update()
  {
  }

private:
  Item& item;
};

#include <boost/variant.hpp>
#include <vector>

typedef std::vector<
  boost::variant<
    Article,
    AgedBrie,
    BackstagePass,
    Sulfuras > >
Articles;

class Updater : public boost::static_visitor<>
{
public:
  template<class T>
  void operator()(T& t)
  {
    t.update();
  }
};

#include <algorithm>

void GildedRose::updateQuality() 
{
  Articles articles;
  for (vector<Item>::iterator it = items.begin(); it < items.end(); ++it)
    {
      if (isSulfuras(*it))
	{
	  articles.push_back(Sulfuras(*it));
	}
      else if (isAgedBrie(*it))
	{
	  articles.push_back(AgedBrie(*it));
	}
      else if (isBackstagePass(*it))
	{
	  articles.push_back(BackstagePass(*it));
	}
      else
	{
	  articles.push_back(Article(*it));
	}
    }
  Updater u;
  std::for_each(articles.begin(), articles.end(), boost::apply_visitor(u));
}
