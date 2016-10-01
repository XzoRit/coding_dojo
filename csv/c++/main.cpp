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
const auto rows_from = [](const auto& csv_text)
{
    using ranges::action::split;
    return split(csv_text, '\n');
};
const auto cols_from = [](const auto& csv_row)
{
    using ranges::action::split;
    return split(csv_row, ';');
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
const auto max_size_per_col = [](const auto& data)
{
    using namespace std;
    vector<size_t> col_sizes;
    const auto by_max_size = [](const auto& a, const auto& b)
    {
	return max(a, b.size());
    };
    
    for(const auto& c : by_colums(data))
    {
        const auto m = ranges::accumulate(c, size_t{0}, by_max_size);
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
const auto print = [](auto& str, const auto& data)
{
    using namespace std;
    using ranges::view::tail;

    const auto col_sizes = max_size_per_col(data);

    format_row(str, data[0], col_sizes);
    str << '\n';

    str << format_separator(col_sizes);
    str << '\n';

    for(auto&& r : tail(data))
    {
        format_row(str, r, col_sizes);
        str << '\n';
    }
};
}
struct type
{
    using data_type = std::vector<std::vector<std::string>>;
    using cols_type = data_type;
    using rows_type = data_type;
    explicit type(const data_type& data)
        : m_data(data)
    {}
    const data_type& rows() const
    {
        return m_data;
    }
    const cols_type& cols() const
    {
        return impl::by_colums(m_data);
    }
private:
    data_type m_data;
};
std::ostream& operator<<(std::ostream& str, const type& csv)
{
    impl::print(str, csv.rows());
    return str;
}
const auto from = [](const std::string& txt)
{
    using namespace std;
    vector<vector<string>> v;
    const auto rows = impl::rows_from(txt);
    for(auto&& r : rows)
    {
        v.push_back(impl::cols_from(r));
    }
    return type{v};
};
}

using namespace std::string_literals;

TEST_CASE("csv to table")
{
    using namespace xzr;
    using std::vector;
    using std::string;

    const auto csv =
        "Name;Strasse;Ort;Alter\n"
        "Peter Pan;Am Hang 5;12345 Einsam;42\n"
        "Maria Schmitz;Koelner Strasse 45;50123 Koeln;43\n"
        "Paul Meier;Muenchener Weg 1;87654 Muenchen;65\n"
        "Franz Kolp;Lange Strsse 15;45276 Holsten;18\n"s;

    std::stringstream str;
    str << csv::from(csv);
    CHECK(str.str() ==
          "Name         |Strasse           |Ort           |Alter|\n"
          "-------------+------------------+--------------+-----+\n"
          "Peter Pan    |Am Hang 5         |12345 Einsam  |42   |\n"
          "Maria Schmitz|Koelner Strasse 45|50123 Koeln   |43   |\n"
          "Paul Meier   |Muenchener Weg 1  |87654 Muenchen|65   |\n"
          "Franz Kolp   |Lange Strsse 15   |45276 Holsten |18   |\n");
}
