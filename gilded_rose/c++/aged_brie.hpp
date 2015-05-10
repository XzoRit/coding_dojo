#ifndef _AGED_BRIE_HPP_
#define _AGED_BRIE_HPP_

#include <ostream>

class AgedBrie
{
public:
  AgedBrie(int quality);
  bool operator==(AgedBrie const& other) const;
  bool operator!=(AgedBrie const& other) const;
  void update();
private:
  friend std::ostream& operator<<(std::ostream& o, AgedBrie const& a);
  int quality;
};

#endif
