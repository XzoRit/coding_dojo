#include "gilded_rose.hpp"
#include "articles.hpp"
#include <iostream>

using namespace std;

int main()
{
  Articles articles;
  articles.push_back(Article("+5 Dexterity Vest", 10, 20));
  articles.push_back(AgedBrie(0));
  articles.push_back(Article("Elixir of the Mongoose", 5, 7));
  articles.push_back(Sulfuras());
  articles.push_back(Sulfuras());
  articles.push_back(BackstagePass("TAFKAL80ETC concert", 15, 20));
  articles.push_back(BackstagePass("TAFKAL80ETC concert", 10, 49));
  articles.push_back(BackstagePass("TAFKAL80ETC concert", 5, 49));
  GildedRose<Articles> app(articles);

  cout << "OMGHAI!" << endl;

  for (int day = 0; day <= 30; day++)
    {
      cout << "-------- day " << day << " --------\n";
      cout << app << "\n\n";
      app.updateQuality();
    }
}
