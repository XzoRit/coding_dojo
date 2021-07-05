#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

using std::variant;
using std::visit;

class Quality
{
  public:
    static int max()
    {
        return 50;
    }

    static int min()
    {
        return 0;
    }
};

class Article
{
  public:
    Article(std::string name, int sellIn, int quality);
    void update();

  private:
    std::string name;
    int sellIn;
    int quality;

    friend bool operator==(const Article& a, const Article& b);
    friend bool operator!=(const Article& a, const Article& b);
    friend std::ostream& operator<<(std::ostream& o, const Article& a);
};

Article::Article(std::string name, int sellIn, int quality)
    : name{name}
    , sellIn{sellIn}
    , quality{quality}
{
}

void Article::update()
{
    if (sellIn > 0)
    {
        --quality;
    }
    else
    {
        quality -= 2;
    }
    if (quality < Quality::min())
    {
        quality = Quality::min();
    }
    --sellIn;
}

bool operator==(const Article& a, const Article& b)
{
    return (a.sellIn == b.sellIn) && (a.quality == b.quality) && (a.name == b.name);
}

bool operator!=(const Article& a, const Article& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, const Article& a)
{
    o << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

class AgedBrie
{
  public:
    AgedBrie(int quality);
    void update();

  private:
    int quality;

    friend bool operator==(const AgedBrie& a, const AgedBrie& b);
    friend bool operator!=(const AgedBrie& a, const AgedBrie& b);
    friend std::ostream& operator<<(std::ostream& o, const AgedBrie& a);
};

AgedBrie::AgedBrie(int quality)
    : quality{quality}
{
}

void AgedBrie::update()
{
    if (quality < Quality::max())
    {
        ++quality;
    }
}

bool operator==(const AgedBrie& a, const AgedBrie& b)
{
    return a.quality == b.quality;
}

bool operator!=(const AgedBrie& a, const AgedBrie& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, const AgedBrie& a)
{
    o << "Aged Brie, " << a.quality;
    return o;
}

class BackstagePass
{
  public:
    BackstagePass(std::string concert, int sellIn, int quality);
    void update();

  private:
    std::string concert;
    int sellIn;
    int quality;

    friend bool operator==(const BackstagePass& a, const BackstagePass& b);
    friend bool operator!=(const BackstagePass& a, const BackstagePass& b);
    friend std::ostream& operator<<(std::ostream& o, const BackstagePass& b);
};

BackstagePass::BackstagePass(std::string concert, int sellIn, int quality)
    : concert{concert}
    , sellIn{sellIn}
    , quality{quality}
{
}

void BackstagePass::update()
{
    if (sellIn <= 0)
    {
        quality = Quality::min();
    }
    else if (sellIn < 6)
    {
        quality += 3;
    }
    else if (sellIn < 11)
    {
        quality += 2;
    }
    else
    {
        ++quality;
    }
    if (quality > Quality::max())
    {
        quality = Quality::max();
    }
    --sellIn;
}

bool operator==(const BackstagePass& a, const BackstagePass& b)
{
    return (a.quality == b.quality) && (a.sellIn == b.sellIn) && (a.concert == b.concert);
}

bool operator!=(const BackstagePass& a, const BackstagePass& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, const BackstagePass& b)
{
    o << "Backstage pass for " << b.concert << ", " << b.sellIn << ", " << b.quality;
    return o;
}

class Sulfuras
{
  private:
    friend std::ostream& operator<<(std::ostream& o, const Sulfuras& s);
};

std::ostream& operator<<(std::ostream& o, const Sulfuras& s)
{
    o << "Sulfuras";
    return o;
}

class Conjured
{
  public:
    Conjured(std::string name, int sellIn, int quality);
    void update();

  private:
    std::string name;
    int sellIn;
    int quality;

    friend bool operator==(const Conjured& a, const Conjured& b);
    friend bool operator!=(const Conjured& a, const Conjured& b);
    friend std::ostream& operator<<(std::ostream& o, const Conjured& a);
};

Conjured::Conjured(std::string name, int sellIn, int quality)
    : name{name}
    , sellIn{sellIn}
    , quality{quality}
{
}

void Conjured::update()
{
    if (sellIn > 0)
    {
        quality -= 2;
    }
    else
    {
        quality -= 4;
    }
    if (quality < Quality::min())
    {
        quality = Quality::min();
    }
    --sellIn;
}

bool operator==(const Conjured& a, const Conjured& b)
{
    return (a.sellIn == b.sellIn) && (a.quality == b.quality) && (a.name == b.name);
}

bool operator!=(const Conjured& a, const Conjured& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& o, const Conjured& a)
{
    o << "Conjured " << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

class GildedRose
{
  public:
    using Item = variant<Article, AgedBrie, BackstagePass, Sulfuras, Conjured>;

    void add(Item);
    void update();

  private:
    using Articles = std::vector<Item>;
    Articles articles;

    friend std::ostream& operator<<(std::ostream& o, GildedRose const& g);

    struct Update
    {
        template <class T>
        void operator()(T& t) const
        {
            t.update();
        }

        void operator()(Sulfuras) const
        {
        }
    };

    struct OStream
    {
        explicit OStream(std::ostream* o)
            : o{o}
        {
        }

        template <class T>
        void operator()(const T& t) const
        {
            (*o) << t << '\n';
        }

        std::ostream* o;
    };
};

void GildedRose::add(Item it)
{
    articles.push_back(it);
}

void GildedRose::update()
{
    Update update{};
    for (auto& item : articles)
        visit(update, item);
}

std::ostream& operator<<(std::ostream& o, GildedRose const& g)
{
    GildedRose::OStream stream{&o};
    o << "name, sellIn, quality\n";
    for (const auto& item : g.articles)
        visit(stream, item);

    return o;
}

#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_COLORS_NONE
// #define DOCTEST_CONFIG_DISABLE
#include <doctest.h>

int main(int argc, const char** argv)
{
    doctest::Context context{};
    context.applyCommandLine(argc, argv);
    const int res{context.run()};
    if (context.shouldExit() || res != 0)
        return res;

    GildedRose store{};
    store.add(Article("+5 Dexterity Vest", 10, 20));
    store.add(AgedBrie(0));
    store.add(Article("Elixir of the Mongoose", 5, 7));
    store.add(Sulfuras());
    store.add(Sulfuras());
    store.add(BackstagePass("TAFKAL80ETC concert", 15, 20));
    store.add(BackstagePass("TAFKAL80ETC concert", 10, 49));
    store.add(BackstagePass("TAFKAL80ETC concert", 5, 49));
    store.add(Conjured("Sword of Gold", 5, 21));

    std::cout << "GildedRose\n";
    for (int day{0}; day <= 30; ++day)
    {
        std::cout << "-------- day " << day << " --------\n";
        store.update();
        std::cout << store << "\n\n";
    }

    return 0;
}

SCENARIO("article with positive sellin is updated")
{
    GIVEN("an article with positive sellin")
    {
        const int quality{7};
        const int sellIn{16};
        const std::string name{"article"};
        Article a{name, sellIn, quality};
        WHEN("it is updated")
        {
            a.update();
            THEN("quality and sellin are decremented by 1")
            {
                CHECK(a == Article{name, sellIn - 1, quality - 1});
            }
        }
    }
}

SCENARIO("article with sellin of 0 is updated")
{
    GIVEN("an aritcle with a sellin value of 0")
    {
        const int quality{7};
        const int sellIn{0};
        const std::string name{"article"};
        Article a{name, sellIn, quality};
        WHEN("it is updated")
        {
            a.update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(a == Article{name, sellIn - 1, quality - 2});
            }
        }
    }
}

SCENARIO("article with min quality is updated")
{
    GIVEN("an article with min quality")
    {
        const int sellIn{0};
        const std::string name{"article"};
        Article a{name, sellIn, Quality::min()};
        WHEN("it is updated")
        {
            a.update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(a == Article{name, sellIn - 1, Quality::min()});
            }
        }
    }
}

