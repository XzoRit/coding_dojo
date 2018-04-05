#include <doctest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <optional>

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

bool operator!=(const player& p1, const player& p2)
{
    return !(p1.name == p2.name);
}

player inc_score_of(const player& p)
{
    return player{p.name, ++p.points};
}

struct game
{
    struct simple
    {
        player player_1;
        player player_2;
    };
    struct forty
    {
        player player_1;
        player player_2;
    };
    struct deuce
    {
    };
    struct advantage
    {
        player leading;
    };
    struct winner
    {
        string won_by;
    };
    variant<simple, forty, deuce, advantage, winner> state;
};

struct player_1_scored
{};

struct player_2_scored
{};

using score_action = variant<player_1_scored, player_2_scored>;

bool scorer_gets_forty_points(const game::simple& g, player_1_scored)
{
    return g.player_1.points == point::Thirty;
}

bool scorer_gets_forty_points(const game::simple& g, player_2_scored)
{
    return g.player_2.points == point::Thirty;
}

game::forty create_forty_game(const game::simple& g, player_1_scored)
{
    return {inc_score_of(g.player_1), g.player_2};
}

game::forty create_forty_game(const game::simple& g, player_2_scored)
{
    return {g.player_1, inc_score_of(g.player_2)};
}

game::winner create_winner_game(const game::forty& g, player_1_scored)
{
    return {g.player_1.name};
}

game::winner create_winner_game(const game::forty& g, player_2_scored)
{
    return {g.player_2.name};
}

game::advantage create_advantage_game(const game::deuce& g, player_1_scored)
{
    return game::advantage{};
}

game::advantage create_advantage_game(const game::deuce& g, player_2_scored)
{
    return game::advantage{};
}

bool is_deuce(const game::forty& g, player_1_scored)
{
    return
        g.player_1.points == point::Thirty &&
        g.player_2.points == point::Forty;
}

bool is_deuce(const game::forty& g, player_2_scored)
{
    return
        g.player_1.points == point::Forty &&
        g.player_2.points == point::Thirty;
}

optional<player> has_winner(const game::simple& g)
{
    if(g.player_1.points == point::Forty) return g.player_1;
    if(g.player_2.points == point::Forty) return g.player_2;
    else return nullopt;
}

game::simple inc_score_of(const game::simple& g, player_1_scored)
{
    return {inc_score_of(g.player_1), g.player_2};
}

game::simple inc_score_of(const game::simple& g, player_2_scored)
{
    return {g.player_1, inc_score_of(g.player_2)};
}

template<class scoring_player>
struct update_game_state
{
    game operator()(const game::simple& g) const
    {
        if(scorer_gets_forty_points(g, scoring_player{}))
            return game{create_forty_game(g, scoring_player{})};
        else
            return game{inc_score_of(g, scoring_player{})};
    }
    game operator()(const game::forty& g) const
    {
        if(is_deuce(g, scoring_player{}))
            return game{game::deuce{}};
        else
            return game{create_winner_game(g, scoring_player{})};
    }
    game operator()(const game::deuce& g) const
    {
        return game{create_advantage_game(g, scoring_player{})};
    }
    game operator()(const game::advantage& g) const
    {
        return game{g};
    }
    game operator()(const game::winner&) const
    {
        return game{};
    }
};

struct apply_score_action
{
    template<class scoring_player>
    game operator()(scoring_player) const
    {
        return visit(update_game_state<scoring_player> {}, current.state);
    }
    const game& current;
};

game update(const game& g, const score_action& player_scored)
{
    return visit(apply_score_action{g}, player_scored);
}

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

ostream& operator<<(ostream& str, const game::forty& g)
{
    str << g.player_1 << " vs. " << g.player_2;
    str << '\n';
    return str;
}

ostream& operator<<(ostream& str, game::deuce)
{
    str << "deuce\n";
    return str;
}

ostream& operator<<(ostream& str, const game::advantage& g)
{
    str << "advantage " << g.leading.name << "\n";
    return str;
}

ostream& operator<<(ostream& str, const game::winner& g)
{
    str << g.won_by << ": won\n";
    return str;
}

ostream& operator<<(ostream& str, const game& g)
{
    visit([&](const auto & a) mutable { str << a; }, g.state);
    return str;
}

string draw(const game& g)
{
    stringstream str;
    str << g;
    return str.str();
}

TEST_CASE("simple game")
{
    const player player_1{"player_1", point::Love};
    const player player_2{"player_2", point::Love};
    game g{game::simple{player_1, player_2}};

    auto a = draw(g);
    REQUIRE(a == "player_1: 0 vs. player_2: 0\n"s);

    SUBCASE("player_1 scores once")
    {
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 15 vs. player_2: 0\n"s);

        INFO("scores twice");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 30 vs. player_2: 0\n"s);

        INFO("scores thrice");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 40 vs. player_2: 0\n"s);

        INFO("player_1 won");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: won\n"s);
    }
    SUBCASE("player_2 scores once")
    {
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 0 vs. player_2: 15\n"s);

        INFO("scores twice");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 0 vs. player_2: 30\n"s);

        INFO("scores thrice");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "player_1: 0 vs. player_2: 40\n"s);

        INFO("player_2 won");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "player_2: won\n"s);
    }
}

TEST_CASE("deuce/advantage/win game")
{
    const player player_1{"player_1", point::Love};
    const player player_2{"player_2", point::Love};
    game g{game::simple{player_1, player_2}};

    for(int i{}; i < 3; ++i)
    {
        g = update(g, player_1_scored{});
        g = update(g, player_2_scored{});
    }

    INFO("deuce");
    auto a = draw(g);
    REQUIRE(a == "deuce\n"s);

    INFO("advantage player_1");
    g = update(g, player_1_scored{});
    a = draw(g);
    REQUIRE(a == "advantage player_1\n"s);
}
}
