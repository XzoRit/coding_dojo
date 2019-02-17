#include <functional>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

namespace xzr::pencil
{
    inline namespace v1
    {
        struct paper
        {
            void write(const std::string& txt)
                {
                    txt_ += txt;
                }
            const std::string& text() const
                {
                    return txt_;
                }
            std::string txt_{};
        };
        struct durability
        {
            durability() = default;
            explicit durability(int d)
                : value_{d}
                {}
            explicit operator bool()
                {
                    return value_ > 0;
                }
            void degrade(unsigned char c)
                {
                    if(value_ && !std::isspace(c))
                    {
                        if(std::isupper(c)) value_ -= 2;
                        else value_ -= 1;
                    }
                }
            int value_{0};
        };
        struct pen
        {
            pen(paper* p, durability d)
                : paper_{p}
                , durability_{d}
                , initial_durability_{d}
                {}
            void write(const std::string& txt)
                {
                    std::string s{};
                    for(auto c : txt)
                    {
                        if(durability_) s += c;
                        else s += ' ';
                        durability_.degrade(c);
                    }
                    if(paper_) paper_->write(s);
                }
            void sharpen()
                {
                    durability_ = initial_durability_;
                }
            void exchange_paper(paper* p)
                {
                    paper_ = p;
                }
            paper* paper_;
            durability durability_;
            durability initial_durability_;
        };
    }
}
namespace
{
    using xzr::pencil::paper;
    using xzr::pencil::pen;
    using xzr::pencil::durability;

    TEST_CASE("writing to causes a pencil point to go dull")
    {
        paper sheet{};
        pen pencil{&sheet, durability{8}};

        pencil.write("abc");
        CHECK(sheet.text() == "abc");
        SUBCASE("append")
        {
            pencil.write("def");
            CHECK(sheet.text() == "abcdef");
            SUBCASE("dull")
            {
                SUBCASE("lower case")
                {
                    pencil.write("ghi");
                    CHECK(sheet.text() == "abcdefgh ");
                    SUBCASE("sharpen")
                    {
                        paper new_sheet{};
                        pencil.exchange_paper(&new_sheet);
                        pencil.sharpen();
                        pencil.write("abcdefghi");
                        CHECK(new_sheet.text() == "abcdefgh ");
                    }
                }
                SUBCASE("upper case")
                {
                    pencil.write("GHI");
                    CHECK(sheet.text() == "abcdefG  ");
                }
                SUBCASE("whitespace")
                {
                    pencil.write("   gh");
                    CHECK(sheet.text() == "abcdef   gh");
                }
            }
        }
    }
}
