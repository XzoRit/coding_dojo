// https://godbolt.org/z/1K5MrnTY5

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
    virtual ~Item() = default;

    virtual void update() = 0;
    virtual void stream(std::ostream& o) const = 0;

    virtual std::unique_ptr<Item> clone() = 0;
    virtual bool equals(const Item& i) const = 0;
};

bool operator==(const Item& a, const Item& b);
bool operator!=(const Item& a, const Item& b);
std::ostream& operator<<(std::ostream& o, const Item& it);

bool operator==(const Item& a, const Item& b)
{
    return a.equals(b);
}

bool operator!=(const Item& a, const Item& b)
{
    return !(a == b);
}

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
    std::unique_ptr<Item> clone() override;
    bool equals(const Item& i) const override;
    void stream(std::ostream& o) const override;

  private:
    std::string name;
    int sellIn;
    int quality;
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

std::unique_ptr<Item> Article::clone()
{
    return std::make_unique<Article>(name, sellIn, quality);
}

bool Article::equals(const Item& i) const
{
    if (const Article* other = dynamic_cast<const Article*>(&i))
    {
        return (sellIn == other->sellIn) && (quality == other->quality) && (name == other->name);
    }
    return false;
}

void Article::stream(std::ostream& o) const
{
    o << name << ", " << sellIn << ", " << quality;
}

class AgedBrie : public Item
{
  public:
    AgedBrie(int quality);
    void update() override;
    std::unique_ptr<Item> clone() override;
    bool equals(const Item& i) const override;
    void stream(std::ostream& o) const override;

  private:
    int quality;
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

std::unique_ptr<Item> AgedBrie::clone()
{
    return std::make_unique<AgedBrie>(quality);
}

bool AgedBrie::equals(const Item& i) const
{
    if (const AgedBrie* other = dynamic_cast<const AgedBrie*>(&i))
    {
        return quality == other->quality;
    }
    return false;
}

void AgedBrie::stream(std::ostream& o) const
{
    o << "Aged Brie, " << quality;
}

class BackstagePass : public Item
{
  public:
    BackstagePass(std::string concert, int sellIn, int quality);
    void update() override;
    std::unique_ptr<Item> clone() override;
    bool equals(const Item& i) const override;
    void stream(std::ostream& o) const override;

