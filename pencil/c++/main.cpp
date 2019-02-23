#include <boost/algorithm/string/find.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

namespace xzr::pencil
{
    inline namespace v1
    {
        struct paper
        {
            using value_type = std::string::value_type;
            using iterator = std::string::iterator;
            iterator begin()
                {
                    return txt_.begin();
                }
            iterator end()
                {
                    return txt_.end();
                }
            template<class Char>
            void push_back(Char c)
                {
                    txt_.push_back(c);
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
        struct eraser
        {
            eraser()
                : durability_{0}
                {}
            explicit eraser(durability d)
                : durability_{d}
                {}
            void erase(char& c)
                {
                    const auto tmp{c};
                    if(durability_) c = ' ';
                    durability_.degrade(tmp);
                }
            durability durability_;
        };
        struct pen
        {
            pen(durability d, length l, eraser e)
                : initial_durability_{d}
                , durability_{d}
                , length_{l}
                , eraser_{e}
                {}
            template<class OutIter>
            void write_to(const std::string& txt, OutIter it)
                {
                    for(auto c : txt)
                    {
                        if(durability_) (*it++) = c;
                        else (*it++) = ' ';
                        durability_.degrade(c);
                    }
                }
            template<class OutRange>
            void insert_to(const std::string& txt, OutRange out_range)
                {
                    auto it{std::begin(out_range)};
                    for(auto c : txt)
                    {
                        if(durability_)
                        {
                            if((*it) == ' ') (*it++) = c;
                            else (*it++) = '@';
                        }
                        else (*it++) = ' ';
                        durability_.degrade(c);
                    }
                }
            void sharpen()
                {
                    if(length_) durability_ = initial_durability_;
                    length_.shorten();
                }
            template<class Range>
            void erase_from(Range range)
                {
                    for(auto& a : range)
                    {
                        eraser_.erase(a);
                    }
                }
            const durability initial_durability_;
            durability durability_;
            length length_;
            eraser eraser_;
        };
        void write(const std::string& txt, pen& pen, paper& sheet)
        {
            pen.write_to(txt, std::back_inserter(sheet));
        }
        auto erase(const std::string& txt, pen& pen, paper& sheet)
        {
            const auto& sheet_range{boost::make_iterator_range(sheet.begin(), sheet.end())};
            const auto& erase_range{boost::find_last(sheet_range, txt)};
            pen.erase_from(erase_range);
            return erase_range;
        }
        template<class Range>
        void insert(const std::string& txt, const Range& insert_range, pen& pen)
        {
            pen.insert_to(txt, insert_range);
        }
    }
}
namespace
{
    using xzr::pencil::durability;
    using xzr::pencil::eraser;
    using xzr::pencil::length;
    using xzr::pencil::paper;
    using xzr::pencil::pen;

    TEST_CASE("writing to causes a pencil point to go dull")
    {
        paper sheet{};
        pen pencil{durability{8}, length{1}, eraser{durability{4}}};

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
    }

    TEST_CASE("eraser")
    {
        paper sheet{};
        pen pencil{durability{100}, length{1}, eraser{durability{4}}};
        write("abcabc", pencil, sheet);
        const auto& erased_range{erase("ab", pencil, sheet)};
        CHECK(sheet.text() == "abc  c");
        SUBCASE("durability")
        {
            erase("  ", pencil, sheet);
            CHECK(sheet.text() == "abc  c");
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
        SUBCASE("insert")
        {
            insert("de", erased_range, pencil);
            CHECK(sheet.text() == "abcdec");
        }
        SUBCASE("insert too much")
        {
            insert("def", erased_range, pencil);
            CHECK(sheet.text() == "abcde@");
        }
    }
}
