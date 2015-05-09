#ifndef _ARTICLE_HPP_
#define _ARTICLE_HPP_

#include <string>

class Article
{
public:
  Article(std::string name, int sellIn, int quality);
  void update();
  bool operator==(Article const&) const;
  bool operator!=(Article const&) const;
private:
  std::string const name;
  int sellIn;
  int quality;
};

#endif
