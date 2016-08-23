#include "diamond.hpp"
#include <boost/range/irange.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/size.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/join.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/phoenix/operator/arithmetic.hpp>
#include <boost/phoenix/stl/container.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <iterator>

namespace v3
{
  using namespace std::literals::string_literals;
  using std::string;
  using std::begin;
  using std::end;
  using boost::irange;
  using boost::combine;
  using boost::copy_range;
  using boost::size;
  using boost::join;
  using boost::adaptors::transformed;
  using boost::adaptors::reversed;
  using boost::adaptors::sliced;
  using boost::phoenix::construct;
  using boost::fusion::fold;
  using boost::phoenix::arg_names::_1;
  using boost::phoenix::arg_names::_2;
  using boost::phoenix::rbegin;
  using boost::phoenix::rend;
  using SpacesAndLetter = boost::tuple<const string&, const char&, const string&>;

  namespace impl
  {
    static auto letters(int amount)
    {
      return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"s.substr(0, amount);
    }

    static auto spaces_after(int amount)
    {
      return irange(0, amount) | transformed(construct<string>(_1, ' '));
    }

    static auto spaces_before(int amount)
    {
      return spaces_after(amount) | reversed;
    }

    static auto concat(const SpacesAndLetter& spaces_and_letter)
    {
      return fold(spaces_and_letter, string{""}, _1 + _2);
    }

    static const auto mirror_vertical = [](const auto& lines)
    {
      return lines | transformed(_1 + construct<string>(rbegin(_1) + 1, rend(_1)));
    };

    static const auto mirror_horizontal = [](const auto& lines)
    {
      return join(lines, lines | sliced(0, size(lines) - 1) | reversed);
    };
    
    static auto all_lines(int amount)
    {
      return mirror_horizontal(mirror_vertical(Diamond::lines(amount)));
    }
  }
}

namespace v3
{
  string Diamond::letters(int amount)
  {
    return impl::letters(amount);
  }

  Diamond::Lines Diamond::spaces_after(int amount)
  {
    return copy_range<Lines>(impl::spaces_after(amount));
  }

  Diamond::Lines Diamond::spaces_before(int amount)
  {
    return copy_range<Lines>(impl::spaces_before(amount));
  }
  
  Diamond::Lines Diamond::lines(int amount)
  {
    return copy_range<Lines>(combine(spaces_before(amount),
				     letters(amount),
				     spaces_after(amount)) | transformed(impl::concat));
  }

  Diamond::Lines Diamond::mirror_vertical(Lines lines)
  {
    return copy_range<Lines>(impl::mirror_vertical(lines));
  }

  Diamond::Lines Diamond::mirror_horizontal(Lines lines)
  {
    return copy_range<Lines>(impl::mirror_horizontal(lines));
  }

  Diamond::Lines Diamond::all_lines(int amount)
  {
    return copy_range<Lines>(
      impl::mirror_horizontal(
        impl::mirror_vertical(
	  lines(amount))));
  }

  int Diamond::char_to_num(char c)
  {
    return c - 'A' + 1;
  }

  string Diamond::print(char c)
  {
    return boost::accumulate(impl::all_lines(char_to_num(c)), ""s, _1 + _2 + '\n');
  }
}
