defmodule StringCalculator do
	def add("") do
		0
	end

	def add(numsAsString) do
			splitBySeparator(numsAsString)
			|> Enum.map(&(String.to_integer/1))
			|> Enum.partition(&(&1 < 0))
			|> sumPositives
	end

	defp sumPositives({[], pos}) do
		Enum.reduce(pos, &(+/2))
	end

	defp sumPositives({negs, _}) do
		negsAsString = Enum.map(negs, &(to_string/1)) |> Enum.reduce(&(&2 <> " " <> &1))
		raise(ArgumentError, message: "negative numbers ( " <> negsAsString <> " ) not allowed")
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
