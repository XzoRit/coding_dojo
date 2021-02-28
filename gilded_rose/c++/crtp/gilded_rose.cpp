#include <iostream>
#include <ostream>
#include <string>

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

template <class It>
class Item
{
  public:
    void update();
};

template <class It>
void Item<It>::update()
{
    It& self = *static_cast<It*>(this);
    self.on_update();
}

template <class It>
void updateItem(Item<It>& item)
{
    item.update();
}

class Article : public Item<Article>
{
  public:
    Article(std::string name, int sellIn, int quality);
    void on_update();

    bool operator==(Article const&) const;
    bool operator!=(Article const&) const;

  private:
    std::string const name;
    int sellIn;
    int quality;

    friend std::ostream& operator<<(std::ostream& o, Article const& a);
};

Article::Article(std::string name, int sellIn, int quality)
    : name(name)
    , sellIn(sellIn)
    , quality(quality)
{
}

void Article::on_update()
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

bool Article::operator==(Article const& other) const
{
    return (sellIn == other.sellIn) && (quality == other.quality) && (name == other.name);
}

bool Article::operator!=(Article const& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& o, Article const& a)
{
    o << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

class AgedBrie : public Item<AgedBrie>
{
  public:
    AgedBrie(int quality);
    void on_update();

    bool operator==(AgedBrie const& other) const;
    bool operator!=(AgedBrie const& other) const;

  private:
    int quality;

    friend std::ostream& operator<<(std::ostream& o, AgedBrie const& a);
};

AgedBrie::AgedBrie(int quality)
    : quality(quality)
{
}

void AgedBrie::on_update()
{
    if (quality < Quality::max())
    {
        ++quality;
    }
}

bool AgedBrie::operator==(AgedBrie const& other) const
{
    return quality == other.quality;
}

bool AgedBrie::operator!=(AgedBrie const& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& o, AgedBrie const& a)
{
    o << "Aged Brie, " << a.quality;
    return o;
}

class BackstagePass : public Item<BackstagePass>
{
  public:
    BackstagePass(std::string concert, int sellIn, int quality);
    void on_update();

    bool operator==(BackstagePass const& other) const;
    bool operator!=(BackstagePass const& other) const;

  private:
    std::string concert;
    int sellIn;
    int quality;

    friend std::ostream& operator<<(std::ostream& o, BackstagePass const& b);
};

BackstagePass::BackstagePass(std::string concert, int sellIn, int quality)
    : concert(concert)
    , sellIn(sellIn)
    , quality(quality)
{
}

void BackstagePass::on_update()
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

bool BackstagePass::operator==(BackstagePass const& other) const
{
    return (quality == other.quality) && (sellIn == other.sellIn) && (concert == other.concert);
}

bool BackstagePass::operator!=(BackstagePass const& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& o, BackstagePass const& b)
{
    o << "Backstage pass for " << b.concert << ", " << b.sellIn << ", " << b.quality;
    return o;
}

class Sulfuras : public Item<Sulfuras>
{
  public:
    void on_update();

  private:
    friend std::ostream& operator<<(std::ostream& o, Sulfuras const& s);
};

void Sulfuras::on_update()
{
}

std::ostream& operator<<(std::ostream& o, Sulfuras const& s)
{
    o << "Sulfuras";
    return o;
}

class Conjured : public Item<Conjured>
{
  public:
    Conjured(std::string name, int sellIn, int quality);
    void on_update();

    bool operator==(Conjured const&) const;
    bool operator!=(Conjured const&) const;

  private:
    std::string name;
    int sellIn;
    int quality;

    friend std::ostream& operator<<(std::ostream& o, Conjured const& a);
};

Conjured::Conjured(std::string name, int sellIn, int quality)
    : name(name)
    , sellIn(sellIn)
    , quality(quality)
{
}

void Conjured::on_update()
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

bool Conjured::operator==(Conjured const& other) const
{
    return (sellIn == other.sellIn) && (quality == other.quality) && (name == other.name);
}

bool Conjured::operator!=(Conjured const& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& o, Conjured const& a)
{
    o << "Conjured " << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

class GildedRose
{
  public:
    void update();

  private:
    Article a{"+5 Dexterity Vest", 10, 20};
    AgedBrie b{0};
    Article c{"Elixir of the Mongoose", 5, 7};
    Sulfuras d{};
    Sulfuras e{};
    BackstagePass f{"TAFKAL80ETC concert", 15, 20};
    BackstagePass g{"TAFKAL80ETC concert", 10, 49};
    BackstagePass h{"TAFKAL80ETC concert", 5, 49};
    Conjured i{"Sword of Gold", 5, 21};

    friend std::ostream& operator<<(std::ostream& o, GildedRose const& g);
};

void GildedRose::update()
{
    updateItem(a);
    updateItem(b);
    updateItem(c);
    updateItem(d);
    updateItem(e);
    updateItem(f);
    updateItem(g);
    updateItem(h);
    updateItem(i);
}

std::ostream& operator<<(std::ostream& o, GildedRose const& g)
{
    o << "name, sellIn, quality\n";
    o << g.a << '\n';
    o << g.b << '\n';
    o << g.c << '\n';
    o << g.d << '\n';
    o << g.e << '\n';
    o << g.f << '\n';
    o << g.g << '\n';
    o << g.h << '\n';
    o << g.i << '\n';

    return o;
}

#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_COLORS_NONE
#include <doctest.h>

SCENARIO("article with positive sellin is updated")
{
    GIVEN("an article with positive sellin")
    {
        int const quality = 7;
        int const sellIn = 16;
        std::string const name = "article";
        Article a(name, sellIn, quality);
        WHEN("it is updated")
        {
            a.update();
            THEN("quality and sellin are decremented by 1")
            {
                CHECK(a == Article(name, sellIn - 1, quality - 1));
            }
        }
    }
}

SCENARIO("article with sellin of 0 is updated")
{
    GIVEN("an aritcle with a sellin value of 0")
    {
        int const quality = 7;
        int const sellIn = 0;
        std::string const name = "article";
        Article a(name, sellIn, quality);
        WHEN("it is updated")
        {
            a.update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(a == Article(name, sellIn - 1, quality - 2));
            }
        }
    }
}

SCENARIO("article with min quality is updated")
{
    GIVEN("an article with min quality")
    {
        int const sellIn = 0;
        std::string const name = "article";
        Article a(name, sellIn, Quality::min());
        WHEN("it is updated")
        {
            a.update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(a == Article(name, sellIn - 1, Quality::min()));
            }
        }
    }
}

