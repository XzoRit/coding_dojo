#include <doctest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>

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
    struct simple
    {
        player player_1;
        player player_2;
    };
    struct winner
    {
        player won_by;
    };
    variant<simple, winner> state;
};

struct player_scored
{
    player scored_player;
};

using action = player_scored;

const auto inc_score_of = [](const auto& p)
{
    return player{p.name, ++p.points};
};

struct do_action
{
    game operator()(const game::simple& g) const
    {
        game new_game{};
        if(act.scored_player == g.player_1
           &&
           g.player_1.points == point::Forty)
        {
            new_game.state =
                game::winner{act.scored_player};
        }
        else if(act.scored_player == g.player_1)
        {
            new_game.state =
                game::simple{inc_score_of(g.player_1), g.player_2};
        }
        else
        {
            new_game.state =
                game::simple{g.player_1, inc_score_of(g.player_2)};
        }
        return new_game;
    }
    game operator()(const game::winner&) const
    {
        return game{};
    }
    action act;
};

const auto update = [](const auto& g, const auto& act)
{
    return visit(do_action{act}, g.state);
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

ostream& operator<<(ostream& str, const game::simple& g)
{
    str << g.player_1 << " vs. " << g.player_2;
    str << '\n';

    return str;
}

ostream& operator<<(ostream& str, const game::winner& g)
{
    str << g.won_by.name << ": won\n";

    return str;
}

ostream& operator<<(ostream& str, const game& g)
{
    visit([&](const auto& a) mutable
          { str << a; }
          , g.state);
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
    game g{};
    g.state = game::simple{player_1, player_2};

    const auto a = draw(g);
    REQUIRE(a == "player_1: 0 vs. player_2: 0\n"s);

    SUBCASE("player_1 scores once")
    {
        const auto g_1 = update(g, player_scored{player_1});
        const auto b = draw(g_1);
        REQUIRE(b == "player_1: 15 vs. player_2: 0\n"s);
        SUBCASE("player_1 twice")
        {
            const auto g_2 = update(g_1, player_scored{player_1});
            const auto b = draw(g_2);
            REQUIRE(b == "player_1: 30 vs. player_2: 0\n"s);
            SUBCASE("player_1 thrice")
            {
                const auto g_3 = update(g_2, player_scored{player_1});
                const auto b = draw(g_3);
                REQUIRE(b == "player_1: 40 vs. player_2: 0\n"s);
                SUBCASE("player_1 won")
                {
                    const auto g_4 = update(g_3, player_scored{player_1});
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
