#include <array>
#include <ostream>
#include <variant>

namespace xzr
{
namespace cx
{
inline namespace v1
{
template<class InputIt1, class InputIt2>
constexpr bool
equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (!(*first1 == *first2)) { return false; }
  }
  return true;
}
}
}
}
namespace xzr
{
namespace ocr
{
namespace impl
{
inline namespace v1
{
enum class mask : char { keep, ignore };

inline std::ostream& operator<<(std::ostream& str, mask m)
{
  if (m == mask::keep) str << "keep";
  if (m == mask::ignore) str << "ignore";
  return str;
}

template<class T>
constexpr std::variant<T, mask> operator|(mask m, T t) noexcept
{
  if (m == mask::keep) return t;
  return mask::ignore;
}

using ocr_str_t = std::array<char, 27 * 3>;
using ocr_digit_t = std::array<char, 9>;
using ocr_digits_t = std::array<ocr_digit_t, 10>;
using ocr_num_t = std::array<ocr_digit_t, 9>;
using num_t = std::array<int, 9>;
using mask_t = std::array<mask, 57>;

// sliding_window{reapeat((take(3), drop(24)), 2), keep(3))};
constexpr mask_t sliding_window{
  { mask::keep,   mask::keep,   mask::keep,   mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::keep,   mask::keep,   mask::keep,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::ignore,
    mask::ignore, mask::ignore, mask::ignore, mask::ignore, mask::keep,
    mask::keep,   mask::keep }
};

constexpr ocr_digit_t str_zero{
  { '.', '_', '.', '|', '.', '|', '|', '_', '|' }
};
constexpr ocr_digit_t str_one{
  { '.', '.', '.', '.', '.', '|', '.', '.', '|' }
};
constexpr ocr_digit_t str_two{
  { '.', '_', '.', '.', '_', '|', '|', '_', '.' }
};
constexpr ocr_digit_t str_three{
  { '.', '_', '.', '.', '_', '|', '.', '_', '|' }
};
constexpr ocr_digit_t str_four{
  { '.', '.', '.', '|', '_', '|', '.', '.', '|' }
};
constexpr ocr_digit_t str_five{
  { '.', '_', '.', '|', '_', '.', '.', '_', '|' }
};
constexpr ocr_digit_t str_six{
  { '.', '.', '.', '|', '_', '.', '|', '_', '|' }
};
constexpr ocr_digit_t str_seven{
  { '.', '_', '.', '.', '.', '|', '.', '.', '|' }
};
constexpr ocr_digit_t str_eight{
  { '.', '_', '.', '|', '_', '|', '|', '_', '|' }
};
constexpr ocr_digit_t str_nine{
  { '.', '_', '.', '|', '_', '|', '.', '.', '|' }
};

constexpr ocr_digits_t ocr_digits{ str_zero,  str_one,  str_two, str_three,
                                   str_four,  str_five, str_six, str_seven,
                                   str_eight, str_nine };

constexpr auto extract_one_digit(const ocr_str_t& letters, std::size_t offset)
{
  ocr_digit_t digit{};
  for (int i{}, j{}; i < size(sliding_window); ++i)
  {
    if (sliding_window[i] == mask::ignore) continue;
    digit[j++] = letters[i + offset];
    if (i == size(sliding_window)) j = 0;
  }
  return digit;
};

constexpr ocr_num_t to_digits(const ocr_str_t& letters)
{
  ocr_num_t digits{};
  std::size_t digit_offset{};
  for (int i{}; i < 9; ++i)
  {
    digit_offset = i * 3;
    digits[i] = extract_one_digit(letters, digit_offset);
  }
  return digits;
}

constexpr auto digits_to_ints(const ocr_num_t& digits)
{
  num_t ints{};
  for (int a{}; a < size(digits); ++a)
  {
    for (int b{}; b < size(ocr_digits); ++b)
    {
      if (xzr::cx::equal(
            begin(ocr_digits[b]),
            end(ocr_digits[b]),
            begin(digits[a]),
            end(digits[a])))
      {
        ints[a] = b;
        break;
      }
    }
  }
  return ints;
}
constexpr auto ints_to_int(const num_t& num)
{
  num_t::value_type res{};
  for (auto i{ 0 }; i < size(num); ++i)
  {
    int a{ 1 };
    for (int b{}; b < size(num) - 1 - i; ++b)
    {
      a *= 10;
    }
    res += num[i] * a;
  }
  return res;
}
constexpr auto digits_to_int(const ocr_str_t& letters)
{
  return ints_to_int(digits_to_ints(to_digits(letters)));
}
}
}
}
}
namespace xzr
{
namespace ocr
{
inline namespace v1
{
using ocr_str_t = impl::ocr_str_t;
constexpr auto parse(const ocr_str_t& ocr_str)
{
  return impl::digits_to_int(ocr_str);
}
}
}
}
