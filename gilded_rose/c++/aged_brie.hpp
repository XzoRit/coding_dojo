#ifndef _AGED_BRIE_HPP_
#define _AGED_BRIE_HPP_

class AgedBrie
{
public:
  AgedBrie(int quality);
  bool operator==(AgedBrie const& other) const;
  bool operator!=(AgedBrie const& other) const;
  void update();
private:
  int quality;
};

#endif
