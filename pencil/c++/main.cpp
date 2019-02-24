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
        struct scratch_pad
        {
            scratch_pad(paper pap, pen p)
                : paper_{std::move(pap)}
                , pen_{std::move(p)}
                {}
            std::string text() const
                {
                    return paper_.text();
                }
            void write(const std::string& txt)
                {
                    v1::write(txt, pen_, paper_);
                }
            auto erase(const std::string& txt)
                {
                    return v1::erase(txt, pen_, paper_);
                }
            template<class Range>
            void insert(const std::string& txt, const Range& insert_range)
                {
                    v1::insert(txt, insert_range, pen_);
                }
            void sharpen_pen()
                {
                    pen_.sharpen();
                }
            paper paper_;
            pen pen_;
        };
    }
}
namespace
{
    using xzr::pencil::durability;
    using xzr::pencil::eraser;
    using xzr::pencil::length;
    using xzr::pencil::paper;
    using xzr::pencil::pen;
    using xzr::pencil::scratch_pad;

    TEST_CASE("writing to causes a pencil point to go dull")
    {
        scratch_pad pad{paper{}, pen{durability{8}, length{1}, eraser{durability{4}}}};
        pad.write("abc");
        CHECK(pad.text() == "abc");
        SUBCASE("append")
        {
            pad.write("def");
            CHECK(pad.text() == "abcdef");
            SUBCASE("dull")
            {
                SUBCASE("lower case")
                {
                    pad.write("ghi");
                    CHECK(pad.text() == "abcdefgh ");
                    SUBCASE("sharpen")
                    {
                        pad.sharpen_pen();
                        pad.write("abcdefghi");
                        CHECK(pad.text() == "abcdefgh abcdefgh ");
                        SUBCASE("length exceeded")
                        {
                            pad.sharpen_pen();
                            pad.write("abc");
                            CHECK(pad.text() == "abcdefgh abcdefgh    ");
                        }
                    }
                }
                SUBCASE("upper case")
                {
                    pad.write("GHI");
                    CHECK(pad.text() == "abcdefG  ");
                }
                SUBCASE("whitespace")
                {
                    pad.write("   gh");
                    CHECK(pad.text() == "abcdef   gh");
                }
            }
        }
    }

    TEST_CASE("eraser")
    {
        scratch_pad pad{paper{}, pen{durability{100}, length{1}, eraser{durability{4}}}};
        pad.write("abcabc");
        const auto& erased_range{pad.erase("ab")};
        CHECK(pad.text() == "abc  c");
        SUBCASE("durability")
        {
            pad.erase("  ");
            CHECK(pad.text() == "abc  c");
            SUBCASE("lower case")
            {
                pad.erase("ab");
                CHECK(pad.text() == "  c  c");
                SUBCASE("dull")
                {
                    pad.erase("c");
                    CHECK(pad.text() == "  c  c");
                }
            }
        }
        SUBCASE("insert")
        {
            pad.insert("de", erased_range);
            CHECK(pad.text() == "abcdec");
        }
        SUBCASE("insert too much")
        {
            pad.insert("def", erased_range);
            CHECK(pad.text() == "abcde@");
        }
    }
}
