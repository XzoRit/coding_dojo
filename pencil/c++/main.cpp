#include <boost/algorithm/string/find.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

namespace xzr::pencil
{
    inline namespace v1
    {
        struct paper
        {
            using iterator = std::string::iterator;
            iterator begin()
                {
                    return txt_.begin();
                }
            iterator end()
                {
                    return txt_.end();
                }
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
            explicit operator bool() const
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
        struct length
        {
            explicit length(int l)
                : value_{l}
                {}
            explicit operator bool() const
                {
                    return value_ > 0;
                }
            void shorten()
                {
                    if(value_) --value_;
                }
            int value_;
        };
        struct pen
        {
            pen(durability d, length l, durability e)
                : initial_durability_{d}
                , durability_{d}
                , length_{l}
                , eraser_durability_{e}
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
                    if(length_) durability_ = initial_durability_;
                    length_.shorten();
                }
            template<class Range>
            void erase(Range range)
                {
                    for(auto& a : range)
                    {
                        const auto b{a};
                        if(eraser_durability_) a = ' ';
                        eraser_durability_.degrade(b);
                    }
                }
            const durability initial_durability_;
            durability durability_;
            length length_;
            durability eraser_durability_;
        };
        void write(const std::string& txt, pen& pen, paper& sheet)
        {
            sheet.write(pen.write(txt));
        }
        void erase(const std::string& txt, pen& pen, paper& sheet)
        {
            const auto& range{boost::make_iterator_range(sheet.begin(), sheet.end())};
            pen.erase(boost::find_last(range, txt));
        }
    }
}
namespace
{
    using xzr::pencil::durability;
    using xzr::pencil::length;
    using xzr::pencil::paper;
    using xzr::pencil::pen;

    TEST_CASE("writing to causes a pencil point to go dull")
    {
        paper sheet{};
        pen pencil{durability{8}, length{1}, durability{4}};

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
                        SUBCASE("length exceeded")
                        {
                            pencil.sharpen();
                            write("abc", pencil, new_sheet);
                            CHECK(new_sheet.text() == "abcdefgh    ");
                        }
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
        SUBCASE("eraser")
        {
            write("abc", pencil, sheet);
            erase("ab", pencil, sheet);
            CHECK(sheet.text() == "abc  c");
            SUBCASE("durability")
            {
                SUBCASE("whitespace")
                {
                    erase("  ", pencil, sheet);
                    CHECK(sheet.text() == "abc  c");
                }
                SUBCASE("lower case")
                {
                    erase("ab", pencil, sheet);
                    CHECK(sheet.text() == "  c  c");
                    SUBCASE("dull")
                    {
                        erase("c", pencil, sheet);
                        CHECK(sheet.text() == "  c  c");
                    }
                }
            }
        }
    }
}
