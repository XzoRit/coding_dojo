#include <libargs/args.hpp>

int main()
{
  const auto a{ xzr::args::add(1, 3) };
  return (a == 4);
}
