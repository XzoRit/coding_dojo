#ifndef _ARTICLE_HPP_
#define _ARTICLE_HPP_

class Item;

class Article
{
public:
  explicit Article(Item& it);

  void update();

private:
  Item& item;
};

#endif
