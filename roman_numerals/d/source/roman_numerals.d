module xzr.roman_numerals;

import specd.specd;

struct ArabicToRoman
{
  struct Imperativ
  {
    static auto convert(int arabic) pure nothrow @safe
      in
	{
	  assert(arabic >= 0);
	  assert(arabic <= 3999);
	}
    out(result)
      {
	assert(result.length <= 15);
      }
    body
      {
	string roman;
	foreach(mapping; symbolTable)
	  {
	    while(arabic >= mapping.arabic)
	      {
		roman ~= mapping.roman;
		arabic -= mapping.arabic;
	      }
	  }
	return roman;
      }

    import std.typecons : Tuple;
    private alias ArabicRoman = Tuple!(int, "arabic", string, "roman");
    private static immutable ArabicRoman[] symbolTable =
      [
       ArabicRoman(1000, "M"),
       ArabicRoman(900, "CM"),
       ArabicRoman(500, "D"),
       ArabicRoman(400, "CD"),
       ArabicRoman(100, "C"),
       ArabicRoman(90, "XC"),
       ArabicRoman(50, "L"),
       ArabicRoman(40, "XL"),
       ArabicRoman(10, "X"),
       ArabicRoman(9, "IX"),
       ArabicRoman(5, "V"),
       ArabicRoman(4, "IV"),
       ArabicRoman(1, "I")
       ];

  }
  
  struct Functional
  {
    import std.conv : to;
    import std.string : rightJustifier;
    import std.algorithm : map;
    import std.array : array, join;
    import std.range : zip;
    import std.functional : pipe;

    static auto digits_of(immutable int num) pure @safe
    {      
      return num.to!string()
	.rightJustifier(4, '0')
	.map!(a => to!int(a) - 48)
	.array();
    }

    static auto to_roman(immutable int[] digits) pure @safe
    {
      return zip(symbolTable, digits).map!(a => a[0][a[1]]).array();
    }

    static auto join_symbols(immutable string[] symbols) pure @safe
    {
      return join(symbols);
    }

    static auto convert(int arabic) pure @safe
    {
      return pipe!(digits_of, to_roman, join_symbols)(arabic);
    }
	 
    private static immutable(string[]) ones =
      ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"];
    private static immutable(string[]) tens =
      ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"];
    private static immutable(string[]) hundreds =
      ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"];
    private static immutable(string[]) thousands =
      ["", "M", "MM", "MMM"];
    private static immutable(string[][]) symbolTable =
      [thousands, hundreds, tens, ones];

  }
}

unittest
{
  alias ArabicRoman = ArabicToRoman.Imperativ;
  
  describe("calling convert with 0")
    .should("return an empty string",
  	    (ArabicRoman.convert(0)).must.equal(""));

  describe("calling convert with 0")
    .should("return an empty string",
	    (ArabicRoman.convert(0)).must.equal(""));

  describe("calling convert with 3")
    .should("return III",
  	    (ArabicRoman.convert(3)).must.equal("III"));

  describe("calling convert with 5")
    .should("return V",
  	    (ArabicRoman.convert(5)).must.equal("V"));

  describe("calling convert with 8")
    .should("return VIII",
  	    (ArabicRoman.convert(8)).must.equal("VIII"));

  describe("calling convert with 10")
    .should("return X",
  	    (ArabicRoman.convert(10)).must.equal("X"));

  describe("calling convert with 30")
    .should("return XXX",
  	    (ArabicRoman.convert(30)).must.equal("XXX"));

  describe("calling convert with 15")
    .should("return XV",
  	    (ArabicRoman.convert(15)).must.equal("XV"));

  describe("calling convert with 18")
    .should("return XVIII",
  	    (ArabicRoman.convert(18)).must.equal("XVIII"));

  describe("calling convert with 4")
    .should("return IV",
  	    (ArabicRoman.convert(4)).must.equal("IV"));

  describe("calling convert with 9")
    .should("return IX",
  	    (ArabicRoman.convert(9)).must.equal("IX"));

  describe("calling convert with 1754")
    .should("return MDCCLIV",
  	    (ArabicRoman.convert(1754)).must.equal("MDCCLIV"));

  describe("calling convert with 3888")
    .should("return MMDCCCLXXXVIII empty string",
  	    (ArabicRoman.convert(3888)).must.equal("MMMDCCCLXXXVIII"));
}

unittest
{
  alias ArabicRoman = ArabicToRoman.Functional;
  
  describe("digits_of")
    .should([
	     "return [0, 0, 0, 0] on 0":
	     {
	       (ArabicRoman.digits_of(0)).must.equal([0, 0, 0, 0]);
	     },
	     "return [1, 2, 3, 4] on 1234":
	     {
	       (ArabicRoman.digits_of(1234)).must.equal([1, 2, 3, 4]);
	     },
	     "return [4, 3, 2, 1] on 4321":
	     {
	       (ArabicRoman.digits_of(4321)).must.equal([4, 3, 2, 1]);
	     }
	     ]);
  
  describe("to_roman")
    .should([
	     "return ["", "", "", ""] on [0, 0, 0, 0]":
	     {
	       (ArabicRoman.to_roman([0, 0, 0, 0])).must.equal(["", "", "", ""]);
	     },
	     "return [M, C, X, I] on [1, 1, 1, 1]":
	     {
	       (ArabicRoman.to_roman([1, 1, 1, 1])).must.equal(["M", "C", "X", "I"]);
	     },
	     "return [MMM, CCC, XXX, III] on [3, 3, 3, 3]":
	     {
	       (ArabicRoman.to_roman([3, 3, 3, 3])).must.equal(["MMM", "CCC", "XXX", "III"]);
	     },
	     "return [, CD, XL, IV] on [0, 4, 4, 4]":
	     {
	       (ArabicRoman.to_roman([0, 4, 4, 4])).must.equal(["", "CD", "XL", "IV"]);
	     },
	     "return [, CM, XC, IX] on [0, 9, 9, 9]":
	     {
	       (ArabicRoman.to_roman([0, 9, 9, 9])).must.equal(["", "CM", "XC", "IX"]);
	     }
	     ]);

  describe("join_symbols")
    .should([
	     "return empty string on [ , , , ]":
	     {
	       (ArabicRoman.join_symbols(["", "", "", ""])).must.equal("");
	     },
	     "return MCXI on [M, C, X, I]":
	     {
	       (ArabicRoman.join_symbols(["M", "C", "X", "I"])).must.equal("MCXI");
	     },
	     "return MMMCCCXXXIII on [MMM, CCC, XXX, III]":
	     {
	       (ArabicRoman.join_symbols(["MMM", "CCC", "XXX", "III"])).must.equal("MMMCCCXXXIII");
	     }
             ]);

  describe("convert")
    .should([
	     "return empty string on 0":
	     {
	       (ArabicRoman.convert(0)).must.equal("");
	     },
	     "return MCMLXI on 1961":
	     {
	       (ArabicRoman.convert(1961)).must.equal("MCMLXI");
	     },
	     "return MMMDCCCLXXXVIII on [MMM, DCCC, LXXX, VIII]":
	     {
	       (ArabicRoman.convert(3888)).must.equal("MMMDCCCLXXXVIII");
	     }
             ]);
}
