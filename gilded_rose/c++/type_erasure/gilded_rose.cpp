// https://godbolt.org/z/aqz3Tvs4e

#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#define V1

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

NS_V1
{
    class Item
    {
      public:
        template <class It>
        Item(It it)
            : item{std::make_unique<ItemModel<It>>(std::move(it))}
        {
        }

        Item(const Item& rhs)
            : item(rhs.item->clone())
        {
        }

        Item(Item&& rhs) = default;

        Item& operator=(Item rhs) noexcept
        {
            this->swap(rhs);
            return *this;
        }

        void swap(Item& rhs) noexcept
        {
            item.swap(rhs.item);
        }

        void update()
        {
            item->update();
        }

        void stream(std::ostream& o) const
        {
            item->stream(o);
        }

        friend bool operator==(const Item& a, const Item& b);
        friend bool operator!=(const Item& a, const Item& b);

      private:
        struct ItemBase
        {
            virtual std::unique_ptr<ItemBase> clone() const = 0;
            virtual void update() = 0;
            virtual bool equals(const ItemBase* a) const = 0;
            virtual void stream(std::ostream&) = 0;
            virtual ~ItemBase() = default;
        };

        template <class It>
        struct ItemModel : public ItemBase
        {
            explicit ItemModel(It it)
                : item(std::move(it))
            {
            }

            std::unique_ptr<ItemBase> clone() const override
            {
                return std::make_unique<ItemModel>(item);
            }

            void update() override
            {
                item.update();
            }

            bool equals(const ItemBase* a) const override
            {
                const ItemModel<It>* aItem = dynamic_cast<const ItemModel<It>*>(a);

                if (aItem)
                    return aItem->item == item;
                else
                    return false;
            }

            void stream(std::ostream& o) override
            {
                o << item;
            }

            It item;
        };

        std::unique_ptr<ItemBase> item;
    };

    bool operator==(const Item& a, const Item& b)
    {
        return a.item->equals(b.item.get());
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
}

NS_V2
{
    class Item
    {
      public:
        template <class It>
        Item(It it)
            : repr_{new It{std::move(it)}}
            , delete_{[](void* r) { delete static_cast<It*>(r); }}
            , clone_{[](void* r) -> void* { return new It{*static_cast<It*>(r)}; }}
            , update_{[](void* r) { static_cast<It*>(r)->update(); }}
            , stream_{[](void* r, std::ostream& o) { o << (*static_cast<It*>(r)); }}
            , equals_{[](void* a, void* b) { return (*static_cast<It*>(a)) == (*static_cast<It*>(b)); }}
        {
        }

        Item(const Item& other)
            : repr_{other.clone_(other.repr_)}
            , delete_{other.delete_}
            , clone_{other.clone_}
            , update_{other.update_}
            , stream_{other.stream_}
            , equals_{other.equals_}
        {
        }

        Item(Item&& rhs) noexcept
            : Item{}
        {
            this->swap(rhs);
        }

        ~Item()
        {
            if (repr_)
            {
                delete_(repr_);
                repr_ = nullptr;
                delete_ = nullptr;
                clone_ = nullptr;
                update_ = nullptr;
                stream_ = nullptr;
                equals_ = nullptr;
            }
        }

        Item& operator=(Item rhs) noexcept
        {
            this->swap(rhs);
            return *this;
        }

        void swap(Item& rhs) noexcept
        {
            using std::swap;
            swap(repr_, rhs.repr_);
            swap(delete_, rhs.delete_);
            swap(clone_, rhs.clone_);
            swap(update_, rhs.update_);
            swap(stream_, rhs.stream_);
            swap(equals_, rhs.equals_);
        }

        void update()
        {
            update_(repr_);
        }

        friend bool operator==(const Item& a, const Item& b);
        friend bool operator!=(const Item& a, const Item& b);
        friend std::ostream& operator<<(std::ostream& o, const Item& it);

      private:
        Item() = default;
        void* repr_{nullptr};
        void (*delete_)(void*){nullptr};
        void* (*clone_)(void*){nullptr};
        void (*update_)(void*){nullptr};
        void (*stream_)(void*, std::ostream&){nullptr};
        bool (*equals_)(void*, void*){nullptr};
    };

    bool operator==(const Item& a, const Item& b)
    {
        return a.equals_(a.repr_, b.repr_);
    }

    bool operator!=(const Item& a, const Item& b)
    {
        return !(a == b);
    }

    std::ostream& operator<<(std::ostream& o, const Item& it)
    {
        it.stream_(it.repr_, o);
        return o;
    }

    void swap(Item & a, Item & b) noexcept
    {
        a.swap(b);
    }
}

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
  public:
    void update();

  private:
    friend std::ostream& operator<<(std::ostream& o, const Sulfuras& s);
};

