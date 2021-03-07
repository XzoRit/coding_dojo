#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

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

class Item
{
  public:
    virtual void update() = 0;
    virtual void stream(std::ostream& o) const = 0;
    virtual ~Item() = default;
};

std::ostream& operator<<(std::ostream& o, const Item& it);

std::ostream& operator<<(std::ostream& o, const Item& it)
{
    it.stream(o);
    return o;
}

class Article : public Item
{
  public:
    Article(std::string name, int sellIn, int quality);
    void update() override;
    void stream(std::ostream& o) const override;

  private:
    std::string name;
    int sellIn;
    int quality;

    friend bool operator==(const Article& a, const Article& b);
    friend bool operator!=(const Article& a, const Article& b);
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

void Article::stream(std::ostream& o) const
{
    o << name << ", " << sellIn << ", " << quality;
}

bool operator==(const Article& a, const Article& b)
{
    return (a.sellIn == b.sellIn) && (a.quality == b.quality) && (a.name == b.name);
}

bool operator!=(const Article& a, const Article& b)
{
    return !(a == b);
}

class AgedBrie : public Item
{
  public:
    AgedBrie(int quality);
    void update() override;
    void stream(std::ostream& o) const override;

  private:
    int quality;

    friend bool operator==(const AgedBrie& a, const AgedBrie& b);
    friend bool operator!=(const AgedBrie& a, const AgedBrie& b);
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

void AgedBrie::stream(std::ostream& o) const
{
    o << "Aged Brie, " << quality;
}

bool operator==(const AgedBrie& a, const AgedBrie& b)
{
    return a.quality == b.quality;
}

bool operator!=(const AgedBrie& a, const AgedBrie& b)
{
    return !(a == b);
}

class BackstagePass : public Item
{
  public:
    BackstagePass(std::string concert, int sellIn, int quality);
    void update() override;
    void stream(std::ostream& o) const override;

  private:
    std::string concert;
    int sellIn;
    int quality;

    friend bool operator==(const BackstagePass& a, const BackstagePass& b);
    friend bool operator!=(const BackstagePass& a, const BackstagePass& b);
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

void BackstagePass::stream(std::ostream& o) const
{
    o << "Backstage pass for " << concert << ", " << sellIn << ", " << quality;
}

bool operator==(const BackstagePass& a, const BackstagePass& b)
{
    return (a.quality == b.quality) && (a.sellIn == b.sellIn) && (a.concert == b.concert);
}

bool operator!=(const BackstagePass& a, const BackstagePass& b)
{
    return !(a == b);
}

class Sulfuras : public Item
{
  public:
    void update() override;
    void stream(std::ostream& o) const override;
};

void Sulfuras::update()
{
}

void Sulfuras::stream(std::ostream& o) const
{
    o << "Sulfuras";
}

class Conjured : public Item
{
  public:
    Conjured(std::string name, int sellIn, int quality);
    void update() override;
    void stream(std::ostream& o) const override;

  private:
    std::string name;
    int sellIn;
    int quality;

    friend bool operator==(const Conjured& a, const Conjured& b);
    friend bool operator!=(const Conjured& a, const Conjured& b);
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

void Conjured::stream(std::ostream& o) const
{
    o << "Conjured " << name << ", " << sellIn << ", " << quality;
}

bool operator==(const Conjured& a, const Conjured& b)
{
    return (a.sellIn == b.sellIn) && (a.quality == b.quality) && (a.name == b.name);
}

bool operator!=(const Conjured& a, const Conjured& b)
{
    return !(a == b);
}

class GildedRose
{
  public:
    using ItemRef = std::unique_ptr<Item>;
    void add(ItemRef item);
    void update();

  private:
    using Articles = std::vector<ItemRef>;
    Articles articles;

    friend std::ostream& operator<<(std::ostream& o, const GildedRose& g);
};

void GildedRose::add(ItemRef item)
{
    articles.push_back(std::move(item));
}

void GildedRose::update()
{
    std::for_each(begin(articles), end(articles), [](const auto& item) { item->update(); });
}

std::ostream& operator<<(std::ostream& o, const GildedRose& g)
{
    o << "name, sellIn, quality\n";
    std::for_each(begin(g.articles), end(g.articles), [&o](const auto& item) { o << *item << '\n'; });

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
    doctest::Context context{};
    context.applyCommandLine(argc, argv);
    const int res{context.run()};
    if (context.shouldExit() || res != 0)
        return res;

    GildedRose store{};
    store.add(std::make_unique<Article>("+5 Dexterity Vest", 10, 20));
    store.add(std::make_unique<AgedBrie>(0));
    store.add(std::make_unique<Article>("Elixir of the Mongoose", 5, 7));
    store.add(std::make_unique<Sulfuras>());
    store.add(std::make_unique<Sulfuras>());
    store.add(std::make_unique<BackstagePass>("TAFKAL80ETC concert", 15, 20));
    store.add(std::make_unique<BackstagePass>("TAFKAL80ETC concert", 10, 49));
    store.add(std::make_unique<BackstagePass>("TAFKAL80ETC concert", 5, 49));
    store.add(std::make_unique<Conjured>("Sword of Gold", 5, 21));

    std::cout << "GildedRose\n";
    for (int day{0}; day <= 30; ++day)
    {
        std::cout << "-------- day " << day << " --------\n";
        store.update();
        std::cout << store << "\n\n";
    }

    return 0;
}
