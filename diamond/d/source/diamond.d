module xzr.diamond;

struct Diamond
{
  static auto letters(char including)
  {
    import std.ascii : uppercase;
    return uppercase[0..(including - 'A' + 1)];
  }
}

unittest
{
  import specd.specd;

  describe("letters")
    .should(["return A on A":
	     { Diamond.letters('A').must.equal("A"); },
	     "return AB on B":
	     { Diamond.letters('B').must.equal("AB"); },
	     "return ABC on C":
	     { Diamond.letters('C').must.equal("ABC"); }
	     ]);
}
