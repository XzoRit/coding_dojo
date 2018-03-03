#include <doctest.h>
#include <iostream>
#include <optional>
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
    Thirty,
    Forty
};

point operator++(point p)
{
    if(p == point::Love) return point::Fifteen;
    if(p == point::Fifteen) return point::Thirty;
    if(p == point::Thirty) return point::Forty;
    return p;
}

struct player
{
    string name;
    point points;
};

bool operator==(const player& p1, const player& p2)
{
    return (p1.name == p2.name);
}

struct game
{
    player player_1;
    player player_2;
    optional<player> won_by;
};

struct player_scored
{
    player scored_player;
};

const auto inc_score_of = [](const auto& p)
{
    return player{p.name, ++p.points};
};

const auto update = [](const auto& g, const auto& act)
{
    if(act.scored_player.points == point::Forty)
    {
        return game{g.player_1, g.player_2, act.scored_player};
    }
    if(act.scored_player == g.player_1)
        return game{inc_score_of(g.player_1), g.player_2};
    else return game{g.player_1, inc_score_of(g.player_2)};
};

ostream& operator<<(ostream& str, const point& p)
{
    if(p == point::Love) str << "0";
    else if(p == point::Fifteen) str << "15";
    else if(p == point::Thirty) str << "30";
    else if(p == point::Forty) str << "40";
    return str;
}

ostream& operator<<(ostream& str, const player& p)
{
    str << p.name << ": " << p.points;
    return str;
}

ostream& operator<<(ostream& str, const game& g)
{
    if(g.won_by)
    {
        str << (*g.won_by).name << ": won\n";
    }
    else
    {
        str << g.player_1 << " vs. " << g.player_2;
        str << '\n';
    }
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

    SUBCASE("player_1 scores once")
    {
        const auto g_1 = update(g, player_scored{player_1});
        const auto b = draw(g_1);
        REQUIRE(b == "player_1: 15 vs. player_2: 0\n"s);
        SUBCASE("player_1 twice")
        {
            const auto g_2 = update(g_1, player_scored{g_1.player_1});
            const auto b = draw(g_2);
            REQUIRE(b == "player_1: 30 vs. player_2: 0\n"s);
            SUBCASE("player_1 thrice")
            {
                const auto g_3 = update(g_2, player_scored{g_2.player_1});
                const auto b = draw(g_3);
                REQUIRE(b == "player_1: 40 vs. player_2: 0\n"s);
                SUBCASE("player_1 won")
                {
                    const auto g_4 = update(g_3, player_scored{g_3.player_1});
                    const auto b = draw(g_4);
                    REQUIRE(b == "player_1: won\n"s);
                }
            }
        }
    }
    SUBCASE("player_2 scores")
    {
        const auto g_1 = update(g, player_scored{player_2});
        const auto b = draw(g_1);
        REQUIRE(b == "player_1: 0 vs. player_2: 15\n"s);
    }
}
}
