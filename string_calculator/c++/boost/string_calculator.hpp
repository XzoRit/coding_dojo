#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/end.hpp>

#include <boost/tokenizer.hpp>

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator/comparison.hpp>

#include <vector>
#include <string>
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
  std::pair<std::string, std::string> extractSep(std::string const& parse)
  {
    static std::string::size_type const SizeOfSepSection = 4;

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
      return std::make_pair(std::string(parse.begin() + SizeOfSepSection, parse.end()), std::string(1, parse[2]));
    else
      return std::make_pair(parse, ",\n");
  }

  int add(std::string const& nums)
  {
    // int sum = 0;
    // client::adder(nums.begin(), nums.end(), sum);
    // return sum;

    using boost::phoenix::arg_names::arg1;
    using boost::adaptors::transformed;
    using boost::adaptors::filtered;

    if(nums.empty()) return 0;

    std::pair<std::string, std::string> const numsAndSep = extractSep(nums);

    typedef boost::char_separator<char> SeparatorType;
    typedef boost::tokenizer<SeparatorType> TokenizerType;

    SeparatorType separator(numsAndSep.second.c_str());
    TokenizerType separatedNums(numsAndSep.first, separator);

    std::vector<int> ints;
    boost::push_back(ints, separatedNums | transformed(&strToInt));

    if(boost::find_if(ints, arg1 < 0) == boost::const_end(ints))
      {
        return boost::accumulate(ints, 0);
      }
    else
      {
	std::vector<int> negNums;
	boost::push_back(negNums, ints | filtered(arg1 < 0));

	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
	boost::copy(negNums, std::ostream_iterator<int>(exceptTxt, " "));
	throw std::invalid_argument(exceptTxt.str());
      }
  }

}

#endif
