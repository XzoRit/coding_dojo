#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <lib/str_utils.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator/comparison.hpp>

#include <vector>
#include <string>
#include <functional>
#include <sstream> // boost stream?
#include <stdexcept> // boost exception?
#include <iterator>

#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
 
int strToInt(std::string const& str)
{
  int result;
  std::string::const_iterator i = str.begin();
  if(boost::spirit::qi::parse(i, str.end(), boost::spirit::int_, result)) return result;
  else throw std::invalid_argument(str.c_str());
}

// #include <boost/spirit/include/qi.hpp>
// #include <boost/spirit/include/phoenix_core.hpp>
// #include <boost/spirit/include/phoenix_operator.hpp>
// #include <iostream>
// #include <string>

// namespace client
// {
//     namespace qi = boost::spirit::qi;
//     namespace ascii = boost::spirit::ascii;
//     namespace phoenix = boost::phoenix;

//     using qi::int_;
//     using qi::_1;
//     using ascii::space;
//     using phoenix::ref;

//     template <typename Iterator>
//     bool adder(Iterator first, Iterator last, int& n)
//     {
//         bool r = qi::phrase_parse(first, last,
//             (
//                 int_[ref(n) = _1] >> *(',' >> int_[ref(n) += _1])
// 	    ),
//             space);

//         if (first != last) return false;
//         return r;
//     }
// }

namespace StringCalculator
{
  template<typename IterOut>
  void make_ints_from_str(std::string const& numsAsString, std::string const& sep, IterOut out)
  {
    using boost::lexical_cast;
    using boost::bind;

    using boost::range::transform;
    using boost::range::push_back;
    using boost::range::copy;
    using boost::range::find_if;
    using boost::adaptors::filtered;
    
    using boost::phoenix::arg_names::arg1;

    using std::vector;
    using std::string;

    if(numsAsString.empty()) return;

    vector<string> sepNumsAsString;
    StrUtil::split(numsAsString.c_str(), sep.c_str(), std::back_inserter(sepNumsAsString));

    vector<int> ints(sepNumsAsString.size(), 0);
    transform(sepNumsAsString, boost::begin(ints), &strToInt);

    if(find_if(ints, arg1 < 0) == boost::const_end(ints))
      {
        copy(ints, out);
      }
    else
      {
	vector<int> negNums;
	push_back(negNums, ints | filtered(arg1 < 0));

	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
        copy(negNums, std::ostream_iterator<int>(exceptTxt, " "));

	throw std::invalid_argument(exceptTxt.str());
      }
  }

  std::pair<std::string, std::string> extractSep(std::string const& parse)
  {
    using std::string;

    static string::size_type const SizeOfSepSection = 4;

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
      return std::make_pair(string(parse.begin() + SizeOfSepSection, parse.end()), string(1, parse[2]));
    else
      return std::make_pair(parse, ",\n");
  }

  int add(std::string const& nums)
  {
    // int sum = 0;
    // client::adder(nums.begin(), nums.end(), sum);
    // return sum;

    std::pair<std::string, std::string> const numsAndSep = extractSep(nums);

    std::vector<int> ints;
    make_ints_from_str(numsAndSep.first, numsAndSep.second, std::back_inserter(ints));

    return boost::accumulate(ints, 0);
  }

}

#endif
