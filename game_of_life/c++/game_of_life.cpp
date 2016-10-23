#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <initializer_list>

using namespace std;

class Universe
{
public:
    static auto setup(const initializer_list<initializer_list<bool>>& grid)
    {
        return Universe{grid};
    }

    static auto next_generation(const Universe& universe)
    {
        auto newUniverse = universe;

        const auto endX = universe.m_grid.size() - 1;
        const auto endY = universe.m_grid[0].size() - 1;

        for(auto y = 1u; y < endY; ++y)
        {
            for(auto x = 1u; x < endX; ++x)
            {
                auto numOfAliveNeighbours{0};
                numOfAliveNeighbours += universe.m_grid[x-1][y-1];
                numOfAliveNeighbours += universe.m_grid[x  ][y-1];
                numOfAliveNeighbours += universe.m_grid[x+1][y-1];
                numOfAliveNeighbours += universe.m_grid[x-1][y  ];
                numOfAliveNeighbours += universe.m_grid[x+1][y  ];
                numOfAliveNeighbours += universe.m_grid[x-1][y+1];
                numOfAliveNeighbours += universe.m_grid[x  ][y+1];
                numOfAliveNeighbours += universe.m_grid[x+1][y+1];

                newUniverse.m_grid[x][y] =
                    ((numOfAliveNeighbours == 2 && universe.m_grid[x][y])
                     ||
                     (numOfAliveNeighbours == 3));
            }
        }
        return newUniverse;
    }

    friend bool operator==(const Universe& lhs, const Universe& rhs);
    friend ostream& operator<<(ostream&, const Universe& universe);

private:
    Universe(const initializer_list<initializer_list<bool>>& grid)
        : m_grid(cbegin(grid), cend(grid))
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
            Universe::setup(
        {
            {false, false, false},
            {false, true , false},
            {false, false, false}
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
            {false, false, false},
            {false, false, false},
            {false, false, false}
        });

        CHECK(actual == expected);
    }

    SECTION("one living neighbor")
    {
        const auto livingCell =
            Universe::setup(
        {
            {false, false, false},
            {true , true , false},
            {false, false, false}
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
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
            Universe::setup(
        {
            {false, false, true },
            {false, true , false},
            {false, true , false}
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected = livingCell;

        CHECK(actual == expected);
    }

    SECTION("three living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {false, true , false},
            {true , true , true },
            {false, false, false}
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected = livingCell;

        CHECK(actual == expected);
    }
}

TEST_CASE("any live cell with more than three live neighbours dies")
{
    SECTION("four living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {true , false, true },
            {false, true , false},
            {true , true , false}
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
            {true , false, true },
            {false, false, false},
            {true , true , false}
        });

        CHECK(actual == expected);
    }

    SECTION("five living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {false, true , true },
            {true , true , false},
            {true , false, true }
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
            {false, true , true },
            {true , false, false},
            {true , false, true }
        });

        CHECK(actual == expected);
    }

    SECTION("six living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {false, true , true },
            {true , true , false},
            {true , true , true }
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
            {false, true , true },
            {true , false, false},
            {true , true , true }
        });

        CHECK(actual == expected);
    }

    SECTION("seven living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {false, true , true },
            {true , true , true },
            {true , true , true }
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
            {false, true , true },
            {true , false, true },
            {true , true , true }
        });

        CHECK(actual == expected);
    }

    SECTION("eight living neighbors")
    {
        const auto livingCell =
            Universe::setup(
        {
            {true , true , true },
            {true , true , true },
            {true , true , true }
        });

        const auto actual = Universe::next_generation(livingCell);

        const auto expected =
            Universe::setup(
        {
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
        Universe::setup(
    {
        {false, true , false},
        {false, false, true },
        {false, true , false}
    });

    const auto actual = Universe::next_generation(livingCell);

    const auto expected =
        Universe::setup(
    {
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
            Universe::setup(
        {
            {false, false, false, false, false},
            {false, true , true , false, false},
            {false, true , false, true , false},
            {false, false, true , false, false},
            {false, false, false, false, false}
        });
        for(int i = 0; i < 10; ++i)
        {
            const auto actual = Universe::next_generation(expected);
            CHECK(expected == actual);
            expected = actual;
        }
    }
    SECTION("blinker oscilates")
    {
        auto vertical =
            Universe::setup(
        {
            {false, false, false, false, false},
            {false, false, true , false, false},
            {false, false, true , false, false},
            {false, false, true , false, false},
            {false, false, false, false, false}
        });
        auto horizontal =
            Universe::setup(
        {
            {false, false, false, false, false},
            {false, false, false, false, false},
            {false, true , true , true , false},
            {false, false, false, false, false},
            {false, false, false, false, false}
        });
        auto actual = vertical;
        for(int i = 0; i < 10; ++i)
        {
            actual = Universe::next_generation(actual);
            if(i % 2) CHECK(vertical == actual);
            else CHECK(horizontal == actual);
        }
    }
}
