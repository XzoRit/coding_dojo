module xzr.diamond;

struct Diamond
{
  import std.ascii               : uppercase;
  import std.array               : replicate;
  import std.algorithm.iteration : map;
  import std.range               : iota, retro, zip, drop;
  import std.conv                : to;

  static auto letters(int amount)
  {
    return uppercase[0..amount];
  }

  static auto spaces_after(int amount)
  {
    return iota(0, amount)
      .map!(a => replicate(" ", a));
  }

  static auto spaces_before(int amount)
  {
    return spaces_after(amount).retro;
  }

  static auto lines(int amount)
  {
    return zip(spaces_before(amount),
	       letters(amount),
	       spaces_after(amount))
      .map!(a => a[0] ~ to!string(a[1]) ~ a[2]);
  }

  static auto mirror_vertical(string[] lines)
  {
    return
      zip(lines,
	  map!(a => retro(a))(lines)
	  .map!(a => drop(a, 1)))
      .map!(a => a[0] ~ to!string(a[1]));
  }
}

unittest
{
  import specd.specd;
  import std.array : array;

  describe("letters")
    .should(["return A if given 1":
	     { Diamond.letters(1).must.equal("A"); },
	     "return AB if given 2":
	     { Diamond.letters(2).must.equal("AB"); },
	     "return ABC if given 3":
	     { Diamond.letters(3).must.equal("ABC"); }
	     ]);

  describe("spaces_after")
    .should(["""return [""] if given 1""":
	     { Diamond.spaces_after(1).array.must.equal([""]); },
	     """return ["", " "] if given 2""":
	     { Diamond.spaces_after(2).array.must.equal(["", " "]); },
	     """return ["", " ", "  "] if given 3""":
	     { Diamond.spaces_after(3).array.must.equal(["", " ", "  "]); }
	     ]);

  describe("spaces_before")
    .should(["""return [""] if given 1""":
	     { Diamond.spaces_before(1).array.must.equal([""]); },
	     """return ["", " "] if given 2""":
	     { Diamond.spaces_before(2).array.must.equal([" ", ""]); },
	     """return ["", " ", "  "] if given 2""":
	     { Diamond.spaces_before(3).array.must.equal(["  ", " ", ""]); }
	     ]);

  describe("lines")
    .should(["return [A] if given 1":
	     { Diamond.lines(1).array.must.equal(["A"]); },
	     "return [ A, B ] if given 2":
	     { Diamond.lines(2).array.must.equal([" A", "B "]); },
	     "return [  A,  B , C  ] if given 3":
	     { Diamond.lines(3).array.must.equal(["  A", " B ", "C  "]); }
	     ]);

  describe("mirror_vertical")
    .should(["return [A] if given [A]":
	     { Diamond.mirror_vertical(["A"]).array.must.equal(["A"]); },
	     "return [ A , B B] if given [ A, B ]":
	     { Diamond.mirror_vertical([" A", "B "]).array.must.equal([" A ", "B B"]); }/*,
	     "return [  A  ,  B B , C   C] if given [  A,  B , C  ]":
	     { Diamond.mirror_vertical(["  A", " B ", "C  "]).array.must.equal(["  A  ", " B B ", "C   C"]); }*/
	     ]);
  }