SCENARIO("aged brie is updated")
{
    GIVEN("an aged brie")
    {
        const int quality{28};
        AgedBrie a{quality};
        WHEN("it is updated")
        {
            a.update();
            THEN("quality increases by 1")
            {
                CHECK(a == AgedBrie{quality + 1});
            }
        }
    }
}

SCENARIO("aged brie with max quality is updated")
{
    GIVEN("an aged brie with max quality")
    {
        AgedBrie a{Quality::max()};
        WHEN("it is updated")
        {
            a.update();
            THEN("quality does not change")
            {
                CHECK(a == AgedBrie{Quality::max()});
            }
        }
    }
}

SCENARIO("backstage pass with sellin over 10 is updated")
{
    GIVEN("a backstage pass with sellin over 10")
    {
        const int quality{41};
        const int sellIn{11};
        const std::string concert{"x.y.u."};
        BackstagePass b{concert, sellIn, quality};
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increases by 1 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, quality + 1});
            }
        }
    }
}

SCENARIO("backstage pass with sellin over 10 and max quality is updated")
{
    GIVEN("a backstage pass with sellin over 10 and max quality")
    {
        const int sellIn{11};
        const std::string concert{"x.y.u."};
        BackstagePass b{concert, sellIn, Quality::max()};
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increases does not change and sellin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, Quality::max()});
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 10 is updated")
{
    GIVEN("a backstage with sellin of 10")
    {
        const int quality{41};
        const int sellIn{10};
        const std::string concert{"x.y.u."};
        BackstagePass b{concert, sellIn, quality};
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increaes by 2 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, quality + 2});
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 10 and quality 1 under max is updated")
{
    GIVEN("a backstage pass with sellin of 10 and quality 1 under max")
    {
        const int quality{Quality::max() - 1};
        const int sellIn{10};
        const std::string concert{"x.y.u."};
        BackstagePass b{concert, sellIn, quality};
        WHEN("it is updated")
        {
            b.update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, Quality::max()});
            }
        }
    }
}
SCENARIO("backstage pass with sellin of 5 is updated")
{
    GIVEN("a backstage with sellin of 5")
    {
        const int quality{41};
        const int sellIn{5};
        const std::string concert{"x.y.u."};
        BackstagePass b{concert, sellIn, quality};
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increaes by 3 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, quality + 3});
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 5 and quality 1 under max is updated")
{
    GIVEN("a backstage pass with sellin of 5 and quality 1 under max")
    {
        const int quality{Quality::max() - 1};
        const int sellIn{5};
        const std::string concert{"x.y.u."};
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, Quality::max()});
            }
        }
    }
}

