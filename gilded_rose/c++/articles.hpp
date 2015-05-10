#ifndef _ARTICLES_HPP_
#define _ARTICLES_HPP_

#include "article.hpp"
#include "aged_brie.hpp"
#include "backstage_pass.hpp"
#include "sulfuras.hpp"
#include "conjured.hpp"
#include <boost/variant.hpp>
#include <vector>

typedef std::vector<
  boost::variant<
    Article,
    AgedBrie,
    BackstagePass,
    Sulfuras,
    Conjured > >
Articles;

#endif
