#ifndef _SULFURAS_HPP_
#define _SULFURAS_HPP_

class Item;

class Sulfuras
{
public:
  explicit Sulfuras(Item& it);

  void update();

private:
  Item& item;
};

#endif
