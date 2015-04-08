defmodule StringCalculator do
	def add("") do
		0
	end

	def add(numsAsString) do
		{negs, pos} = splitBySeparator(numsAsString)
		|> Enum.map(&(String.to_integer/1))
    |> Enum.partition(&(&1 < 0))
		if Enum.empty?(negs) do
			Enum.reduce(pos, &(+/2))
		else
			raise(ArgumentError, message: "negative numbers not allowed")
		end
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
