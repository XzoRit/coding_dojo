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
	assert(add("") == 0);
	assert(add("1") == 1);
	assert(add("11") == 11);
	assert(add("1,22") == 23);
	assert(add("1,22,333") == 356);
	assert(add("1\n22,333") == 356);
	assert(add("//T\n1T22T333") == 356);
}
