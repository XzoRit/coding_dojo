#include <doctest.h>

#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_key.hpp>

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

namespace fusion = boost::fusion;

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
    struct player_1 {};
    struct player_2 {};
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
        variant<player_1, player_2> leading;
    };
    struct winner
    {
        variant<player_1, player_2> the_one_and_only;
    };
    using state_type = variant<simple, forty, deuce, advantage, winner>;
    state_type state;
};

struct player_1_scored {};
struct player_2_scored {};

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
    return {game::player_1{}};
}

game::winner create_winner_game(const game::forty& g, player_2_scored)
{
    return {game::player_2{}};
}

game::advantage create_advantage_game(const game::deuce& g, player_1_scored)
{
    return game::advantage{game::player_1{}};
}

game::advantage create_advantage_game(const game::deuce& g, player_2_scored)
{
    return game::advantage{game::player_2{}};
}

template<class player_scored>
struct create_deuce_or_winner_game;

template<>
struct create_deuce_or_winner_game<player_1_scored>
{
    game::state_type operator()(const game::player_1& p)
    {
        return game::winner{game::player_1{}};
    }
    game::state_type operator()(const game::player_2&)
    {
        return game::deuce{};
    }
};

template<>
struct create_deuce_or_winner_game<player_2_scored>
{
    game::state_type operator()(const game::player_1&)
    {
        return game::deuce{};
    }
    game::state_type operator()(const game::player_2& p)
    {
        return game::winner{game::player_2{}};
    }
};

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
        return game{visit(create_deuce_or_winner_game<scoring_player>{}, g.leading)};
    }
    game operator()(const game::winner& g) const
    {
        return game{g};
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

using map_player_type_to_name =
    fusion::map<
        fusion::pair<game::player_1, std::string>,
        fusion::pair<game::player_2, std::string>
    >;
map_player_type_to_name player_type_to_name{
    fusion::make_pair<game::player_1>("oscar"),
    fusion::make_pair<game::player_2>("bert")
};

struct player_type_to_string
{
    template<class player_type>
    string operator()(const player_type&)
    {
        return fusion::at_key<player_type>(player_type_to_name);
    }
};

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
    str << "advantage " << visit(player_type_to_string{}, g.leading) << "\n";
    return str;
}

ostream& operator<<(ostream& str, const game::winner& g)
{
    str << visit(player_type_to_string{}, g.the_one_and_only) << ": won\n";
    return str;
}

ostream& operator<<(ostream& str, const game& g)
{
    visit([&str](const auto & a) mutable { str << a; }, g.state);
    return str;
}

string draw(const game& g)
{
    stringstream str;
    str << g;
    return str.str();
}

const auto player_1_name{"oscar"s};
const auto player_2_name{"bert"s};

TEST_CASE("simple game")
{
    const player player_1{player_1_name, point::Love};
    const player player_2{player_2_name, point::Love};
    game g{game::simple{player_1, player_2}};

    auto a = draw(g);
    REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 0\n"s);

    SUBCASE("player_1 scores once")
    {
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 15 vs. " + player_2_name + ": 0\n"s);

        INFO("scores twice");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 30 vs. " + player_2_name + ": 0\n"s);

        INFO("scores thrice");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 40 vs. " + player_2_name + ": 0\n"s);

        INFO("player_1 won");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": won\n"s);
    }
    SUBCASE("player_2 scores once")
    {
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 15\n"s);

        INFO("scores twice");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 30\n"s);

        INFO("scores thrice");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 40\n"s);

        INFO("player_2 won");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "" + player_2_name + ": won\n"s);
    }
}

TEST_CASE("deuce/advantage/win game")
{
    const player player_1{player_1_name, point::Love};
    const player player_2{player_2_name, point::Love};
    game g{game::simple{player_1, player_2}};

    for(int i{}; i < 3; ++i)
    {
        g = update(g, player_1_scored{});
        g = update(g, player_2_scored{});
    }

    INFO("deuce");
    auto a = draw(g);
    REQUIRE(a == "deuce\n"s);

    INFO("advantage " + player_1_name);
    g = update(g, player_1_scored{});
    a = draw(g);
    REQUIRE(a == "advantage " + player_1_name + "\n"s);

    INFO("deuce");
    g = update(g, player_2_scored{});
    a = draw(g);
    REQUIRE(a == "deuce\n"s);

    SUBCASE("player_1 will win")
    {
        INFO("advantage " + player_1_name + "");
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == "advantage " + player_1_name + "\n"s);

        INFO("winner " + player_1_name);
        g = update(g, player_1_scored{});
        a = draw(g);
        REQUIRE(a == player_1_name + ": won\n"s);
    }

    SUBCASE("player_2 will win")
    {
        INFO("advantage " + player_2_name + "");
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "advantage " + player_2_name + "\n"s);

        INFO("winner " + player_2_name);
        g = update(g, player_2_scored{});
        a = draw(g);
        REQUIRE(a == "" + player_2_name + ": won\n"s);
    }
}
}
