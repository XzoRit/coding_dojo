import specd.specd;
import std.signals;

interface Recipe
{
  int amountWaterMl() immutable pure nothrow
    out (result)
	  {
	    assert(result > 0);
	  }

  string brew() immutable pure nothrow
    out (result)
	  {
	    assert(result.length > 0);
	  }
}

class CoffeeRecipe : Recipe
{
  int amountWaterMl() immutable pure nothrow
  {
    return 175;
  }

  unittest
    {
      describe("amount water for coffee")
      	.should("return 175",
      		(new immutable(CoffeeRecipe)().amountWaterMl().must.equal(175)));
    }

  string brew() immutable pure nothrow
  {
    return "dripping coffee through filter";
  }

  unittest
    {
      describe("brew")
      	.should("return brewing coffee",
      		(new immutable(CoffeeRecipe)().brew().must.equal("dripping coffee through filter")));
    }
}

class TeaRecipe : Recipe
{
  int amountWaterMl() immutable pure nothrow
  {
    return 200;
  }

  unittest
    {
      describe("amount water for tea")
      	.should("be 200ml",
      		(new immutable(TeaRecipe)().amountWaterMl().must.equal(200)));
    }

  immutable pure nothrow string brew()
  {
    return "steeping tea";
  }

  unittest
    {
      describe("brew")
      	.should("return steeping tea",
      		(new immutable(TeaRecipe)().brew().must.equal("steeping tea")));
    }
}

struct BoilingWater
{
  immutable(int) amountMl;
}
struct Brewing
{
  immutable(string) what;
}
struct PouringIntoCup
{
  immutable(string) what;
}

class CaffeineBeverage
{
  mixin Signal!BoilingWater sigBoilingWater;
  mixin Signal!Brewing sigBrewing;
  mixin Signal!PouringIntoCup sigPouringIntoCup;

  this(immutable(Recipe) recipe, immutable(string) description)
  {
    m_description = description;
    m_recipe = recipe;
  }

  string description() const pure nothrow
  {
    return m_description;
  }

  void prepare()
  {
    boilWater(m_recipe.amountWaterMl());
    brewing(m_recipe.brew());
    pouringIntoCup();
  }

  private void boilWater(int amountWaterMl)
  {
    emit(BoilingWater(amountWaterMl));
  }

  private void brewing(string what)
  {
    emit(Brewing(what));
  }

  private void pouringIntoCup()
  {
    emit(PouringIntoCup(m_description));
  }

  private immutable(string) m_description;
  private immutable(Recipe) m_recipe;
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

    void received(BoilingWater boiling) nothrow
    {
      amountWaterMl = boiling.amountMl;
    }

    void received(Brewing brewing) nothrow
    {
      brewingWhat = brewing.what;
    }

    void received(PouringIntoCup pouring) nothrow
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
  CaffeineBeverage create() immutable
    out (result)
	  {
	    assert(result !is null);
	  }
}

class CoffeeFactory : CaffeineBeverageFactory
{
  CaffeineBeverage create() immutable
  {
    return new CaffeineBeverage(new immutable(CoffeeRecipe)(), "Coffee");
  }
}

class TeaFactory : CaffeineBeverageFactory
{
  CaffeineBeverage create() immutable
  {
    return new CaffeineBeverage(new immutable(TeaRecipe)(), "Tea");
  }
}

class BeverageFactory(Observer)
{
  this(const(Observer) observer)
  {
    m_factories["coffee"] = new immutable(CoffeeFactory)();
    m_factories["tea"] = new immutable(TeaFactory)();
    m_observer = observer;
  }

  CaffeineBeverage create(string beverage) const
  {
    auto caff = m_factories[beverage].create();
    caff.sigBoilingWater.connect(&m_observer.opApply);
    caff.sigBrewing.connect(&m_observer.opApply);
    caff.sigPouringIntoCup.connect(&m_observer.opApply);
    return caff;
  }

  private immutable(CaffeineBeverageFactory)[immutable(string)] m_factories;
  private const(Observer) m_observer;
}

class ConsoleWriter
{
  import std.stdio;

  void opApply(BoilingWater boiling) const
  {
    import std.conv;
    writeln("boiling " ~ to!string(boiling.amountMl) ~ "ml water");
  }

  void opApply(Brewing brewing) const
  {
    writeln(brewing.what);
  }

  void opApply(PouringIntoCup pouring) const
  {
    writeln("pouring " ~ pouring.what ~ " into cup");
  }

  bool askForBeverage(out string beverage) const
  {
    import std.string;
    writeln("What beverage would you like to have? (q for quit!)");
    beverage = chomp(readln());
    return beverage != "q";
  }
}

class CoffeeMachine
{
  void request(BeveragePreparation preparation)
  {
    m_preparations ~= preparation;
  }

  void prepareBeverages()
  {
    foreach(preparation; m_preparations) preparation();
  }

  private alias BeveragePreparation = void delegate();
  private alias BeveragePreparations = BeveragePreparation[];
  private BeveragePreparations m_preparations;
}

unittest
{
  auto coffeeMachine = new CoffeeMachine();
  bool callbackHasBeenCalled = false;
  coffeeMachine.request({ callbackHasBeenCalled = true; });
  coffeeMachine.prepareBeverages();
  assert(callbackHasBeenCalled);
}

void main()
{
  auto const consoleWriter = new ConsoleWriter();
  auto const beverageFactory = new BeverageFactory!ConsoleWriter(consoleWriter);
  auto coffeeMachine = new CoffeeMachine();
  do
    {
      string beverage;
      if(!consoleWriter.askForBeverage(beverage)) break;
      coffeeMachine.request(&beverageFactory.create(beverage).prepare);
  } while(true);
  coffeeMachine.prepareBeverages();
}
