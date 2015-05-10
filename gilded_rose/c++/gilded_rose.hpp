#ifndef _GILDED_ROSE_HPP_
#define _GILDED_ROSE_HPP_

#include "articles.hpp"
#include <ostream>

class GildedRose
{
public:
  explicit GildedRose(Articles articles);    
  void updateQuality();
private:
  friend std::ostream& operator<<(std::ostream& o, GildedRose const& g);
  Articles articles;
};

#endif
