module xzr.diamond;

struct Diamond
{
  import std.ascii               : uppercase;
  import std.array               : replicate;
  import std.algorithm.iteration : map, reduce;
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

  static auto mirror_vertical(Range)(Range lines)
  {
    return
      zip(lines,
	  lines.map!(a => retro(a).drop(1)))
      .map!(a => a[0] ~ to!string(a[1]));
  }

  static auto mirror_horizontal(Range)(Range lines)
  {
    import std.array : array;
    auto lines_as_array = array(lines);
    foreach(line; retro(lines).drop(1)) lines_as_array ~= line;
    return lines_as_array;
  }

  static auto all_lines(int amount)
  {
    return mirror_horizontal(mirror_vertical(lines(amount)));
  }

  static auto print(char c)
  {
    immutable amount = c - 'A' + 1;
    return reduce!((a, b) => a ~ b ~ '\n')("", all_lines(amount));
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
	     { Diamond.mirror_vertical([" A", "B "]).array.must.equal([" A ", "B B"]); },
	     "return [  A  ,  B B , C   C] if given [  A,  B , C  ]":
	     { Diamond.mirror_vertical(["  A", " B ", "C  "]).array.must.equal(["  A  ", " B B ", "C   C"]); }
	     ]);

  describe("mirror_horizontal")
    .should(["return [A] if given [A]":
	     { Diamond.mirror_horizontal(["A"]).array.must.equal(["A"]); },
	     "return [ A, B, A] if given [ A, B ]":
	     { Diamond.mirror_horizontal([" A", "B "]).array.must.equal([" A", "B ", " A"]); },
	     "return [  A,  B , C  ,  B ,   A] if given [  A,  B , C  ]":
	     { Diamond.mirror_horizontal(["  A", " B ", "C  "]).array.must.equal(["  A", " B ", "C  ", " B ", "  A"]); }
	     ]);

  describe("all_lines")
    .should(["return [A] if given 1":
	     { Diamond.all_lines(1).must.equal(["A"]); },
	     "return [ A ,  B ,  A ] if given 2":
	     { Diamond.all_lines(2).must.equal([" A ",
						"B B",
						" A "]); },
	     "return [  A  ,  B B , C   C ,  B B ,   A  ] if given 3":
	     { Diamond.all_lines(3).must.equal(["  A  ",
						" B B ",
						"C   C",
						" B B ",
						"  A  "]); }
	     ]);

  describe("print")
    .should(["return A-Diamond if given 'A'":
	     { Diamond.print('A').must.equal("A\n"); },
	     "return B-Diamond if given 'B'":
	     { Diamond.print('B').must.equal(" A \n"
					     "B B\n"
					     " A \n"); },
	     "return C-Diamond if given 'C'":
	     { Diamond.print('C').must.equal("  A  \n"
					     " B B \n"
					     "C   C\n"
					     " B B \n"
					     "  A  \n"); }
	     ]);

  import std.stdio : writeln;
  import std.ascii : uppercase;
  foreach(c; uppercase) writeln(Diamond.print(c));
}