SCENARIO("aged brie is updated")
{
    GIVEN("an aged brie")
    {
        int const quality = 28;
        AgedBrie a(quality);
        WHEN("it is updated")
        {
            a.update();
            THEN("quality increases by 1")
            {
                CHECK(a == AgedBrie(quality + 1));
            }
        }
    }
}

SCENARIO("aged brie with max quality is updated")
{
    GIVEN("an aged brie with max quality")
    {
        AgedBrie a(Quality::max());
        WHEN("it is updated")
        {
            a.update();
            THEN("quality does not change")
            {
                CHECK(a == AgedBrie(Quality::max()));
            }
        }
    }
}

SCENARIO("backstage pass with sellin over 10 is updated")
{
    GIVEN("a backstage pass with sellin over 10")
    {
        int const quality = 41;
        int const sellIn = 11;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increases by 1 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, quality + 1));
            }
        }
    }
}

SCENARIO("backstage pass with sellin over 10 and max quality is updated")
{
    GIVEN("a backstage pass with sellin over 10 and max quality")
    {
        int const sellIn = 11;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, Quality::max());
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increases does not change and sellin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 10 is updated")
{
    GIVEN("a backstage with sellin of 10")
    {
        int const quality = 41;
        int const sellIn = 10;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increaes by 2 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, quality + 2));
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 10 and quality 1 under max is updated")
{
    GIVEN("a backstage pass with sellin of 10 and quality 1 under max")
    {
        int const quality = Quality::max() - 1;
        int const sellIn = 10;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
            }
        }
    }
}
SCENARIO("backstage pass with sellin of 5 is updated")
{
    GIVEN("a backstage with sellin of 5")
    {
        int const quality = 41;
        int const sellIn = 5;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality increaes by 3 and sellin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, quality + 3));
            }
        }
    }
}

SCENARIO("backstage pass with sellin of 5 and quality 1 under max is updated")
{
    GIVEN("a backstage pass with sellin of 5 and quality 1 under max")
    {
        int const quality = Quality::max() - 1;
        int const sellIn = 5;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, Quality::max()));
            }
        }
    }
}

SCENARIO("backstage pass for a passed concert is updated")
{
    GIVEN("a backstage pass with sellin of 0")
    {
        int const quality = 41;
        int const sellIn = 0;
        std::string const concert = "x.y.u.";
        BackstagePass b(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b.update();
            THEN("quality value is is set to min and sellin is decreased by 1")
            {
                CHECK(b == BackstagePass(concert, sellIn - 1, Quality::min()));
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
        int const quality = 7;
        int const sellIn = 16;
        std::string const name = "conjured article";
        Conjured c(name, sellIn, quality);
        WHEN("it is updated")
        {
            c.update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(c == Conjured(name, sellIn - 1, quality - 2));
            }
        }
    }
}

SCENARIO("conjured article with sellin of 0 is updated")
{
    GIVEN("a conjured aritcle with a sellin value of 0")
    {
        int const quality = 7;
        int const sellIn = 0;
        std::string const name = "conjured article";
        Conjured c(name, sellIn, quality);
        WHEN("it is updated")
        {
            c.update();
            THEN("quality is decremented by 4 and sellin is decremented by 1")
            {
                CHECK(c == Conjured(name, sellIn - 1, quality - 4));
            }
        }
    }
}

SCENARIO("conjured article with min quality is updated")
{
    GIVEN("a conjured article with min quality")
    {
        int const sellIn = 0;
        std::string const name = "conjured article";
        Conjured c(name, sellIn, Quality::min());
        WHEN("it is updated")
        {
            c.update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(c == Conjured(name, sellIn - 1, Quality::min()));
            }
        }
    }
}

int main(int argc, const char** argv)
{

    auto a = Article("+5 Dexterity Vest", 10, 20);
    auto b = AgedBrie(0);
    auto c = Article("Elixir of the Mongoose", 5, 7);
    auto d = Sulfuras();
    auto e = Sulfuras();
    auto f = BackstagePass("TAFKAL80ETC concert", 15, 20);
    auto g = BackstagePass("TAFKAL80ETC concert", 10, 49);
    auto h = BackstagePass("TAFKAL80ETC concert", 5, 49);
    auto i = Conjured("Sword of Gold", 5, 21);

    GildedRose store;

    std::cout << "GildedRose\n";

    for (int day = 0; day <= 30; day++)
    {
        std::cout << "-------- day " << day << " --------\n";
        std::cout << "name, sellIn, quality\n";

        store.update();

        std::cout << store << "\n\n";
    }

    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit())
        return res;

    return res;
}
