#ifndef _GILDED_ROSE_HPP_
#define _GILDED_ROSE_HPP_

#include "articles.hpp"

class GildedRose
{
public:
  explicit GildedRose(Articles articles);    
  void updateQuality();
private:
  Articles articles;
};

#endif
