#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>

using namespace std;
using namespace std::string_literals;

bool no_one_scored_yet(int score_left, int score_right)
{
  return !(score_left || score_right);
}

string score(int score_left, int score_right)
{
  if(no_one_scored_yet(score_left, score_right)) return "Love-All";
  
  const auto sep{'-'};
  const auto numbers = vector<string>{"Love", "Fifteen", "Thirty", "Fourty"};
  
  auto  left_str = numbers[score_left ];
  auto right_str = numbers[score_right];
  
  return left_str + sep + right_str;
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
