#ifndef _GILDED_ROSE_HPP_
#define _GILDED_ROSE_HPP_

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <algorithm>
#include <ostream>

template<class ArticlesType>
class GildedRose
{
public:
  explicit GildedRose(ArticlesType articles);    
  void updateQuality();
private:
  template<class Articles>
  friend std::ostream& operator<<(std::ostream& o, GildedRose<Articles> const& g);
  ArticlesType articles;
};

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

template<class Articles>
std::ostream& operator<<(std::ostream& o, GildedRose<Articles> const& g)
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

template<class ArticlesType>
GildedRose<ArticlesType>::GildedRose(ArticlesType articles)
  : articles(articles)
{
}

template<class ArticlesType>
void GildedRose<ArticlesType>::updateQuality() 
{
  Updater u;
  std::for_each(articles.begin(), articles.end(), boost::apply_visitor(u));
}

#endif
