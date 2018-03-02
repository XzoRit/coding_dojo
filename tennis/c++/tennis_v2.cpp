#include <doctest.h>
#include <string>

namespace
{
}
namespace v2
{
    using namespace std;
    using namespace std::string_literals;

    struct game
    {};

    const auto draw = [](const auto&){ return "0-0"s; };

TEST_CASE("game")
{
    game g{};
    const auto a = draw(g);
    CHECK(a == "0-0");
}
}
