#ifndef _BACKSTAGE_PASS_HPP_
#define _BACKSTAGE_PASS_HPP_

#include <string>

class BackstagePass
{
public:
  BackstagePass(std::string concert, int sellIn, int quality);
  bool operator==(BackstagePass const& other) const;
  bool operator!=(BackstagePass const& other) const;
  void update();
private:
  std::string concert;
  int sellIn;
  int quality;
};

#endif
