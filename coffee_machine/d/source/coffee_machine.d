import specd.specd;

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
  }
}

class CaffeineBeverage
{
  this(Recipe recipe, string description)
  {
    m_description = description;
    m_recipe = recipe;
  }

  final pure nothrow string description()
  {
    return m_description;
  }

  void prepare()
  {
    boilWater(m_recipe.amountWaterMl());
    m_recipe.brew();
    pourInCup();
  }

  private void boilWater(int amountWaterMl)
  {
  }

  private void pourInCup()
  {
  }

  private string m_description;
  private Recipe m_recipe;
}

unittest
{
  auto caff = new CaffeineBeverage(null, "Caff");
  describe("a call to descrption")
    .should("return same text as given in ctor",
  	      (caff.description().must.equal("Caff")));
}
