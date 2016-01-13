module xzr.diamond;

struct Diamond
{
  import std.ascii               : uppercase;
  import std.array               : replicate;
  import std.algorithm.iteration : map;
  import std.range               : iota, retro, zip;
  import std.conv                : to;

  static auto letters(char including)
  {
    return uppercase[0..(including - 'A' + 1)];
  }

  static auto spaces_after(int num)
  {
    return iota(0, num+1)
      .map!(a => replicate(" ", a));
  }

  static auto spaces_before(int num)
  {
    return spaces_after(num).retro;
  }

  static auto lines(char including)
  {
    immutable num = including - 'A';
    return zip(spaces_before(num),
	       letters(including),
	       spaces_after(num))
      .map!(a => concat(a.expand));
  }

private:
  static auto concat(string before, dchar letter, string after)
  {
    return before ~ to!string(letter) ~ after;
  }
}

unittest
{
  import specd.specd;
  import std.array : array;

  describe("letters")
    .should(["return A if given A":
	     { Diamond.letters('A').must.equal("A"); },
	     "return AB if given B":
	     { Diamond.letters('B').must.equal("AB"); },
	     "return ABC if given C":
	     { Diamond.letters('C').must.equal("ABC"); }
	     ]);

  describe("spaces_after")
    .should(["""return [""] if given 0""":
	     { Diamond.spaces_after(0).array.must.equal([""]); },
	     """return ["", " "] if given 1""":
	     { Diamond.spaces_after(1).array.must.equal(["", " "]); },
	     """return ["", " ", "  "] if given 2""":
	     { Diamond.spaces_after(2).array.must.equal(["", " ", "  "]); }
	     ]);

  describe("spaces_before")
    .should(["""return [""] if given 0""":
	     { Diamond.spaces_before(0).array.must.equal([""]); },
	     """return ["", " "] if given 1""":
	     { Diamond.spaces_before(1).array.must.equal([" ", ""]); },
	     """return ["", " ", "  "] if given 2""":
	     { Diamond.spaces_before(2).array.must.equal(["  ", " ", ""]); }
	     ]);

  describe("lines")
    .should(["return [A] if given A":
	     { Diamond.lines('A').array.must.equal(["A"]); },
	     """return [ A, B ] if given B""":
	     { Diamond.lines('B').array.must.equal([" A", "B "]); },
	     """return [  A,  B , C  ] if given C""":
	     { Diamond.lines('C').array.must.equal(["  A", " B ", "C  "]); }
	     ]);
}
