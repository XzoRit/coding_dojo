#ifndef _CONJURED_HPP_
#define _CONJURED_HPP_

#include <string>
#include <ostream>

class Conjured
{
public:
  Conjured(std::string name, int sellIn, int quality);
  void update();
  bool operator==(Conjured const&) const;
  bool operator!=(Conjured const&) const;
private:
  friend std::ostream& operator<<(std::ostream& o, Conjured const& a);
  std::string const name;
  int sellIn;
  int quality;
};

#endif
