defmodule StringCalculator do
	def add ("") do
		0
	end

	def add (numsAsString) do
		splitBySeparator(numsAsString)
		|> Enum.map(&(String.to_integer/1))
		|> Enum.reduce(&(+/2))
	end

	defp splitBySeparator(numsAsString) do
		{nums, separator} = extractSeparator(numsAsString)
		String.split(nums, separator)
	end

	defp extractSeparator("//" <> rest) do
		[sepSpec, nums] = String.split(rest)
		{nums, sepSpec}
	end

	defp extractSeparator(numsAsString) do
		{String.replace(numsAsString, "\n", ","), ","}
	end
end
