#include "gilded_rose.hpp"
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <algorithm>

class OStreamer : public boost::static_visitor<>
{
public:
  explicit OStreamer(std::ostream& o)
    : o(o)
  {
  }

  template<class T>
  void operator()(T& t)
  {
    o << t << '\n';
  }
private:
  std::ostream& o;
};

std::ostream& operator<<(std::ostream& o, GildedRose const& g)
{
  o << "name, sellIn, quality\n";
  OStreamer ostr(o);
  std::for_each(g.articles.begin(), g.articles.end(), boost::apply_visitor(ostr));
  return o;
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

GildedRose::GildedRose(Articles articles)
  : articles(articles)
{
}

void GildedRose::updateQuality() 
{
  Updater u;
  std::for_each(articles.begin(), articles.end(), boost::apply_visitor(u));
}