  private:
    std::string concert;
    int sellIn;
    int quality;
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

std::unique_ptr<Item> BackstagePass::clone()
{
    return std::make_unique<BackstagePass>(concert, sellIn, quality);
}

bool BackstagePass::equals(const Item& i) const
{
    if (const BackstagePass* other = dynamic_cast<const BackstagePass*>(&i))
    {
        return (quality == other->quality) && (sellIn == other->sellIn) && (concert == other->concert);
    }
    return false;
}

void BackstagePass::stream(std::ostream& o) const
{
    o << "Backstage pass for " << concert << ", " << sellIn << ", " << quality;
}

class Sulfuras : public Item
{
  public:
    void update() override;
    std::unique_ptr<Item> clone() override;
    bool equals(const Item& i) const override;
    void stream(std::ostream& o) const override;
};

void Sulfuras::update()
{
}

std::unique_ptr<Item> Sulfuras::clone()
{
    return std::make_unique<Sulfuras>();
}

bool Sulfuras::equals(const Item& i) const
{
    return dynamic_cast<const Sulfuras*>(&i);
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
    std::unique_ptr<Item> clone() override;
    bool equals(const Item& i) const override;
    void stream(std::ostream& o) const override;

  private:
    std::string name;
    int sellIn;
    int quality;
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

std::unique_ptr<Item> Conjured::clone()
{
    return std::make_unique<Conjured>(name, sellIn, quality);
}

bool Conjured::equals(const Item& i) const
{
    if (const Conjured* other = dynamic_cast<const Conjured*>(&i))
    {
        return (sellIn == other->sellIn) && (quality == other->quality) && (name == other->name);
    }
    return false;
}

void Conjured::stream(std::ostream& o) const
{
    o << "Conjured " << name << ", " << sellIn << ", " << quality;
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
    for (auto&& item : articles)
    {
        item->update();
    }
}

std::ostream& operator<<(std::ostream& o, const GildedRose& g)
{
    o << "name, sellIn, quality\n";
    for (auto&& item : g.articles)
    {
        o << *item << '\n';
    }

    return o;
}

#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_COLORS_NONE
// #define DOCTEST_CONFIG_DISABLE
#include <doctest.h>

int main(int argc, const char** argv)
{
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

    doctest::Context context{};
    context.applyCommandLine(argc, argv);
    const int res{context.run()};

    if (context.shouldExit() || res != 0)
        return res;

    return 0;
}

void testItem(Item* i)
{
    {
        const auto old{i->clone()};
        i->update();
        CHECK(*old != *i);
    }
    {
        std::ostringstream os{};
        os << (*i);
        CHECK(!os.str().empty());
    }
}

TEST_CASE("article behaves like an item")
{
    std::unique_ptr<Item> a = std::make_unique<Article>("article", 16, 7);
    testItem(a.get());
}

SCENARIO("article with positive sellin is updated")
{
    GIVEN("an article with positive sellin")
    {
        int const quality = 7;
        int const sellIn = 16;
        std::string const name = "article";
        std::unique_ptr<Item> a = std::make_unique<Article>(name, sellIn, quality);
        WHEN("it is updated")
        {
            a->update();
            THEN("quality and sellin are decremented by 1")
            {
                CHECK(*a == Article(name, sellIn - 1, quality - 1));
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
        std::unique_ptr<Item> a = std::make_unique<Article>(name, sellIn, quality);
        WHEN("it is updated")
        {
            a->update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(*a == Article(name, sellIn - 1, quality - 2));
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
        std::unique_ptr<Item> a = std::make_unique<Article>(name, sellIn, Quality::min());
        WHEN("it is updated")
        {
            a->update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(*a == Article(name, sellIn - 1, Quality::min()));
            }
        }
    }
}

TEST_CASE("aged brie behaves like an item")
{
    std::unique_ptr<Item> a = std::make_unique<AgedBrie>(28);
    testItem(a.get());
}

SCENARIO("aged brie is updated")
{
    GIVEN("an aged brie")
    {
        int const quality = 28;
        std::unique_ptr<Item> a = std::make_unique<AgedBrie>(quality);
        WHEN("it is updated")
        {
            a->update();
            THEN("quality increases by 1")
            {
                CHECK(*a == AgedBrie(quality + 1));
            }
        }
    }
}

SCENARIO("aged brie with max quality is updated")
{
    GIVEN("an aged brie with max quality")
    {
        std::unique_ptr<Item> a = std::make_unique<AgedBrie>(Quality::max());
        WHEN("it is updated")
        {
            a->update();
            THEN("quality does not change")
            {
                CHECK(*a == AgedBrie(Quality::max()));
            }
        }
    }
}

TEST_CASE("backstage pass behaves like an item")
{
    const auto b{std::make_unique<BackstagePass>("abc", 11, 41)};
    testItem(b.get());
}

SCENARIO("backstage pass with sellin over 10 is updated")
{
    GIVEN("a backstage pass with sellin over 10")
    {
        int const quality = 41;
        int const sellIn = 11;
        std::string const concert = "x.y.u.";
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality increases by 1 and sellin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, quality + 1));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, Quality::max());
        WHEN("it is updated")
        {
            b->update();
            THEN("quality increases does not change and sellin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, Quality::max()));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality increaes by 2 and sellin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, quality + 2));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, Quality::max()));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality increaes by 3 and sellin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, quality + 3));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality is set to max and selllin decreases by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, Quality::max()));
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
        std::unique_ptr<Item> b = std::make_unique<BackstagePass>(concert, sellIn, quality);
        WHEN("it is updated")
        {
            b->update();
            THEN("quality value is is set to min and sellin is decreased by 1")
            {
                CHECK(*b == BackstagePass(concert, sellIn - 1, Quality::min()));
            }
        }
    }
}

TEST_CASE("sulfuras behaves like an item")
{
    const auto s{std::make_unique<Sulfuras>()};
    testItem(s.get());
}

SCENARIO("sulfuras is updated")
{
    GIVEN("sulfuras")
    {
        std::unique_ptr<Item> s = std::make_unique<Sulfuras>();
        WHEN("it is updated")
        {
            THEN("neither quality nor sellin change")
            {
            }
        }
    }
}

TEST_CASE("conjured behaves like an item")
{
    const auto c{std::make_unique<Conjured>("conjured", 16, 7)};
    testItem(c.get());
}

SCENARIO("conjured article with positive sellin is updated")
{
    GIVEN("a conjured article with positive sellin")
    {
        int const quality = 7;
        int const sellIn = 16;
        std::string const name = "conjured article";
        std::unique_ptr<Item> c = std::make_unique<Conjured>(name, sellIn, quality);
        WHEN("it is updated")
        {
            c->update();
            THEN("quality is decremented by 2 and sellin is decremented by 1")
            {
                CHECK(*c == Conjured(name, sellIn - 1, quality - 2));
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
        std::unique_ptr<Item> c = std::make_unique<Conjured>(name, sellIn, quality);
        WHEN("it is updated")
        {
            c->update();
            THEN("quality is decremented by 4 and sellin is decremented by 1")
            {
                CHECK(*c == Conjured(name, sellIn - 1, quality - 4));
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
        std::unique_ptr<Item> c = std::make_unique<Conjured>(name, sellIn, Quality::min());
        WHEN("it is updated")
        {
            c->update();
            THEN("quality does not change and sellin is decremented by 1")
            {
                CHECK(*c == Conjured(name, sellIn - 1, Quality::min()));
            }
        }
    }
}
