#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/hana.hpp>
#include <boost/mp11/tuple.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

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
    self.update();
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
class AgedBrie : public Item<AgedBrie>
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
class BackstagePass : public Item<BackstagePass>
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
class Sulfuras : public Item<Sulfuras>
{
  public:
    void update();

  private:
    friend std::ostream& operator<<(std::ostream& o, const Sulfuras& s);
};
void Sulfuras::update()
{
}
std::ostream& operator<<(std::ostream& o, const Sulfuras& s)
{
    o << "Sulfuras";
    return o;
}
class Conjured : public Item<Conjured>
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
#define V2
#if defined(V1)
#define NS_V1 inline namespace v1
#else
#define NS_V1 namespace v1
#endif
#if defined(V2)
#define NS_V2 inline namespace v2
#else
#define NS_V2 namespace v2
#endif
NS_V1
{
    using Articles = std::
        tuple<Article, AgedBrie, Article, Sulfuras, Sulfuras, BackstagePass, BackstagePass, BackstagePass, Conjured>;
    class GildedRose
    {
      public:
        void update();

      private:
        Articles articles = std::make_tuple(Article{"+5 Dexterity Vest", 10, 20},
                                            AgedBrie{0},
                                            Article{"Elixir of the Mongoose", 5, 7},
                                            Sulfuras{},
                                            Sulfuras{},
                                            BackstagePass{"TAFKAL80ETC concert", 15, 20},
                                            BackstagePass{"TAFKAL80ETC concert", 10, 49},
                                            BackstagePass{"TAFKAL80ETC concert", 5, 49},
                                            Conjured{"Sword of Gold", 5, 21});
        friend std::ostream& operator<<(std::ostream& o, GildedRose const& g);
    };
    void GildedRose::update()
    {
        ::boost::mp11::tuple_for_each(articles, [](auto& item) { updateItem(item); });
    }
    std::ostream& operator<<(std::ostream& o, GildedRose const& g)
    {
        o << "name, sellIn, quality\n";
        ::boost::mp11::tuple_for_each(g.articles, [&](const auto& item) { o << item << '\n'; });
        return o;
    }
}
NS_V2
{
    struct Articles
    {
        Article a{"+5 Dexterity Vest", 10, 20};
        AgedBrie b{0};
        Article c{"Elixir of the Mongoose", 5, 7};
        Sulfuras d{};
        Sulfuras e{};
        BackstagePass f{"TAFKAL80ETC concert", 15, 20};
        BackstagePass g{"TAFKAL80ETC concert", 10, 49};
        BackstagePass h{"TAFKAL80ETC concert", 5, 49};
        Conjured i{"Sword of Gold", 5, 21};
    };
}
BOOST_HANA_ADAPT_STRUCT(v2::Articles, a, b, c, d, e, f, g, h, i);
BOOST_FUSION_ADAPT_STRUCT(v2::Articles, a, b, c, d, e, f, g, h, i);
NS_V2
{
    class GildedRose
    {
      public:
        void update();

      private:
        Articles articles;
        friend std::ostream& operator<<(std::ostream& o, GildedRose const& g);
    };
    void GildedRose::update()
    {
        ::boost::hana::for_each(::boost::hana::members(articles), [](auto&& item) { updateItem(item); });
        // ::boost::fusion::for_each(articles,
        //                           [](auto&& item) { updateItem(item); });
    }
    std::ostream& operator<<(std::ostream& o, GildedRose const& g)
    {
        o << "name, sellIn, quality\n";
        ::boost::hana::for_each(::boost::hana::members(g.articles), [&](const auto& item) { o << item << '\n'; });
        // ::boost::fusion::for_each(g.articles,
        //                           [&](const auto& item) { o << item <<
        '\n';
        //                           });
        return o;
    }
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
