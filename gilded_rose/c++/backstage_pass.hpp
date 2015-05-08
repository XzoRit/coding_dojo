#ifndef _BACKSTAGE_PASS_HPP_
#define _BACKSTAGE_PASS_HPP_

class Item;

class BackstagePass
{
public:
  explicit BackstagePass(Item& it);

  void update();

private:
  Item& item;
};

#endif
