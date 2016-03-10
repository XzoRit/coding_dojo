#ifndef V2_DIAMOND_H
#define V2_DIAMOND_H

#include <vector>
#include <string>

namespace v2
{
  class Diamond
  {
  public:
    typedef std::vector<std::string> Lines;
    static std::string letters(int amount);
    static Lines spaces_after(int amount);
    static Lines spaces_before(int amount);
    static Lines lines(int amount);
    static Lines mirror_vertical(Lines lines);
    static Lines mirror_horizontal(Lines lines);
    static Lines all_lines(int amount);
    static int char_to_num(char c);
    static std::string print(char c);
  };
}

#endif
