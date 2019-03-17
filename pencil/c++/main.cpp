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
            using const_iterator = std::string::const_iterator;
            const_iterator begin() const
                {
                    return txt_.begin();
                }
            const_iterator end() const
                {
                    return txt_.end();
                }
            iterator begin()
                {
                    return txt_.begin();
                }
            iterator end()
                {
                    return txt_.end();
                }
            void push_back(value_type c)
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
            durability degrade(unsigned char c)
                {
                    const auto old{*this};
                    if(value_ && !std::isspace(c))
                    {
                        if(std::isupper(c)) value_ -= 2;
                        else value_ -= 1;
                    }
                    return old;
                }
            int value_{0};
        };
        int shorten(int current)
        {
            if(current) --current;
            return current;;
        }
        struct length
        {
            explicit length(int l)
                : value_{l}
                {}
            explicit operator bool() const
                {
                    return value_ > 0;
                }
            length operator--() const
                {
                    return length{shorten(value_)};
                }
            length operator--(int)
                {
                    const auto l{*this};
                    value_ = shorten(value_);
                    return l;
                }
            int value_{0};
        };
        struct eraser
        {
            eraser() = default;
            explicit eraser(durability d)
                : durability_{d}
                {}
            template<class Range>
            Range erase(Range r)
                {
                    std::replace_if(
                        std::begin(r), std::end(r),
                        [this](auto c){ return durability_.degrade(c); }
                        , ' ');
                    return r;
                }
            durability durability_{0};
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
                        if(durability_.degrade(c)) (*it++) = c;
                        else (*it++) = std::isspace(c) ? c : ' ';
                    }
                }
            template<class OutRange>
            void insert_to(const std::string& txt, OutRange out_range)
                {
                    auto it{std::begin(out_range)};
                    for(auto c : txt)
                    {
                        if(durability_.degrade(c))
                        {
                            if((*it) == ' ') (*it++) = c;
                            else (*it++) = '@';
                        }
                        else (*it++) = ' ';
                    }
                }
            void sharpen()
                {
                    if(length_--) durability_ = initial_durability_;
                }
            template<class Range>
            Range erase_from(Range range)
                {
                    return eraser_.erase(range);
                }
            const durability initial_durability_;
            durability durability_;
            length length_;
            eraser eraser_;
        };
        auto find_last(const std::string& txt, paper& p)
        {
            const auto& paper_range{boost::make_iterator_range(p.begin(), p.end())};
            return boost::find_last(paper_range, txt);
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
                    pen_.write_to(txt, std::back_inserter(paper_));
                }
            auto erase(const std::string& txt)
                {
                    return pen_.erase_from(find_last(txt, paper_));
                }
            template<class Range>
            void insert(const std::string& txt, const Range& insert_range)
                {
                    pen_.insert_to(txt, insert_range);
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

    TEST_CASE(
        "As a writer "
        "I want to be able use a pencil to write text on a sheet of paper "
        "so that I can better remember my thoughts")
    {
        scratch_pad pad
            {
                paper{},
                pen
                {
                    durability{8},
                    length{1},
                    eraser
                    {
                        durability{4}
                    }
                }
            };

        pad.write("abc");
        CHECK(pad.text() == "abc");

        pad.write("def");
        CHECK(pad.text() == "abcdef");
    }

    TEST_CASE(
        "As a pencil manufacturer "
        "I want writing to cause a pencil point to go dull "
        "so that I can sell more pencils")
    {
        scratch_pad pad
            {
                paper{},
                pen
                {
                    durability{2},
                    length{1},
                    eraser
                    {
                        durability{4}
                    }
                }
            };
        SUBCASE(
            "lowercase letters should degrade the pencil point by a value of one")
        {
            pad.write("abc");
            CHECK(pad.text() == "ab ");
            SUBCASE(
                "As a writer "
                "I want to be able to sharpen my pencil "
                "so that I can continue to write with it after it goes dull")
            {
                pad.sharpen_pen();
                pad.write("abc");
                CHECK(pad.text() == "ab ab ");
                SUBCASE(
                    "When a pencil's length is zero, "
                    "then sharpening it "
                    "no longer restores its point durabliity")
                {
                    pad.sharpen_pen();
                    pad.write("abc");
                    CHECK(pad.text() == "ab ab    ");
                }
            }
        }
        SUBCASE(
            "capital letters should degrade the point by two")
        {
            pad.write("ABC");
            CHECK(pad.text() == "A  ");
        }
        SUBCASE(
            "Writing spaces and newlines expends no graphite; "
            "therefore these characters should not affect the pencil point")
        {
            pad.write("  \nab\n");
            CHECK(pad.text() == "  \nab\n");
        }
    }

    TEST_CASE(
        "As a writer "
        "I want to be able to erase previously written text "
        "so that I can remove my mistakes")
    {
        scratch_pad pad
            {
                paper{},
                pen
                {
                    durability{100},
                    length{1},
                    eraser
                    {
                        durability{4}
                    }
                }
            };
        pad.write("abcabc");
        const auto& erased_range{pad.erase("ab")};
        CHECK(pad.text() == "abc  c");
        SUBCASE(
            "As a writer "
            "I want to be able edit previously written text "
            "so that I can change my writing without starting over")
        {
            pad.insert("de", erased_range);
            CHECK(pad.text() == "abcdec");
        }
        SUBCASE(
            "If the new text is longer than the allocated whitespace "
            "collisions should be represented by the @ character")
        {
            pad.insert("def", erased_range);
            CHECK(pad.text() == "abcde@");
        }
        SUBCASE(
            "As a pencil manufacturer "
            "I want a pencil eraser to eventually wear out "
            "so that I can sell more pencils")
        {
            SUBCASE(
                "all characters except for white space "
                "should degrade the eraser by a value of one")
            {
                pad.erase("  ");
                CHECK(pad.text() == "abc  c");
                pad.erase("ab");
                CHECK(pad.text() == "  c  c");
                SUBCASE(
                    "Once the eraser durability is zero, "
                    "the eraser is worn out "
                    "and can no longer erase")
                {
                    pad.erase("c");
                    CHECK(pad.text() == "  c  c");
                }
            }
        }
    }
}
