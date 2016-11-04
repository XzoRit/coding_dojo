#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>

using namespace std;

string score(int, int)
{
  return {"Love-All"};
}

TEST_CASE("score of 0,0")
{
  CHECK(score(0, 0) == "Love-All");
}
