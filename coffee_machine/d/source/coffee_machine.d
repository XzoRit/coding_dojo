import specd.specd;
import std.signals;

interface Recipe
{
  int amountWaterMl();
  string brew();
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

  string brew()
  {
    return "dripping coffee through filter";
  }

  unittest
    {
      describe("brew")
      	.should("return brewing coffee",
      		(new CoffeeRecipe().brew().must.equal("dripping coffee through filter")));
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

  string brew()
  {
    return "steeping tea";
  }

  unittest
    {
      describe("brew")
      	.should("return steeping tea",
      		(new TeaRecipe().brew().must.equal("steeping tea")));
    }
}

class CaffeineBeverage
{
  struct BoilingWater
  {
    int amountMl;
  }
  struct Brewing
  {
    string description;
  }
  struct PouringIntoCup
  {}

  mixin Signal!BoilingWater sigBoilingWater;
  mixin Signal!Brewing sigBrewing;
  mixin Signal!PouringIntoCup sigPouringIntoCup;

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
    brewing(m_recipe.brew());
    pourInCup();
  }

  private void boilWater(int amountWaterMl)
  {
    emit(BoilingWater(amountWaterMl));
  }

  private void brewing(string what)
  {
    emit(Brewing(what));
  }

  private void pourInCup()
  {
    emit(PouringIntoCup());
  }

  private string m_description;
  private Recipe m_recipe;
}

unittest
{
  auto coffeeRecipe = new CoffeeRecipe;
  auto caff = new CaffeineBeverage(coffeeRecipe, "Caff");
  describe("a call to descrption")
    .should("return same text as given in ctor",
  	      (caff.description().must.equal("Caff")));
  class Observer
  {
    int amountWaterMl;
    string brewingWhat;
    bool receivedPouringIntoCup;

    void received(CaffeineBeverage.BoilingWater boiling)
    {
      amountWaterMl = boiling.amountMl;
    }

    void received(CaffeineBeverage.Brewing brewing)
    {
      brewingWhat = brewing.description;
    }

    void received(CaffeineBeverage.PouringIntoCup)
    {
      receivedPouringIntoCup = true;
    }
  }

  auto  o = new Observer;
  caff.sigBoilingWater.connect(&o.received);
  caff.sigBrewing.connect(&o.received);
  caff.sigPouringIntoCup.connect(&o.received);
  caff.prepare();
  assert(o.amountWaterMl == coffeeRecipe.amountWaterMl());
  assert(o.brewingWhat == coffeeRecipe.brew());
  assert(o.receivedPouringIntoCup);
}
