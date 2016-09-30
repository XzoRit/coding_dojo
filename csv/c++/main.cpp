#include <range/v3/action/split.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/tail.hpp>
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
const auto rows_from = [](const auto& csv_text)
{
    return impl::split_by(csv_text, '\n');
};
const auto cols_from = [](const auto& csv_row)
{
    return impl::split_by(csv_row, ';');
};
const auto by_colums = [](const auto& data)
{
    using namespace std;
    vector<vector<string>> cols;
    for(size_t col = 0; col < data[0].size(); ++col)
    {
        vector<string> col_data;
        for(size_t row = 0; row < data.size(); ++row)
        {
            col_data.push_back(data[row][col]);
        }
        cols.push_back(col_data);
    }
    return cols;
};
const auto max_size_of_each_col = [](const auto& data)
{
    using namespace std;
    vector<size_t> col_sizes;
    for(const auto& c : by_colums(data))
    {
        const auto m =
            ranges::accumulate(
                c,
                size_t{0},
                [](const auto& a, const auto& b)
        {
            return max(a, b.size());
        });
        col_sizes.push_back(m);
    }

    return col_sizes;
};
const auto format_row =
    [](auto& str, const auto& row, const auto& col_sizes)
{
    using namespace std;

    size_t max_idx{0};
    for(auto&& c : row)
    {
        str << c << string(col_sizes[max_idx] - c.size(), ' ') << '|';
        ++max_idx;
    }
};
const auto format_separator = [](const auto& col_sizes)
{
    using namespace std;
    string separator;
    for(auto size : col_sizes)
    {
	separator += string(size, '-') + '+';
    }
    return separator;
};
const auto print =
    [](auto& str, const auto& data) -> decltype(auto)
{
    using namespace std;

    const auto col_sizes = max_size_of_each_col(data);

    format_row(str, data[0], col_sizes);
    str << '\n';

    str << format_separator(col_sizes);
    str << '\n';

    for(auto&& r : ranges::view::tail(data))
    {
	format_row(str, r, col_sizes);
        str << '\n';
    }
    return str;
};
}
struct csv_type
{
    using data_type = std::vector<std::vector<std::string>>;
    using cols_type = data_type;
    using rows_type = data_type;
    explicit csv_type(const data_type& data)
        : m_data(data)
    {}
    const data_type data() const
    {
        return m_data;
    }
    const rows_type rows() const
    {
        return m_data;
    }
    const cols_type cols() const
    {
        return impl::by_colums(m_data);
    }
private:
    data_type m_data;
};
std::ostream& operator<<(std::ostream& str, const csv_type& csv)
{
    return impl::print(str, csv.data());
}
auto csv_from(const std::string& txt) -> csv_type
{
    using namespace std;
    vector<vector<string>> v{};
    const auto rows = impl::rows_from(txt);
    for(auto&& r : rows)
    {
        v.push_back(impl::cols_from(r));
    }
    return csv_type{v};
};
}

using namespace std::string_literals;

TEST_CASE("csv to table")
{
    using xzr::csv::csv_from;
    using std::vector;
    using std::string;

    const auto csv =
        "Name;Strasse;Ort;Alter\n"
        "Peter Pan;Am Hang 5;12345 Einsam;42\n"
        "Maria Schmitz;Koelner Strasse 45;50123 Koeln;43\n"
        "Paul Meier;Muenchener Weg 1;87654 Muenchen;65\n"
        "Franz Kolp;Lange Strsse 15;45276 Holsten;18\n"s;

    std::stringstream str;
    str << csv_from(csv);
    CHECK(str.str() ==
          "Name         |Strasse           |Ort           |Alter|\n"
          "-------------+------------------+--------------+-----+\n"
          "Peter Pan    |Am Hang 5         |12345 Einsam  |42   |\n"
          "Maria Schmitz|Koelner Strasse 45|50123 Koeln   |43   |\n"
          "Paul Meier   |Muenchener Weg 1  |87654 Muenchen|65   |\n"
          "Franz Kolp   |Lange Strsse 15   |45276 Holsten |18   |\n");
}
