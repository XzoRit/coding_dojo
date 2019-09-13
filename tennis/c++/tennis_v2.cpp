#include <doctest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <optional>

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

template<class player_type>
struct player
{
    point points;
};

struct game
{
    struct player_1 {};
    struct player_2 {};
    using player_1_or_player_2 = variant<player_1, player_2>;
    struct simple
    {
        player<player_1> player_1{point::Love};
        player<player_2> player_2{point::Love};
    };
    struct forty
    {
        player_1_or_player_2 leading_player;
        point points_other_players;
    };
    struct deuce
    {
    };
    struct advantage
    {
        player_1_or_player_2 leading;
    };
    struct winner
    {
        player_1_or_player_2 the_one_and_only;
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
    return {game::player_1{}, g.player_2.points};
}

game::forty create_forty_game(const game::simple& g, player_2_scored)
{
    return {game::player_2{}, g.player_1.points};
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
    return std::get_if<game::player_2>(&g.leading_player);
}

bool is_deuce(const game::forty& g, player_2_scored)
{
    return std::get_if<game::player_1>(&g.leading_player);
}

game::simple inc_score_of(const game::simple& g, player_1_scored)
{
    return {{++g.player_1.points}, g.player_2};
}

game::simple inc_score_of(const game::simple& g, player_2_scored)
{
    return {g.player_1, {++g.player_2.points}};
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

struct view
{
    string player_1{};
    string player_2{};

    struct player_to_string
    {
        view* the_view;
        string operator()(const game::player_1&)
        {
            return the_view->player_1;
        }
        string operator()(const game::player_2&)
        {
            return the_view->player_2;
        }
    };
    ostream& draw(ostream& str, const game::simple& g)
    {
        str << player_1 << ": "
            << g.player_1.points << ' '
            << "vs. "
            << player_2 << ": "
            << g.player_2.points << '\n';
        return str;
    }
    ostream& draw(ostream& str, const game::forty& g)
    {
        if(std::get_if<game::player_1>(&g.leading_player))
        {
            str << visit(player_to_string{this}, g.leading_player) << ": " << point::Forty << ' '
                << "vs. "
                << player_2 << ": " << g.points_other_players;
        }
        else
        {
            str << player_1 << ": " << g.points_other_players << ' '
                << "vs. "
                << visit(player_to_string{this}, g.leading_player) << ": " << point::Forty;
        }
        str << '\n';
        return str;
    }
    ostream& draw(ostream& str, game::deuce)
    {
        str << "deuce\n";
        return str;
    }
    ostream& draw(ostream& str, const game::advantage& g)
    {
        str << "advantage " << visit(player_to_string{this}, g.leading) << "\n";
        return str;
    }
    ostream& draw(ostream& str, const game::winner& g)
    {
        str << visit(player_to_string{this}, g.the_one_and_only) << ": won\n";
        return str;
    }
    string draw(const game& g)
    {
      stringstream str;
      visit([this, &str](const auto & a) mutable { draw(str, a); }, g.state);
      return str.str();
    }
};

const auto player_1_name{"john"s};
const auto player_2_name{"jane"s};

TEST_CASE("simple game")
{
    view v{player_1_name, player_2_name};
    game g{game::simple{}};

    auto a = v.draw(g);
    REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 0\n"s);

    SUBCASE("player_1 scores once")
    {
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 15 vs. " + player_2_name + ": 0\n"s);

        INFO("scores twice");
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 30 vs. " + player_2_name + ": 0\n"s);

        INFO("scores thrice");
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 40 vs. " + player_2_name + ": 0\n"s);

        INFO("player_1 won");
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": won\n"s);
    }
    SUBCASE("player_2 scores once")
    {
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 15\n"s);

        INFO("scores twice");
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 30\n"s);

        INFO("scores thrice");
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": 0 vs. " + player_2_name + ": 40\n"s);

        INFO("player_2 won");
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == "" + player_2_name + ": won\n"s);
    }
}

TEST_CASE("deuce/advantage/win game")
{
    view v{player_1_name, player_2_name};
    game g{game::simple{}};

    for(int i{}; i < 3; ++i)
    {
        g = update(g, player_1_scored{});
        g = update(g, player_2_scored{});
    }

    INFO("deuce");
    auto a = v.draw(g);
    REQUIRE(a == "deuce\n"s);

    INFO("advantage " + player_1_name);
    g = update(g, player_1_scored{});
    a = v.draw(g);
    REQUIRE(a == "advantage " + player_1_name + "\n"s);

    INFO("deuce");
    g = update(g, player_2_scored{});
    a = v.draw(g);
    REQUIRE(a == "deuce\n"s);

    SUBCASE("player_1 will win")
    {
        INFO("advantage " + player_1_name + "");
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == "advantage " + player_1_name + "\n"s);

        INFO("winner " + player_1_name);
        g = update(g, player_1_scored{});
        a = v.draw(g);
        REQUIRE(a == player_1_name + ": won\n"s);
    }

    SUBCASE("player_2 will win")
    {
        INFO("advantage " + player_2_name + "");
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == "advantage " + player_2_name + "\n"s);

        INFO("winner " + player_2_name);
        g = update(g, player_2_scored{});
        a = v.draw(g);
        REQUIRE(a == "" + player_2_name + ": won\n"s);
    }
}
}
