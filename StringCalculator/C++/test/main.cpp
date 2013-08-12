#include <string_calculator.hpp>

#include <lib/convert.hpp>
#include <lib/str_utils.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <iterator>

TEST_CASE("Convert::String::to<int>", "")
{
  CHECK(Convert::String::to<int>("0") == 0);

  CHECK(Convert::String::to<int>("1") == 1);
  CHECK(Convert::String::to<int>("12") == 12);
  CHECK(Convert::String::to<int>("123") == 123);
  CHECK(Convert::String::to<int>("1234") == 1234);
  CHECK(Convert::String::to<int>("12345") == 12345);
  CHECK(Convert::String::to<int>("123456") == 123456);
  CHECK(Convert::String::to<int>("1234567") == 1234567);
  CHECK(Convert::String::to<int>("12345678") == 12345678);
  CHECK(Convert::String::to<int>("123456789") == 123456789);

  CHECK(Convert::String::to<int>("-1") == -1);
  CHECK(Convert::String::to<int>("-12") == -12);
  CHECK(Convert::String::to<int>("-123") == -123);
  CHECK(Convert::String::to<int>("-1234") == -1234);
  CHECK(Convert::String::to<int>("-12345") == -12345);
  CHECK(Convert::String::to<int>("-123456") == -123456);
  CHECK(Convert::String::to<int>("-1234567") == -1234567);
  CHECK(Convert::String::to<int>("-12345678") == -12345678);
  CHECK(Convert::String::to<int>("-123456789") == -123456789);
}

TEST_CASE("Convert::Int::to<std::string>", "")
{
  CHECK(Convert::Int::to<std::string>(0) == "0");
  CHECK(Convert::Int::to<std::string>(1) == "1");
  CHECK(Convert::Int::to<std::string>(12) == "12");
  CHECK(Convert::Int::to<std::string>(123) == "123");
  CHECK(Convert::Int::to<std::string>(1234) == "1234");
  CHECK(Convert::Int::to<std::string>(12345) == "12345");
  CHECK(Convert::Int::to<std::string>(123456) == "123456");
  CHECK(Convert::Int::to<std::string>(1234567) == "1234567");
  CHECK(Convert::Int::to<std::string>(12345678) == "12345678");
  CHECK(Convert::Int::to<std::string>(123456789) == "123456789");

  CHECK(Convert::Int::to<std::string>(-1) == "-1");
  CHECK(Convert::Int::to<std::string>(-12) == "-12");
  CHECK(Convert::Int::to<std::string>(-123) == "-123");
  CHECK(Convert::Int::to<std::string>(-1234) == "-1234");
  CHECK(Convert::Int::to<std::string>(-12345) == "-12345");
  CHECK(Convert::Int::to<std::string>(-123456) == "-123456");
  CHECK(Convert::Int::to<std::string>(-1234567) == "-1234567");
  CHECK(Convert::Int::to<std::string>(-12345678) == "-12345678");
  CHECK(Convert::Int::to<std::string>(-123456789) == "-123456789");
}

using namespace StrUtil;

TEST_CASE("split(,)", "")
{
  std::vector<std::string> splitted;
  split("", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "");

  splitted.clear();
  split("  ", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "  ");

  splitted.clear();
  split("0123456789", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "0123456789");

  splitted.clear();
  split("1,2", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");

  splitted.clear();
  split("123,234", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "123");
  CHECK(splitted[1] == "234");

  splitted.clear();
  split("1,2,3,4,5,6,7,8,9,0", ",", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);
  CAPTURE(splitted[9]);

  CHECK(splitted.size() == 10);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");
  CHECK(splitted[2] == "3");
  CHECK(splitted[3] == "4");
  CHECK(splitted[4] == "5");
  CHECK(splitted[5] == "6");
  CHECK(splitted[6] == "7");
  CHECK(splitted[7] == "8");
  CHECK(splitted[8] == "9");
  CHECK(splitted[9] == "0");

  splitted.clear();
  split("1,22,333,4444,55555,666666,7777777,88888888,999999999", ",", std::back_inserter(splitted));

  REQUIRE(splitted.size() == 9);

  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);

  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "22");
  CHECK(splitted[2] == "333");
  CHECK(splitted[3] == "4444");
  CHECK(splitted[4] == "55555");
  CHECK(splitted[5] == "666666");
  CHECK(splitted[6] == "7777777");
  CHECK(splitted[7] == "88888888");
  CHECK(splitted[8] == "999999999");
}

