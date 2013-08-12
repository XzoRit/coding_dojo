#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/numeric.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator/comparison.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/string.hpp>

#include <sstream> // boost stream?
#include <stdexcept> // boost exception?

namespace StringCalculator
{
  template<typename IterOut>
  void make_ints_from_str(boost::container::string const& numsAsString, boost::container::string const& sep, IterOut out)
  {
    using boost::lexical_cast;
    using boost::bind;

    using boost::algorithm::split;
    using boost::algorithm::is_any_of;

    using boost::range::transform;
    using boost::range::push_back;
    using boost::range::copy;
    using boost::adaptors::filtered;
    
    using boost::phoenix::arg_names::arg1;

    using boost::container::vector;
    using boost::container::string;

    if(numsAsString.empty()) return;

    vector<string> sepNumsAsString;
    split(sepNumsAsString, numsAsString, is_any_of(sep));

    vector<int> ints(sepNumsAsString.size(), 0);
    transform(sepNumsAsString, ints.begin(), bind(lexical_cast<int, string>, _1));

    vector<int> negNums;
    push_back(negNums, ints | filtered(arg1 < 0));
    if(negNums.empty())
      {
        copy(ints, out);
      }
    else
      {
	std::ostringstream exceptTxt;
	exceptTxt << "Negative numbers not allowed: ";
        transform(negNums, std::ostream_iterator<string>(exceptTxt, " "), bind(&lexical_cast<string, int>, _1));
	throw std::invalid_argument(exceptTxt.str());
      }
  }

  std::pair<boost::container::string, boost::container::string> extractSep(boost::container::string const& parse)
  {
    using boost::container::string;

    static string::size_type const SizeOfSepSection = 4;

    if(parse.size() >= SizeOfSepSection && parse[0] == '/')
      return std::make_pair(string(parse.begin() + SizeOfSepSection, parse.end()), string(1, parse[2]));
    else
      return std::make_pair(parse, ",\n");
  }

  int add(boost::container::string const& nums)
  {
    std::pair<boost::container::string, boost::container::string> const numsAndSep = extractSep(nums);

    boost::container::vector<int> ints;
    make_ints_from_str(numsAndSep.first, numsAndSep.second, std::back_inserter(ints));

    return boost::accumulate(ints, 0);
  }

}

#endif
