module xzr.diamond;

import std.ascii               : uppercase;
import std.array               : array, replicate;
import std.algorithm.iteration : map;
import std.range               : iota;

struct Diamond
{
  static auto letters(char including)
  {
    return uppercase[0..(including - 'A' + 1)];
  }

  static auto spaces_after(int num)
  {
    return iota(0, num+1)
      .map!(a => replicate(" ", a))
      .array;
  }
}

unittest
{
  import specd.specd;

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
	     { Diamond.spaces_after(0).must.equal([""]); },
	     """return ["", " "] if given 1""":
	     { Diamond.spaces_after(1).must.equal(["", " "]); },
	     """return ["", " ", "  "] if given 2""":
	     { Diamond.spaces_after(2).must.equal(["", " ", "  "]); }
	     ]);
}