SCENARIO("backstage pass for a passed concert is updated")
{
    GIVEN("a backstage pass with sellin of 0")
    {
        const int quality{41};
        const int sellIn{0};
        const std::string concert{"x.y.u."};
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality value is is set to min and sellin is decreased by 1")
            {
                CHECK(b == BackstagePass{concert, sellIn - 1, Quality::min()});
            }
        }
    }
}

SCENARIO("sulfuras is updated")
{
    GIVEN("sulfuras")
    {
        Sulfuras s;
        WHEN("it is updated")
        {
            THEN("neither quality nor sellin change")
            {
            }
        }
    }
}

SCENARIO("conjured article with positive sellin is updated")
{
    GIVEN("a conjured article with positive sellin")
    {
        const int quality{7};
        const int sellIn{16};
        const std::string name{"conjured article"};
        Conjured c(name, sellIn, quality);
        WHEN("it is updated")
        {
            c.update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(c == Conjured{name, sellIn - 1, quality - 2});
            }
        }
    }
}

SCENARIO("conjured article with sellin of 0 is updated")
{
    GIVEN("a conjured aritcle with a sellin value of 0")
    {
        const int quality{7};
        const int sellIn{0};
        const std::string name{"conjured article"};
        Conjured c(name, sellIn, quality);
        WHEN("it is updated")
        {
            c.update();
            THEN("quality is decremented by 4 and sellin is decremented by 1")
            {
                CHECK(c == Conjured{name, sellIn - 1, quality - 4});
            }
        }
    }
}

SCENARIO("conjured article with min quality is updated")
{
    GIVEN("a conjured article with min quality")
    {
        const int sellIn{0};
        const std::string name{"conjured article"};
        Conjured c(name, sellIn, Quality::min());
        WHEN("it is updated")
        {
            c.update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(c == Conjured{name, sellIn - 1, Quality::min()});
            }
        }
    }
}
