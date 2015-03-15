import specd.specd;
import std.signals;

interface Recipe
{
  immutable pure nothrow int amountWaterMl()
    out (result)
	  {
	    assert(result > 0);
	  }

  immutable pure nothrow string brew()
    out (result)
	  {
	    assert(result.length > 0);
	  }
}

class CoffeeRecipe : Recipe
{
  immutable pure nothrow int amountWaterMl()
  {
    return 175;
  }

  unittest
    {
      describe("amount water for coffee")
      	.should("return 175",
      		(new immutable CoffeeRecipe().amountWaterMl().must.equal(175)));
    }

  immutable pure nothrow string brew()
  {
    return "dripping coffee through filter";
  }

  unittest
    {
      describe("brew")
      	.should("return brewing coffee",
      		(new immutable CoffeeRecipe().brew().must.equal("dripping coffee through filter")));
    }
}

class TeaRecipe : Recipe
{
  immutable pure nothrow int amountWaterMl()
  {
    return 200;
  }

  unittest
    {
      describe("amount water for tea")
      	.should("be 200ml",
      		(new immutable TeaRecipe().amountWaterMl().must.equal(200)));
    }

  immutable pure nothrow string brew()
  {
    return "steeping tea";
  }

  unittest
    {
      describe("brew")
      	.should("return steeping tea",
      		(new immutable TeaRecipe().brew().must.equal("steeping tea")));
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

  this(immutable Recipe recipe, immutable string description)
  {
    m_description = description;
    m_recipe = recipe;
  }

  const pure nothrow string description()
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

  private immutable string m_description;
  private immutable Recipe m_recipe;
}

unittest
{
  immutable coffeeRecipe = new CoffeeRecipe;
  auto coffee = new CaffeineBeverage(coffeeRecipe, "Coffee");
  describe("a call to descrption")
    .should("return same text as given in ctor",
	    (coffee.description().must.equal("Coffee")));

  class CaffeineBevergeObserver
  {
    int amountWaterMl;
    string brewingWhat;
    bool receivedPouringIntoCup;

    nothrow void received(CaffeineBeverage.BoilingWater boiling)
    {
      amountWaterMl = boiling.amountMl;
    }

    nothrow void received(CaffeineBeverage.Brewing brewing)
    {
      brewingWhat = brewing.description;
    }

    nothrow void received(CaffeineBeverage.PouringIntoCup)
    {
      receivedPouringIntoCup = true;
    }
  }

  const o = new CaffeineBevergeObserver;
  coffee.sigBoilingWater.connect(&o.received);
  coffee.sigBrewing.connect(&o.received);
  coffee.sigPouringIntoCup.connect(&o.received);
  coffee.prepare();
  assert(o.amountWaterMl == coffeeRecipe.amountWaterMl());
  assert(o.brewingWhat == coffeeRecipe.brew());
  assert(o.receivedPouringIntoCup);
}

interface CaffeineBeverageFactory
{
  immutable CaffeineBeverage create()
    out (result)
	  {
	    assert(result !is null);
	  }
}

class CoffeeFactory : CaffeineBeverageFactory
{
  immutable CaffeineBeverage create()
  {
    return new CaffeineBeverage(new immutable CoffeeRecipe(), "Coffee");
  }
}

class TeaFactory : CaffeineBeverageFactory
{
  immutable CaffeineBeverage create()
  {
    return new CaffeineBeverage(new immutable TeaRecipe(), "Tea");
  }
}

class BeverageFactory(BeverageObserver)
{
  this()
  {
    m_factories["coffee"] = new immutable CoffeeFactory();
    m_factories["tea"] = new immutable TeaFactory();
    m_observer = new BeverageObserver();
  }

  CaffeineBeverage create(string beverage)
  {
    auto caff = m_factories[beverage].create();
    caff.sigBoilingWater.connect(&m_observer.received);
    caff.sigBrewing.connect(&m_observer.received);
    caff.sigPouringIntoCup.connect(&m_observer.received);
    return caff;
  }

  private immutable(CaffeineBeverageFactory)[string] m_factories;
  private BeverageObserver m_observer;
}

class ConsoleWriter
{
  import std.stdio;
  import std.conv;
  void received(CaffeineBeverage.BoilingWater boiling)
  {
    writeln("boiling " ~ to!string(boiling.amountMl) ~ "ml water");
  }

  void received(CaffeineBeverage.Brewing brewing)
  {
    writeln(brewing.description);
  }

  void received(CaffeineBeverage.PouringIntoCup)
  {
    writeln("pouring into cup");
  }
}

void main()
{
  alias ConsoleBeveregeFactory = BeverageFactory!ConsoleWriter; 
  auto consoleBeverageFactory = new ConsoleBeveregeFactory();
  consoleBeverageFactory.create("coffee").prepare();
  consoleBeverageFactory.create("tea").prepare();
}