bool operator==(const Sulfuras&, const Sulfuras&);

void Sulfuras::update()
{
}

bool operator==(const Sulfuras&, const Sulfuras&)
{
    return true;
}

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
    void add(Item item);
    void update();

  private:
    using Articles = std::vector<Item>;
    Articles articles;

    friend std::ostream& operator<<(std::ostream& o, const GildedRose& g);
};

void GildedRose::add(Item item)
{
    articles.push_back(std::move(item));
}

void GildedRose::update()
{
    for (auto& item : articles)
    {
        item.update();
    }
}

std::ostream& operator<<(std::ostream& o, const GildedRose& g)
{
    o << "name, sellIn, quality\n";
    for (const auto& item : g.articles)
    {
        o << item << '\n';
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
    store.add(Article{"+5 Dexterity Vest", 10, 20});
    store.add(AgedBrie{0});
    store.add(Article{"Elixir of the Mongoose", 5, 7});
    store.add(Sulfuras{});
    store.add(Sulfuras{});
    store.add(BackstagePass{"TAFKAL80ETC concert", 15, 20});
    store.add(BackstagePass{"TAFKAL80ETC concert", 10, 49});
    store.add(BackstagePass{"TAFKAL80ETC concert", 5, 49});
    store.add(Conjured{"Sword of Gold", 5, 21});

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

void testItem(Item i)
{
    {
        const auto old{i};
        i.update();
        CHECK(old != i);
    }
    {
        std::ostringstream os{};
        os << i;
        CHECK(!os.str().empty());
    }
}

TEST_CASE("article behaves like an item")
{
    testItem(Article{"article", 16, 7});
}

SCENARIO("article with positive sellin is updated")
{
    GIVEN("an article with positive sellin")
    {
        const int quality{7};
        const int sellIn{16};
        const std::string name{"article"};
        Item a{Article{name, sellIn, quality}};
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
        Item a{Article{name, sellIn, quality}};
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
        Item a{Article{name, sellIn, Quality::min()}};
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

TEST_CASE("aged brie behaves like an item")
{
    testItem(AgedBrie{28});
}

SCENARIO("aged brie is updated")
{
    GIVEN("an aged brie")
    {
        const int quality{28};
        Item a{AgedBrie{quality}};
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
        Item a{AgedBrie{Quality::max()}};
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

TEST_CASE("backstage pass behaves like an item")
{
    testItem(BackstagePass{"abc", 11, 41});
}

SCENARIO("backstage pass with sellin over 10 is updated")
{
    GIVEN("a backstage pass with sellin over 10")
    {
        const int quality{41};
        const int sellIn{11};
        const std::string concert{"x.y.u."};
        Item b{BackstagePass{concert, sellIn, quality}};
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
        Item b{BackstagePass{concert, sellIn, Quality::max()}};
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
        Item b{BackstagePass{concert, sellIn, quality}};
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
        Item b{BackstagePass{concert, sellIn, quality}};
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
        Item b{BackstagePass{concert, sellIn, quality}};
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
        Item b{BackstagePass{concert, sellIn, quality}};
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
        Item b{BackstagePass{concert, sellIn, quality}};
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

TEST_CASE("sulfuras behaves like an item")
{
    testItem(Sulfuras{});
}

SCENARIO("sulfuras is updated")
{
    GIVEN("sulfuras")
    {
        Item s{Sulfuras{}};
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
    testItem(Conjured{"conjured", 16, 7});
}

SCENARIO("conjured article with positive sellin is updated")
{
    GIVEN("a conjured article with positive sellin")
    {
        const int quality{7};
        const int sellIn{16};
        const std::string name{"conjured article"};
        Item c{Conjured{name, sellIn, quality}};
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
        Item c{Conjured{name, sellIn, quality}};
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
        Item c{Conjured{name, sellIn, Quality::min()}};
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
