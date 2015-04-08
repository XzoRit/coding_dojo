defmodule StringCalculator do
	def add("") do
		0
	end

	def add(numsAsString) do
		sum(
			splitBySeparator(numsAsString)
			|> Enum.map(&(String.to_integer/1))
			|> Enum.partition(&(&1 < 0)))
	end

	defp sum({[], pos}) do
		Enum.reduce(pos, &(+/2))
	end

	defp sum({negs, _}) do
		nums = Enum.map(negs, &(to_string/1))
		msg = Enum.reduce(nums, "negative numbers (", &(&2 <> " " <> &1)) <> " ) not allowed"
		raise(ArgumentError, message: msg)
	end

	defp splitBySeparator(numsAsString) do
		[separator, nums] = extractSeparator(numsAsString)
		String.split(nums, separator)
	end

	defp extractSeparator("//" <> rest) do
		String.split(rest)
	end

	defp extractSeparator(numsAsString) do
		[",", String.replace(numsAsString, "\n", ",")]
	end
end
