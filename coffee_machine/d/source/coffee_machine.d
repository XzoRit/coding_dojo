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

struct BoilingWater
{
  immutable int amountMl;
}
struct Brewing
{
  immutable string what;
}
struct PouringIntoCup
{
  immutable string what;
}

class CaffeineBeverage
{
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
    emit(PouringIntoCup(m_description));
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
    string pouringWhat;

    nothrow void received(BoilingWater boiling)
    {
      amountWaterMl = boiling.amountMl;
    }

    nothrow void received(Brewing brewing)
    {
      brewingWhat = brewing.what;
    }

    nothrow void received(PouringIntoCup pouring)
    {
      pouringWhat = pouring.what;
    }
  }

  const o = new CaffeineBevergeObserver;
  coffee.sigBoilingWater.connect(&o.received);
  coffee.sigBrewing.connect(&o.received);
  coffee.sigPouringIntoCup.connect(&o.received);
  coffee.prepare();
  assert(o.amountWaterMl == coffeeRecipe.amountWaterMl());
  assert(o.brewingWhat == coffeeRecipe.brew());
  assert(o.pouringWhat == coffee.description());
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

class BeverageFactory
{
  this()
  {
    m_factories["coffee"] = new immutable CoffeeFactory();
    m_factories["tea"] = new immutable TeaFactory();
  }

  CaffeineBeverage create(string beverage,
			  void delegate(BoilingWater) boiling,
			  void delegate(Brewing) brewing,
			  void delegate(PouringIntoCup) pouring)
  {
    auto caff = m_factories[beverage].create();
    caff.sigBoilingWater.connect(boiling);
    caff.sigBrewing.connect(brewing);
    caff.sigPouringIntoCup.connect(pouring);
    return caff;
  }

  private immutable(CaffeineBeverageFactory)[string] m_factories;
}

class ConsoleWriter
{
  import std.stdio;
  import std.conv;
  const void received(BoilingWater boiling)
  {
    writeln("boiling " ~ to!string(boiling.amountMl) ~ "ml water");
  }

  const void received(Brewing brewing)
  {
    writeln(brewing.what);
  }

  const void received(PouringIntoCup pouring)
  {
    writeln("pouring " ~ pouring.what ~ " into cup");
  }
}

// void main()
// {
//   auto consoleWriter = new ConsoleWriter();
//   auto beverageFactory = new BeverageFactory();
//   beverageFactory
//     .create("coffee",
// 	    &consoleWriter.received,
// 	    &consoleWriter.received,
// 	    &consoleWriter.received).prepare();
//   beverageFactory
//     .create("tea",
// 	    &consoleWriter.received,
// 	    &consoleWriter.received,
// 	    &consoleWriter.received).prepare();
// }
