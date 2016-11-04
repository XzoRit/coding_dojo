#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <array>

using namespace std;
using namespace std::string_literals;

constexpr auto both_same_score(int score_left, int score_right)
{
  return score_left == score_right;
}

auto score(int score_left, int score_right)
{
  constexpr auto sep{'-'};
  constexpr auto score_to_string =
    array<const char*, 4>{{"Love", "Fifteen", "Thirty", "Fourty"}};
  
  if(both_same_score(score_left, score_right))
    {
      return string{score_to_string[score_left]} + sep + "All";
    }
  
  const auto  left_str = score_to_string[score_left ];
  const auto right_str = score_to_string[score_right];
  
  return string{left_str} + sep + right_str;
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
