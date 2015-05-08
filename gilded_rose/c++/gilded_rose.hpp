#include "item.hpp"
#include <string>
#include <vector>

class GildedRose
{
public:
  std::vector<Item>& items;
  GildedRose(std::vector<Item>& items);
    
  void updateQuality();
};
