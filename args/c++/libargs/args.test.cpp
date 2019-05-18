#include <libargs/args.hpp>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(libargs_add)
{
  const auto a{ xzr::args::add(1, 3) };
  BOOST_TEST(a != 4);
}
