class Recipe
{
  alias FuncAmountWaterMlType = int delegate() pure nothrow;
  alias FuncBrewType = string delegate() pure nothrow;

  this(const(FuncAmountWaterMlType) funcAmountWaterMl,
       const(FuncBrewType) funcBrew) pure nothrow
  {
    m_amountWaterMl = funcAmountWaterMl;
    m_brew = funcBrew;
  }

  int amountWaterMl() const pure nothrow
  out (result)
    {
      assert(result > 0);
    }
  body
    {
      return m_amountWaterMl();
    }

  string brew() const pure nothrow
  out (result)
    {
      assert(result.length > 0);
    }
  body
    {
      return m_brew();
    }

  private const(FuncAmountWaterMlType) m_amountWaterMl;
  private const(FuncBrewType) m_brew;
}

struct Recipes
{
  static Recipe tea() pure nothrow
  {
    return new Recipe(() => amountWaterMl(200),
		      () => brewTea());
  }

  static Recipe coffee() pure nothrow
  {
    return new Recipe(() => amountWaterMl(175),
		      () => brewCoffee());
  }

  static int amountWaterMl(int amount) pure nothrow
  {
    return amount;
  }

  static string brewTea() pure nothrow
  {
    return "steeping tea";
  }

  static string brewCoffee() pure nothrow
  {
    return "dripping coffee through filter";
  }
}

class Condiment
{
  final string description() const pure nothrow
  {
    return this.onDescription();
  }

  final float price() const pure nothrow
  {
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
}

class Milk : Condiment
{
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
  override string onDescription() const pure nothrow
  {
    return "-Sugar-";
  }

  override float onPrice() const pure nothrow
  {
    return 0.29;
  }
}

class Condiments
{
  import std.algorithm;

  void add(const(Condiment) condiment)
  {
    m_condiments ~= condiment;
  }

  string description() const pure nothrow
  {
    return reduce!((a, b) => a ~ b.description())("", m_condiments);
  }

  float price() const pure nothrow
  {
    return reduce!((a, b) => a + b.price())(0.0, m_condiments);
  }

  private alias ContainerType = const(Condiment)[];
  private ContainerType m_condiments;
}

unittest
{
  auto condiments = new Condiments();
  assert(condiments.description() == "");
  assert(condiments.price() == 0.0);
  auto const milk = new Milk();
  condiments.add(milk);
  assert(condiments.description() == milk.description());
  assert(condiments.price() == milk.price());
  auto const sugar = new Sugar();
  condiments.add(sugar);
  assert(condiments.description() == milk.description() ~ sugar.description());
  assert(condiments.price() == milk.price() + sugar.price());
}

class CondimentFactory
{
  this()
  {
    m_factories["milk"] = () => new Milk();
    m_factories["sugar"] = () => new Sugar();
  }

  Condiment create(string condiment) const
  {
    return m_factories[condiment]();
  }

  private alias FactoryFunc = Condiment function();
  private FactoryFunc[string] m_factories;
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
       const(float) price,
       const(Condiments) condiments)
  {
    m_recipe = recipe;
    m_description = description;
    m_price = price;
    m_condiments = condiments;
  }

  string description() const pure nothrow
  {
    return m_description ~ m_condiments.description();
  }

  float price() const pure nothrow
  {
    return m_price + m_condiments.price();
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

  private const(Recipe) m_recipe;
  private const(string) m_description;
  private const(float) m_price;
  private const(Condiments) m_condiments;
}

alias Beverages = const(CaffeineBeverage)[];

unittest
{
  const coffeeRecipe = Recipes.coffee();
  auto coffee = new CaffeineBeverage(coffeeRecipe, "Coffee", 1.17, new Condiments());
  assert(coffee.description() == "Coffee");

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

class Coffee : CaffeineBeverage
{
  this(const(Condiments) condiments)
    {
      super(Recipes.coffee(),
	    "Coffee",
	    1.50,
	    condiments);
    }
}

class Tea : CaffeineBeverage
{
  this(const(Condiments) condiments)
    {
      super(Recipes.tea(),
	    "Tea",
	    1.20,
	    condiments);
    }
}

class BeverageFactory(Observer)
{
  this(const(Observer) observer)
  {
    m_factories["coffee"] = (const(Condiments) condiments) => new Coffee(condiments);
    m_factories["tea"] = (const(Condiments) condiments) => new Tea(condiments);
    m_observer = observer;
  }

  CaffeineBeverage create(string beverage, const(Condiments) condiments) const
  {
    auto caff = m_factories[beverage](condiments);
    caff.sigBoilingWater.connect(&m_observer.opCall);
    caff.sigBrewing.connect(&m_observer.opCall);
    caff.sigPouringIntoCup.connect(&m_observer.opCall);
    return caff;
  }

  private alias FactoryFunc = CaffeineBeverage function(const(Condiments));
  private FactoryFunc[string]m_factories;
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

  bool placeOrders() const
  {
    writeln("Please press ENTER for placing orders! (q for quit!)");
    return chomp(readln()) != "q";
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
    writeln("The bill:");
    foreach(const beverage; beverages)
      {
	writeln(beverage.description());
	writeln(beverage.price());
      }
    import std.algorithm;
    immutable sum = reduce!((a, b) => a + b)(0.0f, map!(a => a.price())(beverages));
    writeln("The sum: " ~ to!string(sum));
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
  do
    {
      if(!consoleWriter.placeOrders()) break;
      Beverages beverages;
      do
	{
	  string beverage;
	  if(!consoleWriter.askForBeverage(beverage)) break;
	  Condiments condiments = new Condiments();
	  do
	    {
	      string condiment;
	      if(!consoleWriter.askForCondiment(condiment)) break;
	      condiments.add(condimentFactory.create(condiment));
	    } while(true);
	  beverages ~= beverageFactory.create(beverage, condiments);
	  coffeeMachine.request(&beverages[$-1].prepare);
	} while(true);
      coffeeMachine.prepareBeverages();
      consoleWriter.theBill(beverages);
    } while(true);
}
