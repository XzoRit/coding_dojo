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
            pen(durability d)
                : initial_durability_{d}
                , durability_{d}
                {}
            std::string write(const std::string& txt)
                {
                    std::string s{};
                    for(auto c : txt)
                    {
                        if(durability_) s += c;
                        else s += ' ';
                        durability_.degrade(c);
                    }
                    return s;
                }
            void sharpen()
                {
                    durability_ = initial_durability_;
                }
            const durability initial_durability_;
            durability durability_;
        };
        void write(const std::string& txt, pen& pen, paper& sheet)
        {
            sheet.write(pen.write(txt));
        }
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
        pen pencil{durability{8}};

        write("abc", pencil, sheet);
        CHECK(sheet.text() == "abc");
        SUBCASE("append")
        {
            write("def", pencil, sheet);
            CHECK(sheet.text() == "abcdef");
            SUBCASE("dull")
            {
                SUBCASE("lower case")
                {
                    write("ghi", pencil, sheet);
                    CHECK(sheet.text() == "abcdefgh ");
                    SUBCASE("sharpen")
                    {
                        pencil.sharpen();
                        paper new_sheet{};
                        write("abcdefghi", pencil, new_sheet);
                        CHECK(new_sheet.text() == "abcdefgh ");
                    }
                }
                SUBCASE("upper case")
                {
                    write("GHI", pencil, sheet);
                    CHECK(sheet.text() == "abcdefG  ");
                }
                SUBCASE("whitespace")
                {
                    write("   gh", pencil, sheet);
                    CHECK(sheet.text() == "abcdef   gh");
                }
            }
        }
    }
}
