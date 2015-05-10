#ifndef _ARTICLE_HPP_
#define _ARTICLE_HPP_

#include <string>
#include <ostream>

class Article
{
public:
  Article(std::string name, int sellIn, int quality);
  void update();
  bool operator==(Article const&) const;
  bool operator!=(Article const&) const;
private:
  friend std::ostream& operator<<(std::ostream& o, Article const& a);
  std::string const name;
  int sellIn;
  int quality;
};

#endif
