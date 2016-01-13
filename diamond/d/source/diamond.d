module xzr.diamond;

import std.ascii               : uppercase;
import std.array               : replicate;
import std.algorithm.iteration : map;
import std.range               : iota, retro;

struct Diamond
{
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
}
