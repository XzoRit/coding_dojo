#include <range/v3/action/split.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

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
    using namespace std;
    vector<vector<string>> v{};
    const auto rows = rows_from(txt);
    for(auto&& r : rows)
    {
        v.push_back(cols_from(r));
    }
    return v;
};
    const auto print = [](auto& str, const auto& data) -> decltype(auto)
    {
	using namespace std;
	vector<size_t> col_sizes{};
	for(size_t col = 0; col < data[0].size(); ++col)
	{
	    unsigned max{0};
	    for(size_t row = 0; row < data.size(); ++row)
	    {
		max = (max > data[row][col].size()) ? max : data[row][col].size();
	    }
	    col_sizes.push_back(max);
	}
	for(auto&& r : data)
	{
	    size_t max_idx{0};
	    for(auto&& c : r)
	    {
		str << c << string(col_sizes[max_idx] - c.size(), ' ') << '|';
		++max_idx;
	    }
	    str << '\n';
	}
	return str;
    };
}

using namespace std::string_literals;

TEST_CASE("csv to table")
{
    using xzr::csv::csv_from;
    using xzr::csv::print;
    using std::vector;
    using std::string;

    const auto csv =
        "Name;Strasse;Ort;Alter\n"
        "Peter Pan;Am Hang 5;12345 Einsam;42\n"
        "Maria Schmitz;Koelner Strasse 45;50123 Koeln;43\n"
        "Paul Meier;Muenchener Weg 1;87654 Muenchen;65\n"
	"Franz Kolp;Lange Strsse 15;45276 Holsten;18\n"s;

    const auto expected = vector<vector<string>>
    {
        {"Name","Strasse","Ort","Alter"},
        {"Peter Pan","Am Hang 5","12345 Einsam","42"},
        {"Maria Schmitz","Koelner Strasse 45","50123 Koeln","43"},
        {"Paul Meier","Muenchener Weg 1","87654 Muenchen","65"},
	{"Franz Kolp","Lange Strsse 15","45276 Holsten","18"}
    };
    const auto actual = vector<vector<string>>{csv_from(csv)};
    CHECK(expected == actual);

    std::stringstream str;
    print(str, actual);
    CHECK(str.str() ==
	  "Name         |Strasse           |Ort           |Alter|\n"
	  "Peter Pan    |Am Hang 5         |12345 Einsam  |42   |\n"
	  "Maria Schmitz|Koelner Strasse 45|50123 Koeln   |43   |\n"
	  "Paul Meier   |Muenchener Weg 1  |87654 Muenchen|65   |\n"
	  "Franz Kolp   |Lange Strsse 15   |45276 Holsten |18   |\n");
}
