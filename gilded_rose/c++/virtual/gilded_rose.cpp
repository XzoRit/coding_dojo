#include <iostream>

#ifndef _QUALITY_HPP_
#define _QUALITY_HPP_

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

    static int sulfuras()
    {
        return 80;
    }
};

#endif

class Article
{
};

#ifndef _ARTICLE_HPP_
#define _ARTICLE_HPP_

#include <ostream>
#include <string>

class Article
{
  public:
    Article(std::string name, int sellIn, int quality);
    void update();
    bool operator==(Article const&) const;
    bool operator!=(Article const&) const;

  private:
    friend std::ostream& operator<<(std::ostream& o, Article const& a);
    std::string const name;
    int sellIn;
    int quality;
};

#endif

std::ostream& operator<<(std::ostream& o, Article const& a)
{
    o << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

Article::Article(std::string name, int sellIn, int quality)
    : name(name)
    , sellIn(sellIn)
    , quality(quality)
{
}

bool Article::operator==(Article const& other) const
{
    return (sellIn == other.sellIn) && (quality == other.quality) && (name == other.name);
}

bool Article::operator!=(Article const& other) const
{
    return !(*this == other);
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

#ifndef _AGED_BRIE_HPP_
#define _AGED_BRIE_HPP_

#include <ostream>

class AgedBrie
{
  public:
    AgedBrie(int quality);
    bool operator==(AgedBrie const& other) const;
    bool operator!=(AgedBrie const& other) const;
    void update();

  private:
    friend std::ostream& operator<<(std::ostream& o, AgedBrie const& a);
    int quality;
};

#endif

std::ostream& operator<<(std::ostream& o, AgedBrie const& a)
{
    o << "Aged Brie, " << a.quality;
    return o;
}

AgedBrie::AgedBrie(int quality)
    : quality(quality)
{
}

bool AgedBrie::operator==(AgedBrie const& other) const
{
    return quality == other.quality;
}

bool AgedBrie::operator!=(AgedBrie const& other) const
{
    return !(*this == other);
}

void AgedBrie::update()
{
    if (quality < Quality::max())
    {
        ++quality;
    }
}

#ifndef _BACKSTAGE_PASS_HPP_
#define _BACKSTAGE_PASS_HPP_

#include <ostream>
#include <string>

class BackstagePass
{
  public:
    BackstagePass(std::string concert, int sellIn, int quality);
    bool operator==(BackstagePass const& other) const;
    bool operator!=(BackstagePass const& other) const;
    void update();

  private:
    friend std::ostream& operator<<(std::ostream& o, BackstagePass const& b);
    std::string concert;
    int sellIn;
    int quality;
};

#endif

std::ostream& operator<<(std::ostream& o, BackstagePass const& b)
{
    o << "Backstage pass for " << b.concert << ", " << b.sellIn << ", " << b.quality;
    return o;
}

BackstagePass::BackstagePass(std::string concert, int sellIn, int quality)
    : concert(concert)
    , sellIn(sellIn)
    , quality(quality)
{
}

bool BackstagePass::operator==(BackstagePass const& other) const
{
    return (quality == other.quality) && (sellIn == other.sellIn) && (concert == other.concert);
}

bool BackstagePass::operator!=(BackstagePass const& other) const
{
    return !(*this == other);
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

#ifndef _SULFURAS_HPP_
#define _SULFURAS_HPP_

#include <ostream>

class Sulfuras
{
  public:
    void update();

  private:
    friend std::ostream& operator<<(std::ostream& o, Sulfuras const& s);
};

#endif

std::ostream& operator<<(std::ostream& o, Sulfuras const& s)
{
    o << "Sulfuras";
    return o;
}

void Sulfuras::update()
{
}

#ifndef _CONJURED_HPP_
#define _CONJURED_HPP_

#include <ostream>
#include <string>

class Conjured
{
  public:
    Conjured(std::string name, int sellIn, int quality);
    void update();
    bool operator==(Conjured const&) const;
    bool operator!=(Conjured const&) const;

  private:
    friend std::ostream& operator<<(std::ostream& o, Conjured const& a);
    std::string const name;
    int sellIn;
    int quality;
};

#endif

std::ostream& operator<<(std::ostream& o, Conjured const& a)
{
    o << "Conjured " << a.name << ", " << a.sellIn << ", " << a.quality;
    return o;
}

Conjured::Conjured(std::string name, int sellIn, int quality)
    : name(name)
    , sellIn(sellIn)
    , quality(quality)
{
}

bool Conjured::operator==(Conjured const& other) const
{
    return (sellIn == other.sellIn) && (quality == other.quality) && (name == other.name);
}

bool Conjured::operator!=(Conjured const& other) const
{
    return !(*this == other);
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

#ifndef _ARTICLES_HPP_
#define _ARTICLES_HPP_

#include <variant>
#include <vector>

typedef std::vector<std::variant<Article, AgedBrie, BackstagePass, Sulfuras, Conjured>> Articles;

#endif

#ifndef _GILDED_ROSE_HPP_
#define _GILDED_ROSE_HPP_

#include <algorithm>

template <class ArticlesType>
class GildedRose
{
  public:
    explicit GildedRose(ArticlesType articles);
    void updateQuality();

  private:
    template <class Articles>
    friend std::ostream& operator<<(std::ostream& o, GildedRose<Articles> const& g);
    ArticlesType articles;
};

class OStreamer
{
  public:
    explicit OStreamer(std::ostream& o)
        : o(o)
    {
    }

    template <class T>
    void operator()(const T& t) const
    {
        o << t << '\n';
    }

  private:
    std::ostream& o;
};

template <class Articles>
std::ostream& operator<<(std::ostream& o, GildedRose<Articles> const& g)
{
    o << "name, sellIn, quality\n";
    std::for_each(g.articles.begin(), g.articles.end(), [&o](const auto& as) { std::visit(OStreamer{o}, as); });
    return o;
}

class Updater
{
  public:
    template <class T>
    void operator()(T& t)
    {
        t.update();
    }
};

template <class ArticlesType>
GildedRose<ArticlesType>::GildedRose(ArticlesType articles)
    : articles(articles)
{
}

template <class ArticlesType>
void GildedRose<ArticlesType>::updateQuality()
{
    std::for_each(articles.begin(), articles.end(), [](auto& as) { std::visit(Updater{}, as); });
}

#endif

#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
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
            s.update();
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

using namespace std;

int main(int argc, const char** argv)
{
    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit())
        return res;

    Articles articles;
    articles.push_back(Article("+5 Dexterity Vest", 10, 20));
    articles.push_back(AgedBrie(0));
    articles.push_back(Article("Elixir of the Mongoose", 5, 7));
    articles.push_back(Sulfuras());
    articles.push_back(Sulfuras());
    articles.push_back(BackstagePass("TAFKAL80ETC concert", 15, 20));
    articles.push_back(BackstagePass("TAFKAL80ETC concert", 10, 49));
    articles.push_back(BackstagePass("TAFKAL80ETC concert", 5, 49));
    articles.push_back(Conjured("Sword of Gold", 5, 21));
    GildedRose<Articles> app(articles);

    cout << "OMGHAI!" << endl;

    for (int day = 0; day <= 30; day++)
    {
        cout << "-------- day " << day << " --------\n";
        cout << app << "\n\n";
        app.updateQuality();
    }

    return res;
}
