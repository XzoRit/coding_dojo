import specd.specd;

interface Recipe
{
  int amountWaterMl() const pure nothrow
    out (result)
	  {
	    assert(result > 0);
	  }

  string brew() const pure nothrow
    out (result)
	  {
	    assert(result.length > 0);
	  }
}

class CoffeeRecipe : Recipe
{
  int amountWaterMl() const pure nothrow
  {
    return 175;
  }

  unittest
    {
      describe("amount water for coffee")
      	.should("return 175",
      		(new const(CoffeeRecipe)().amountWaterMl().must.equal(175)));
    }

  string brew() const pure nothrow
  {
    return "dripping coffee through filter";
  }

  unittest
    {
      describe("brew")
      	.should("return brewing coffee",
      		(new const(CoffeeRecipe)().brew().must.equal("dripping coffee through filter")));
    }
}

class TeaRecipe : Recipe
{
  int amountWaterMl() const pure nothrow
  {
    return 200;
  }

  unittest
    {
      describe("amount water for tea")
      	.should("be 200ml",
      		(new const(TeaRecipe)().amountWaterMl().must.equal(200)));
    }

  string brew() const pure nothrow
  {
    return "steeping tea";
  }

  unittest
    {
      describe("brew")
      	.should("return steeping tea",
      		(new const(TeaRecipe)().brew().must.equal("steeping tea")));
    }
}

class Condiment
{
  this()
  {
    m_next = null;
  }

  this(const Condiment next)
  {
    m_next = next;
  }

  final string description() const pure nothrow
  {
    if(m_next) return this.onDescription() ~ m_next.description();
    return this.onDescription();
  }

  final float price() const pure nothrow
  {
    if(m_next) return this.onPrice() + m_next.price();
    return this.onPrice();
  }

  string onDescription() const pure nothrow
  {
    return "";
  }

  float onPrice() const pure nothrow
  {
    return 0.0;
  }
  
  private const(Condiment) m_next;
}

class Milk : Condiment
{
  this(const Condiment next)
  {
    super(next);
  }

  override string onDescription() const pure nothrow
  {
    return "-Milk-";
  }

  override float onPrice() const pure nothrow
  {
    return 0.11;
  }
}

class Sugar : Condiment
{
  this(const Condiment next)
  {
    super(next);
  }

  override string onDescription() const pure nothrow
  {
    return "-Sugar-";
  }

  override float onPrice() const pure nothrow
  {
    return 0.29;
  }
}

interface CaffeineCondimentFactory
{
  Condiment create(const Condiment next) const;
}

class MilkFactory : CaffeineCondimentFactory
{
  override Condiment create(const Condiment next) const
  {
    return new Milk(next);
  }
}

class SugarFactory : CaffeineCondimentFactory
{
  override Condiment create(const Condiment next) const
  {
    return new Sugar(next);
  }
}

class CondimentFactory
{
  this()
  {
    m_factories["milk"] = new MilkFactory();
    m_factories["sugar"] = new SugarFactory();
  }

  Condiment create(const string condiment, const Condiment next) const
  {
    return m_factories[condiment].create(next);
  }

  private const(CaffeineCondimentFactory)[const string] m_factories;
}

struct BoilingWater
{
  const(int) amountMl;
}
struct Brewing
{
  const(string) what;
}
struct PouringIntoCup
{
  const(string) what;
}

class CaffeineBeverage
{
  import std.signals;
  mixin Signal!BoilingWater sigBoilingWater;
  mixin Signal!Brewing sigBrewing;
  mixin Signal!PouringIntoCup sigPouringIntoCup;

  this(const(Recipe) recipe,
       const(string) description,
       const(Condiment) condiment)
  {
    m_recipe = recipe;
    m_description = description;
    m_condiments = condiment;
  }

  string description() const pure nothrow
  {
    if(m_condiments) return m_description ~ m_condiments.description();
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

  private const(string) m_description;
  private const(Recipe) m_recipe;
  private const(Condiment) m_condiments;
}

alias const(CaffeineBeverage)[] Beverages;

unittest
{
  const coffeeRecipe = new CoffeeRecipe;
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
  CaffeineBeverage create(const Condiment) const
    out (result)
	  {
	    assert(result !is null);
	  }
}

class CoffeeFactory : CaffeineBeverageFactory
{
  override CaffeineBeverage create(const Condiment condiment) const
  {
    return new CaffeineBeverage(new const(CoffeeRecipe)(),
				"Coffee",
				condiment);
  }
}

class TeaFactory : CaffeineBeverageFactory
{
  override CaffeineBeverage create(const Condiment condiment) const
  {
    return new CaffeineBeverage(new const(TeaRecipe)(),
				"Tea",
				condiment);
  }
}

class BeverageFactory(Observer)
{
  this(const(Observer) observer)
  {
    m_factories["coffee"] = new const(CoffeeFactory)();
    m_factories["tea"] = new const(TeaFactory)();
    m_observer = observer;
  }

