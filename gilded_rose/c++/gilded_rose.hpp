#include <string>
#include <vector>

class Item
{
public:
  Item(std::string name, int sellIn, int quality)
    : name(name)
    , sellIn(sellIn)
    , quality(quality) 
  {}

  std::string name;
  int sellIn;
  int quality;
};

class GildedRose
{
public:
  std::vector<Item>& items;
  GildedRose(std::vector<Item>& items);
    
  void updateQuality();
};
