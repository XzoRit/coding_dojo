#include <range/v3/action/split.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <vector>

namespace xzr::csv
{
namespace impl
{
using ranges::action::split;
const auto split_by = [](const auto& text, const auto& sep)
{
    return split(text, sep);
};
}
const auto rows_from = [](const auto& csv_text)
{
    return impl::split_by(csv_text, '\n');
};
const auto cols_from = [](const auto& csv_row)
{
    return impl::split_by(csv_row, ';');
};
const auto csv_from = [](const auto& txt)
{
    return rows_from(txt);
};
}

using namespace std::string_literals;

TEST_CASE("split text by newline")
{
    using xzr::csv::rows_from;

    const auto csv_text =
        "first row\n"
        "second row\n"
        "third row"s;

    const auto rows = rows_from(csv_text);

    REQUIRE(rows.size() == 3);
    CHECK(rows[0] == "first row");
    CHECK(rows[1] == "second row");
    CHECK(rows[2] == "third row");
}

TEST_CASE("split row into colums")
{
    using xzr::csv::cols_from;

    const auto row = "col 1;col 2;col 3"s;

    const auto cols = cols_from(row);

    REQUIRE(cols.size() == 3);
    CHECK(cols[0] == "col 1");
    CHECK(cols[1] == "col 2");
    CHECK(cols[2] == "col 3");
}

TEST_CASE("csv to table")
{
    using xzr::csv::csv_from;

    const auto csv =
        "Name;Strasse;Ort;Alter\n"
        "Peter Pan;Am Hang 5;12345 Einsam;42\n"
        "Maria Schmitz;Kölner Straße 45;50123 Köln;43\n"
        "Paul Meier;Münchener Weg 1;87654 München;65\n"s;

    const auto expected = std::vector<std::string>
    {
        "Name;Strasse;Ort;Alter",
        "Peter Pan;Am Hang 5;12345 Einsam;42",
        "Maria Schmitz;Kölner Straße 45;50123 Köln;43",
        "Paul Meier;Münchener Weg 1;87654 München;65"
    };
    const auto actual = std::vector<std::string> {csv_from(csv)};
    CHECK(actual == expected);
}

/*
Name;Strasse;Ort;Alter
Peter Pan;Am Hang 5;12345 Einsam;42
Maria Schmitz;Kölner Straße 45;50123 Köln;43
Paul Meier;Münchener Weg 1;87654 München;65

Name         |Strasse         |Ort          |Alter|
-------------+----------------+-------------+-----+
Peter Pan    |Am Hang 5       |12345 Einsam |42   |
Maria Schmitz|Kölner Straße 45|50123 Köln   |43   |
Paul Meier   |Münchener Weg 1 |87654 München|65   |
*/
