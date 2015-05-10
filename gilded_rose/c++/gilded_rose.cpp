#include "gilded_rose.hpp"
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <algorithm>

using namespace std;

class Updater : public boost::static_visitor<>
{
public:
  template<class T>
  void operator()(T& t)
  {
    t.update();
  }
};

GildedRose::GildedRose(Articles articles)
  : articles(articles)
{
}

void GildedRose::updateQuality() 
{
  Updater u;
  std::for_each(articles.begin(), articles.end(), boost::apply_visitor(u));
}
