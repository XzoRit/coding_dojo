import specd.specd;
import std.array;
import std.conv;
import std.string;
import std.algorithm;
import std.typecons;
import std.regex;

auto splitBySeparator(string numbers)
{
  alias SepAndNums = Tuple!(string, "sep", string, "nums");
  SepAndNums sepAndNums;
  if(numbers[0] == '/')
    {
      immutable i = numbers.indexOf("\n");
      sepAndNums.sep = numbers[2..i];
      sepAndNums.nums = numbers[(i+1)..$];
    }
  else
    {
      sepAndNums.sep = ",";
      sepAndNums.nums = replace(numbers, "\n", sepAndNums.sep);
    }
  return split(sepAndNums.nums, sepAndNums.sep);
}

auto add(string numbers)
{
  if(numbers.empty) return 0;
  auto ints = array(splitBySeparator(numbers).map!(a => to!int(a)));
  auto negs = partition!("a>=0")(ints);
  if(negs.empty) return reduce!"a+b"(0, ints);
  else throw new Exception(reduce!((txt, i) => txt ~ " " ~ to!string(i))("negative numbers not allowed:", negs));
}

unittest
{
  describe("calling add with an empty string")
    .should("return 0",
	    (add("")).must.equal(0));
  describe("calling add with a number")
    .should("return that number",
	    (add("1234567890")).must.equal(1234567890));
  describe("calling add with a comma separated list of numbers")
    .should("return the sum of these numbers",
	    (add("1,22,333")).must.equal(356));
  describe("calling add with many numbers separated by comma or newline")
    .should("return the sum of these numbers",
	    (add("1\n22,333")).must.equal(356));
  describe("calling add with numbers separated by a character contained in the separator specification section")
    .should("return the sum of these numbers",
	    (add("//T\n1T22T333")).must.equal(356));
  describe("calling add with numbers separated by a string contained in the separator specification section")
    .should("return the sum of these numbers",
  	    (add("//*-*\n1*-*22*-*333")).must.equal(356));
  add("//*-*\n1*-*-22*-*-333").must.throw_!Exception;
  try
    {
      add("0,-1,22,-333");
    }
  catch(Exception e)
    {
      (e.msg).must.equal("negative numbers not allowed: -1 -333");
    }
}
