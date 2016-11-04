#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>

using namespace std;
using namespace std::string_literals;

string score(int a, int b)
{
  const auto sep{'-'};
  vector<string> numbers =
    {"Love", "Fifteen", "Thirty", "Fourty"};
  if(a) return numbers[a] + sep + numbers[0];
  if(b) return numbers[0] + sep + numbers[b];
  return numbers[0] + sep + "All";
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