#include <boost/test/unit_test.hpp>
#include <libocr/ocr.hpp>
#include <variant>

/*
 0123456789012345678901234567
0...._.._....._....._.._.._.n
1..|._|._||_||_.|_...||_||_|n
2..||_.._|..|._||_|..||_|..|n
3...........................n
*/

template<class... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...)->overloaded<Ts...>;

namespace cx
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

enum class mask : char { keep, ignore };

std::ostream& operator<<(std::ostream& str, mask m)
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
      if (cx::equal(
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
};

BOOST_AUTO_TEST_CASE(parse_1_to_9)
{
  constexpr ocr_str_t ocr_str{
    { '.', '.', '.', '.', '_', '.', '.', '_', '.', '.', '.', '.', '.', '_',
      '.', '.', '.', '.', '.', '_', '.', '.', '_', '.', '.', '_', '.', '.',
      '.', '|', '.', '_', '|', '.', '_', '|', '|', '_', '|', '|', '_', '.',
      '|', '_', '.', '.', '.', '|', '|', '_', '|', '|', '_', '|', '.', '.',
      '|', '|', '_', '.', '.', '_', '|', '.', '.', '|', '.', '_', '|', '|',
      '_', '|', '.', '.', '|', '|', '_', '|', '.', '.', '|' }
  };

  constexpr num_t expected_ints{ { 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
  constexpr num_t found_ints{ digits_to_ints(to_digits(ocr_str)) };
  static_assert(
    cx::equal(
      begin(expected_ints),
      end(expected_ints),
      begin(found_ints),
      end(found_ints)),
    "expected { 1,2,3,4,5,6,7,8,9 }");
  BOOST_CHECK_EQUAL_COLLECTIONS(
    begin(expected_ints),
    end(expected_ints),
    begin(found_ints),
    end(found_ints));
}
