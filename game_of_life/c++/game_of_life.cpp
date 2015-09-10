#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <initializer_list>

using namespace std;

template<typename T, typename Tag>
class Value
{
public:
  Value(int value)
    : m_value{value}
  {}

  bool operator==(const Value& other) const
  {
    return m_value == other.m_value;
  }

  bool operator!=(const Value& other) const
  {
    return !(*this == other);
  }

  auto value() const
  {
    return m_value;
  }
  
private:    
  int m_value;
};

class Universe
{
public:
  friend bool operator==(const Universe& lhs, const Universe& rhs);
  friend ostream& operator<<(ostream&, const Universe& universe);

  static auto setup(const initializer_list<initializer_list<bool>>& grid)
  {
    auto universe = Universe{};

    for(const auto row : grid)
      {
	auto a = vector<bool>{};
	for(const auto col : row)
	  {
	    a.push_back(col);
	  }
	universe.m_grid.push_back(a);
      }
    
    return universe;
  }

  static auto apply_rules(const Universe& universe)
  {
    auto newUniverse = universe;

    const auto endX = universe.m_grid.size() - 1;
    const auto endY = universe.m_grid[0].size() - 1;

    for(auto y = 1u; y < endY; ++y)
      {
	for(auto x = 1u; x < endX; ++x)
	  {
	    auto alive_count = 0;
	    x -= 1;
	    y -= 1;
	    alive_count += universe.m_grid[x][y];
	    ++y;
	    alive_count += universe.m_grid[x][y];
	    ++y;
	    alive_count += universe.m_grid[x][y];
	    ++x;
	    alive_count += universe.m_grid[x][y];
	    ++x;
	    alive_count += universe.m_grid[x][y];
	    --y;
	    alive_count += universe.m_grid[x][y];
	    --y;
	    alive_count += universe.m_grid[x][y];
	    --x;
	    alive_count += universe.m_grid[x][y];
	    ++y;

	    if(universe.m_grid[x][y])
	      {
		if(alive_count < 2)
		  {
		    newUniverse.m_grid[x][y] = false;
		  }
		else if(alive_count > 3)
		  {
		    newUniverse.m_grid[x][y] = false;
		  }
		else if(alive_count == 2 || alive_count == 3)
		  {
		  }
	      }
	    else
	      {
		if(alive_count == 3)
		  {
		    newUniverse.m_grid[x][y] = true;
		  }
	      }
	  }
      }
    return newUniverse;
  }
  
private:
  Universe()
  {}

  vector<vector<bool>> m_grid;
};

bool operator==(const Universe& lhs, const Universe& rhs)
{
  return (lhs.m_grid == rhs.m_grid);
}

ostream& operator<<(ostream& out, const Universe& universe)
{
  for(const auto row : universe.m_grid)
    {
	for(const auto col : row)
	  {
	    out << (col ? '*' : ' ');
	  }
	out << '\n';
    }
  
  return out;
}

TEST_CASE("any live cell with fewer than two live neighbours dies")
{
  SECTION("no living neighbor")
    {
      const auto livingCell =
	Universe::setup({
	    {false, false, false},
	    {false, true , false},
	    {false, false, false}
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {false, false, false},
    	    {false, false, false},
    	    {false, false, false}
          });

      CHECK(actual == expected);
    }

  SECTION("one living neighbor")
    {
      const auto livingCell =
	Universe::setup({
	    {false, false, false},
	    {true , true , false},
	    {false, false, false}
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {false, false, false},
    	    {true , false, false},
    	    {false, false, false}
          });

      CHECK(actual == expected);
    }
}

TEST_CASE("any live cell with two or three live neighbors lives on")
{
  SECTION("two living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {false, false, true },
	    {false, true , false},
	    {false, true , false}
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected = livingCell;
      
      CHECK(actual == expected);
    }

  SECTION("three living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {false, true , false},
	    {true , true , true },
	    {false, false, false}
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected = livingCell;

      CHECK(actual == expected);
    }
}

TEST_CASE("any live cell with more than three live neighbours dies")
{
  SECTION("four living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {true , false, true },
	    {false, true , false},
	    {true , true , false}
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {true , false, true },
	    {false, false, false},
	    {true , true , false}
          });

      CHECK(actual == expected);
    }

  SECTION("five living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {false, true , true },
	    {true , true , false},
	    {true , false, true }
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {false, true , true },
	    {true , false, false},
	    {true , false, true }
          });

      CHECK(actual == expected);
    }

  SECTION("six living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {false, true , true },
	    {true , true , false},
	    {true , true , true }
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {false, true , true },
	    {true , false, false},
	    {true , true , true }
          });

      CHECK(actual == expected);
    }

  SECTION("seven living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {false, true , true },
	    {true , true , true },
	    {true , true , true }
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {false, true , true },
	    {true , false, true },
	    {true , true , true }
          });

      CHECK(actual == expected);
    }

  SECTION("eight living neighbors")
    {
      const auto livingCell =
	Universe::setup({
	    {true , true , true },
	    {true , true , true },
	    {true , true , true }
	  });

      const auto actual = Universe::apply_rules(livingCell);

      const auto expected =
        Universe::setup({
	    {true , true , true },
	    {true , false, true },
	    {true , true , true }
          });

      CHECK(actual == expected);
    }
}

TEST_CASE("any dead cell with exactly three live neighbours becomes a live cell")
{
  const auto livingCell =
    Universe::setup({
	{false, true , false},
	{false, false, true },
	{false, true , false}
      });

  const auto actual = Universe::apply_rules(livingCell);

  const auto expected =
    Universe::setup({
	{false, true , false},
	{false, true , true },
	{false, true , false}
      });

  CHECK(actual == expected);
}

TEST_CASE("let it run")
{
  SECTION("static start config never changes")
    {
      auto expected =
	Universe::setup({
	    {false, false, false, false, false},  
	    {false, true , true , false, false},  
	    {false, true , false, true , false},  
	    {false, false, true , false, false},  
	    {false, false, false, false, false}   
	  });
      for(int i = 0; i < 10; ++i)
	{
	  const auto actual = Universe::apply_rules(expected);
	  CHECK(expected == actual);
	  expected = actual;
	}
    }
  SECTION("blinker oscilates")
    {
      auto vertical =
	Universe::setup({
	    {false, false, false, false, false},  
	    {false, false, true , false, false},  
	    {false, false, true , false, false},  
	    {false, false, true , false, false},  
	    {false, false, false, false, false}   
	  });
      auto horizontal =
	Universe::setup({
	    {false, false, false, false, false},  
	    {false, false, false, false, false},  
	    {false, true , true , true , false},  
	    {false, false, false, false, false},  
	    {false, false, false, false, false}   
	  });
      auto actual = vertical;
      for(int i = 0; i < 10; ++i)
	{
	  actual = Universe::apply_rules(actual);
	  if(i % 2) CHECK(vertical == actual);
	  else CHECK(horizontal == actual);
	}
    }
}
