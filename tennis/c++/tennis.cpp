#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <vector>

using namespace std;
using namespace std::string_literals;

string score(int score_left, int score_right)
{
  const auto sep{'-'};
  const auto score_to_string =
    vector<string>{"Love", "Fifteen", "Thirty", "Fourty"};

  if(score_left == 4) return "Win for player1";

  if(score_right == 4) return "Win for player2";

  if(score_left == score_right)
    {
      if(score_left == 3) return "Deuce";
      return score_to_string[score_left] + sep + "All";
    }
  
  return score_to_string[score_left] + sep + score_to_string[score_right];
}

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

TEST_CASE("deuce at score of 3,3")
{
  CHECK(score(3, 3) == "Deuce");
}
