import std.array;
import std.conv;
import std.string;
import std.algorithm;

int add(string numbers)
{
  if(numbers.empty) return 0;
  auto separator = [','];
  if(numbers[0] == '/')
    {
      separator[0] = numbers[2];
      numbers = numbers[4..$];
    }
  immutable replaced = replace(numbers, "\n", separator);
  auto splitted = split(replaced, separator);
  auto ints = map!(a => to!int(a))(splitted);
  return reduce!((a, b) => a + b)(0, ints);
}

import specd.specd;

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
}
