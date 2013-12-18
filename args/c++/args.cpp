// clang -I../../../c++/catch/single_include -stdlib=libstd -std=c++11 -o args -c args.cpp
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("", "")
{
  REQUIRE(1 == 0);
}
