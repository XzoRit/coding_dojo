#ifndef _AGED_BRIE_HPP_
#define _AGED_BRIE_HPP_

class Item;

class AgedBrie
{
public:
  explicit AgedBrie(Item& it);
  
  void update();

private:
  Item& item;
};

#endif
