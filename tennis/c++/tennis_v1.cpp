#include <doctest.h>
#include <string>
#include <vector>
#include <map>
#include <optional>

namespace
{
using namespace std;
using namespace std::string_literals;

const auto winning_score = 4;
const auto deuce_border = 3;
const auto sep = '-';
const auto both = "All"s;
const auto winner = "Win for "s;
const auto advantage = "Advantage for "s;
const auto deuce = "Deuce"s;
const auto player1 = "player1"s;
const auto player2 = "player2"s;
const auto score_to_string = vector<string> {"Love", "Fifteen", "Thirty", "Fourty"};
const auto deuce_game_scores = map<int, string>
{
    { 2, winner    + player1},
    {-2, winner    + player2},
    { 1, advantage + player1},
    {-1, advantage + player2},
    { 0, deuce              }
};

const auto is_deuce_game = [](auto score_left, auto score_right)
{
    return
        score_left  >= deuce_border
        &&
        score_right >= deuce_border;
};

const auto has_one_player_won = [](auto score_left, auto score_right) -> optional<string>
{
    if(score_left  == winning_score) return player1;
    if(score_right == winning_score) return player2;
    return nullopt;
};
}
namespace v1
{
const auto score = [](auto score_left, auto score_right)
{
    if(is_deuce_game(score_left, score_right))
    {
        return deuce_game_scores.at(score_left - score_right);
    }

    if(const optional<string> wining_player = has_one_player_won(score_left, score_right))
    {
        return  winner + (*wining_player);
    }

    if(score_left == score_right)
    {
        return score_to_string[score_left] + sep + both;
    }

    return score_to_string[score_left] + sep + score_to_string[score_right];
};

TEST_CASE("score of 0,0")
{
    CHECK(score(0, 0) == "Love-All");
}

TEST_CASE("score of 1,0")
{
    CHECK(score(1, 0) == "Fifteen-Love");
}

TEST_CASE("score of 2,0")
{
    CHECK(score(2, 0) == "Thirty-Love");
}

TEST_CASE("score of 3,0")
{
    CHECK(score(3, 0) == "Fourty-Love");
}

TEST_CASE("score of 0,1")
{
    CHECK(score(0, 1) == "Love-Fifteen");
}

TEST_CASE("score of 0,2")
{
    CHECK(score(0, 2) == "Love-Thirty");
}

TEST_CASE("score of 0,3")
{
    CHECK(score(0, 3) == "Love-Fourty");
}

TEST_CASE("score of 1,1")
{
    CHECK(score(1, 1) == "Fifteen-All");
}

TEST_CASE("score of 2,2")
{
    CHECK(score(2, 2) == "Thirty-All");
}

TEST_CASE("mixed scores")
{
    CHECK(score(1, 2) == "Fifteen-Thirty");
    CHECK(score(2, 1) == "Thirty-Fifteen");

    CHECK(score(1, 3) == "Fifteen-Fourty");
    CHECK(score(3, 1) == "Fourty-Fifteen");

    CHECK(score(2, 3) == "Thirty-Fourty");
    CHECK(score(3, 2) == "Fourty-Thirty");
}

TEST_CASE("score of 4,0")
{
    CHECK(score(4, 0) == "Win for player1");
}

TEST_CASE("score of 0,4")
{
    CHECK(score(0, 4) == "Win for player2");
}

TEST_CASE("deuce")
{
    CHECK(score(3, 3) == "Deuce");
    CHECK(score(4, 4) == "Deuce");
    CHECK(score(5, 5) == "Deuce");
}

TEST_CASE("advantage player1")
{
    CHECK(score(4, 3) == "Advantage for player1");
    CHECK(score(5, 4) == "Advantage for player1");
    CHECK(score(6, 5) == "Advantage for player1");
}

TEST_CASE("advantage player2")
{
    CHECK(score(3, 4) == "Advantage for player2");
    CHECK(score(4, 5) == "Advantage for player2");
    CHECK(score(5, 6) == "Advantage for player2");
}

TEST_CASE("win for player1 after deuce")
{
    CHECK(score(5, 3) == "Win for player1");
    CHECK(score(6, 4) == "Win for player1");
    CHECK(score(7, 5) == "Win for player1");
}

TEST_CASE("win for player2 after deuce")
{
    CHECK(score(3, 5) == "Win for player2");
    CHECK(score(4, 6) == "Win for player2");
    CHECK(score(5, 7) == "Win for player2");
}
}