TEST_CASE("split(\\n)", "")
{
  std::vector<std::string> splitted;
  split("", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "");

  splitted.clear();
  split("  ", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "  ");

  splitted.clear();
  split("0123456789", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);

  CHECK(splitted.size() == 1);
  CHECK(splitted[0] == "0123456789");

  splitted.clear();
  split("1\n2", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");

  splitted.clear();
  split("123\n234", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "123");
  CHECK(splitted[1] == "234");

  splitted.clear();
  split("1\n2\n3\n4\n5\n6\n7\n8\n9\n0", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);
  CAPTURE(splitted[9]);

  CHECK(splitted.size() == 10);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");
  CHECK(splitted[2] == "3");
  CHECK(splitted[3] == "4");
  CHECK(splitted[4] == "5");
  CHECK(splitted[5] == "6");
  CHECK(splitted[6] == "7");
  CHECK(splitted[7] == "8");
  CHECK(splitted[8] == "9");
  CHECK(splitted[9] == "0");

  splitted.clear();
  split("1\n22\n333\n4444\n55555\n666666\n7777777\n88888888\n999999999", "\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);
  CAPTURE(splitted[9]);

  CHECK(splitted.size() == 9);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "22");
  CHECK(splitted[2] == "333");
  CHECK(splitted[3] == "4444");
  CHECK(splitted[4] == "55555");
  CHECK(splitted[5] == "666666");
  CHECK(splitted[6] == "7777777");
  CHECK(splitted[7] == "88888888");
  CHECK(splitted[8] == "999999999");
}

TEST_CASE("split(,\\n)", "")
{
  std::vector<std::string> splitted;
  split("1,2", ",\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");

  splitted.clear();
  split("1\n2", ",\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");

  splitted.clear();
  split("123\n234", ",\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);

  CHECK(splitted.size() == 2);
  CHECK(splitted[0] == "123");
  CHECK(splitted[1] == "234");

  splitted.clear();
  split("1\n2\n3\n4\n5\n6\n7\n8\n9\n0", ",\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);
  CAPTURE(splitted[9]);

  CHECK(splitted.size() == 10);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "2");
  CHECK(splitted[2] == "3");
  CHECK(splitted[3] == "4");
  CHECK(splitted[4] == "5");
  CHECK(splitted[5] == "6");
  CHECK(splitted[6] == "7");
  CHECK(splitted[7] == "8");
  CHECK(splitted[8] == "9");
  CHECK(splitted[9] == "0");

  splitted.clear();
  split("1\n22\n333\n4444\n55555\n666666\n7777777\n88888888\n999999999", ",\n", std::back_inserter(splitted));

  CAPTURE(splitted.size());
  CAPTURE(splitted[0]);
  CAPTURE(splitted[1]);
  CAPTURE(splitted[2]);
  CAPTURE(splitted[3]);
  CAPTURE(splitted[4]);
  CAPTURE(splitted[5]);
  CAPTURE(splitted[6]);
  CAPTURE(splitted[7]);
  CAPTURE(splitted[8]);
  CAPTURE(splitted[9]);

  CHECK(splitted.size() == 9);
  CHECK(splitted[0] == "1");
  CHECK(splitted[1] == "22");
  CHECK(splitted[2] == "333");
  CHECK(splitted[3] == "4444");
  CHECK(splitted[4] == "55555");
  CHECK(splitted[5] == "666666");
  CHECK(splitted[6] == "7777777");
  CHECK(splitted[7] == "88888888");
  CHECK(splitted[8] == "999999999");
}

using namespace StringCalculator;

TEST_CASE("extractSep", "")
{
  CHECK(extractSep("//T\n").second == "T");
  CHECK(extractSep("//;\n").second == ";");
  CHECK(extractSep("//-\n").second == "-");
  CHECK(extractSep("//a\n").second == "a");
  CHECK(extractSep("///\n").second == "/");
  CHECK(extractSep("//\n\n").second == "\n");

  CHECK(extractSep("").second == ",\n");
  CHECK(extractSep("/").second == ",\n");
  CHECK(extractSep("//").second == ",\n");
  CHECK(extractSep("\n").second == ",\n");
  CHECK(extractSep("//\n").second == ",\n");
}

TEST_CASE("add(\"\")", "When called with an empty text returns 0")
{
  CHECK(StringCalculator::add("") == 0);
}

TEST_CASE("add(\"one number\")", "When called with one number returns it")
{
  CHECK(StringCalculator::add("0")     == 0);
  CHECK(StringCalculator::add("1")     == 1);
  CHECK(StringCalculator::add("12")    == 12);
  CHECK(StringCalculator::add("123")   == 123);
  CHECK(StringCalculator::add("1234")  == 1234);
  CHECK(StringCalculator::add("12345") == 12345);
}

TEST_CASE("add(\"1st,2nd\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0,0") == 0);
  CHECK(StringCalculator::add("0,1") == 1);
  CHECK(StringCalculator::add("1,2") == 3);
  CHECK(StringCalculator::add("11,12") == 23);
  CHECK(StringCalculator::add("12,34") == 46);
  CHECK(StringCalculator::add("1000000,1000000") == 2000000);
}

