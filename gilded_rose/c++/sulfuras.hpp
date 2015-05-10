#ifndef _SULFURAS_HPP_
#define _SULFURAS_HPP_

#include <ostream>

class Sulfuras
{
public:
  void update();
private:
  friend std::ostream& operator<<(std::ostream& o, Sulfuras const& s);
};

#endif
