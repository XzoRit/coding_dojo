import specd.specd;
import std.stdio;

interface Recipe
{
  int amountWaterMl();
  void brew();
}

class CoffeeRecipe : Recipe
{
  pure nothrow int amountWaterMl()
  {
    return 175;
  }

  unittest
    {
      describe("amount water for coffee")
      	.should("return 175",
      		(new CoffeeRecipe().amountWaterMl().must.equal(175)));
    }

  void brew()
  {
    writeln("dripping coffee through filter");
  }
}

class TeaRecipe : Recipe
{
  pure nothrow int amountWaterMl()
  {
    return 200;
  }

  unittest
    {
      describe("amount water for tea")
      	.should("be 200ml",
      		(new TeaRecipe().amountWaterMl().must.equal(200)));
    }

  void brew()
  {
    writeln("steeping Tea");
  }
}

class CaffeineBeverage
{
  public final pure nothrow string description()
  {
    return m_description;
  }

  private string m_description;
}

unittest
{
  auto caff = new CaffeineBeverage;
  describe("a default constructed caffeine beverage")
    .should("have an empty description",
  	      (caff.description().must.equal("")));
}