TEST_CASE("add(\"1st,2nd,...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0,0,0,0") == 0);
  CHECK(StringCalculator::add("0,1,0,2") == 3);
  CHECK(StringCalculator::add("1,2,3,4,5,6,7,8,9,0") == 45);
  CHECK(StringCalculator::add("11,12,13,14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000,1000000") == 3000000);
}

TEST_CASE("add(\"1st\\n2nd\\n...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("0\n1\n0\n2") == 3);
  CHECK(StringCalculator::add("1\n2\n3\n4\n5\n6\n7\n8\n9\n0") == 45);
  CHECK(StringCalculator::add("11\n12\n13\n14\n15") == 65);
  CHECK(StringCalculator::add("1000000\n1000000\n1000000") == 3000000);
}

TEST_CASE("add(\"1st(,\\n)2nd(,\\n)...\")", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("0\n0,0\n0") == 0);
  CHECK(StringCalculator::add("0,1\n0,2") == 3);
  CHECK(StringCalculator::add("1\n2\n3,4,5\n6\n7,8\n9\n0") == 45);
  CHECK(StringCalculator::add("11,12\n13\n14,15") == 65);
  CHECK(StringCalculator::add("1000000,1000000\n1000000") == 3000000);
}

TEST_CASE("add(With Sep Spec line)", "When called with two number returns sum")
{
  CHECK(StringCalculator::add("//\n\n0\n0\n0\n0") == 0);
  CHECK(StringCalculator::add("//,\n0,1,22") == 23);
  CHECK(StringCalculator::add("//\\\n11\\2\\3\\4\\5\\6\\7\\8\\9\\0") == 55);
  CHECK(StringCalculator::add("//-\n11-12-13-14-15") == 65);
  CHECK(StringCalculator::add("//:\n1000000:1000000:1000000") == 3000000);
    }

TEST_CASE("add(With Neg Nums)", "When called with two number returns sum")
{
  REQUIRE_THROWS_AS(StringCalculator::add("1,-1,1,-1"), std::invalid_argument);
  try
    {
      StringCalculator::add("1,-1,1,-1");
    }
  catch(std::invalid_argument const& e)
    {
      CHECK(e.what() == std::string("Negative numbers not allowed: -1 -1 "));
    }
}
