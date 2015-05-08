#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <string>

class Item
{
public:
  Item(std::string name, int sellIn, int quality);

  std::string name;
  int sellIn;
  int quality;
};

#endif