  CaffeineBeverage create(string beverage, const Condiment condiment) const
  {
    auto caff = m_factories[beverage].create(condiment);
    caff.sigBoilingWater.connect(&m_observer.opCall);
    caff.sigBrewing.connect(&m_observer.opCall);
    caff.sigPouringIntoCup.connect(&m_observer.opCall);
    return caff;
  }

  private const(CaffeineBeverageFactory)[const(string)] m_factories;
  private const(Observer) m_observer;
}

class ConsoleWriter
{
  import std.stdio;
  import std.conv;
  import std.string;

  void opCall(BoilingWater boiling) const
  {
    writeln("boiling " ~ to!string(boiling.amountMl) ~ "ml water");
  }

  void opCall(Brewing brewing) const
  {
    writeln(brewing.what);
  }

  void opCall(PouringIntoCup pouring) const
  {
    writeln("pouring " ~ pouring.what ~ " into cup");
  }

  void opCall(Starting starting) const
  {
    writeln("starting preparation of " ~ to!string(starting.amount) ~ " beverages");
  }

  void opCall(Preparing preparing) const
  {
    writeln("preparing beverage " ~ to!string(preparing.current));
  }

  void opCall(Finished finished) const
  {
    writeln("finished preparing " ~ to!string(finished.amount) ~ " beverages");
  }

  bool askForBeverage(out string beverage) const
  {
    writeln("What beverage would you like to have? (q for quit!)");
    beverage = chomp(readln());
    return beverage != "q";
  }

  bool askForCondiment(out string condiment) const
  {
    writeln("What condiment would you like to have? (q for quit!)");
    condiment = chomp(readln());
    return condiment != "q";
  }

  void theBill(in Beverages beverages) const
  {
    foreach(const beverage; beverages)
      {
	writeln(beverage.description());
      } 
  }
}

struct Starting
{
  ulong amount;
}
struct Preparing
{
  ulong current;
}
struct Finished
{
  ulong amount;
}

class CoffeeMachine
{
  import std.signals;
  mixin Signal!Starting sigStarting;
  mixin Signal!Preparing sigPreparing;
  mixin Signal!Finished sigFinished;

  void request(BeveragePreparation preparation)
  {
    m_preparations ~= preparation;
  }

  void prepareBeverages()
  {
    starting();
    foreach(current, preparation; m_preparations)
      {
	preparing(current);
	preparation();
      }
    finished();
  }

  private void starting()
  {
    emit(Starting(m_preparations.length));
  }

  private void preparing(ulong current)
  {
    emit(Preparing(current));
  }

  private void finished()
  {
    emit(Finished(m_preparations.length));
    m_preparations.length = 0;
  }

  private alias BeveragePreparation = void delegate();
  private alias BeveragePreparations = BeveragePreparation[];
  private BeveragePreparations m_preparations;
}

unittest
{
  class SigReceiver
  {
    ulong amountStarting;
    ulong currentPreparing;
    ulong amountFinished;

    void received(Starting starting)
    {
      amountStarting = starting.amount;
    }

    void received(Preparing preparing)
    {
      currentPreparing = preparing.current;
    }

    void received(Finished finished)
    {
      amountFinished = finished.amount;
    }
  }

  auto coffeeMachine = new CoffeeMachine();
  auto sigReceiver = new SigReceiver();
  coffeeMachine.sigStarting.connect(&sigReceiver.received);
  coffeeMachine.sigPreparing.connect(&sigReceiver.received);
  coffeeMachine.sigFinished.connect(&sigReceiver.received);
  coffeeMachine.prepareBeverages();

  bool callbackHasBeenCalled = false;
  coffeeMachine.request({ callbackHasBeenCalled = true; });
  coffeeMachine.prepareBeverages();
  assert(callbackHasBeenCalled);
  assert(sigReceiver.amountStarting == 1);
  assert(sigReceiver.currentPreparing == 0);
  assert(sigReceiver.amountFinished == 1);

  coffeeMachine.prepareBeverages();
  assert(sigReceiver.amountStarting == 0);
  assert(sigReceiver.currentPreparing == 0);
  assert(sigReceiver.amountFinished == 0);
}

void main()
{
  auto const consoleWriter = new ConsoleWriter();
  auto const beverageFactory = new BeverageFactory!ConsoleWriter(consoleWriter);
  auto const condimentFactory = new CondimentFactory();
  auto coffeeMachine = new CoffeeMachine();
  coffeeMachine.sigStarting.connect(&consoleWriter.opCall);
  coffeeMachine.sigPreparing.connect(&consoleWriter.opCall);
  coffeeMachine.sigFinished.connect(&consoleWriter.opCall);
  Beverages beverages;
  do
    {
      string beverage;
      if(!consoleWriter.askForBeverage(beverage)) break;
      Condiment condiments;
      do
	{
	  string condiment;
	  if(!consoleWriter.askForCondiment(condiment)) break;
	  condiments = condimentFactory.create(condiment, condiments);
	} while(true);
      beverages ~= beverageFactory.create(beverage, condiments);
      coffeeMachine.request(&beverages[$-1].prepare);
    } while(true);
  coffeeMachine.prepareBeverages();
  consoleWriter.theBill(beverages);
}
