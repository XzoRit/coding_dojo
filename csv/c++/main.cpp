#include <range/v3/action/split.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>

namespace xzr::csv
{
  namespace impl
  {
  const auto split_by = [](const auto& text, const auto& sep)
  {
    return ranges::action::split(text, sep);
  };
  }
  
  const auto rows_from = [](const auto& csv_text)
  {
    return impl::split_by(csv_text, '\n');
  };
}

using namespace std::string_literals;

TEST_CASE("split text by newline")
{
  const auto csv_text =
    "first row\n"
    "second row\n"
    "third row"s;
  const auto rows = xzr::csv::rows_from(csv_text);
  REQUIRE(rows.size() == 3);
  CHECK(rows[0] == "first row");
  CHECK(rows[1] == "second row");
  CHECK(rows[2] == "third row");
}
