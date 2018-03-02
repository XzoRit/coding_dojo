#include <doctest.h>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
}
namespace v2
{
    using namespace std;
    using namespace std::string_literals;

    enum class point
    {
        Love,
        Fifteen,
        Thirty
    };

    point operator++(point p)
    {
        if(p == point::Love) return point::Fifteen;
        if(p == point::Fifteen) return point::Thirty;
        return p;
    }

    struct player
    {
        string name;
        point points;
    };

    struct game
    {
        player player_1;
        player player_2;
    };

    struct player_scored
    {
        player scored_player;
    };

    const auto inc_score_of = [](const auto& p)
    {
        return player{p.name, ++p.points};
    };

    const auto update = [](const auto& g, const auto&)
    {
        return game{inc_score_of(g.player_1), g.player_2};
    };

    ostream& operator<<(ostream& str, const point& p)
    {
        if(p == point::Love) str << "0";
        else if(p == point::Fifteen) str << "15";
        else if(p == point::Thirty) str << "30";
        return str;
    }

    ostream& operator<<(ostream& str, const player& p)
    {
        str << p.name << ": " << p.points;
        return str;
    }

    ostream& operator<<(ostream& str, const game& g)
    {
        str << g.player_1 << " vs. " << g.player_2;
        str << '\n';
        return str;
    }

    const auto draw = [](const auto& game)
    {
        stringstream str;
        str << game;
        return str.str();
    };

TEST_CASE("game")
{
    const player player_1{"player_1", point::Love};
    const player player_2{"player_2", point::Love};
    const game g{player_1, player_2};
    const auto a = draw(g);
    REQUIRE(a == "player_1: 0 vs. player_2: 0\n"s);

    const auto new_g = update(g, player_scored{player_1});
    const auto b = draw(new_g);
    REQUIRE(b == "player_1: 15 vs. player_2: 0\n"s);
}
}
