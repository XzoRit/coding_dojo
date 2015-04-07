defmodule StringCalculator do
	def add (numsAsString) do
		case String.length(numsAsString) do
			0 ->	0
			_ -> splitBySeparator(numsAsString)
					 |> Enum.map(&(String.to_integer/1))
					 |> Enum.reduce(&(+/2))
		end
	end

	defp splitBySeparator(numsAsString) do
		{nums, separator} = extractSeparator(numsAsString)
		String.split(nums, separator)
	end

	defp extractSeparator(numsAsString) do
		if String.starts_with?(numsAsString, "//") do
			{String.slice(numsAsString, 4 .. String.length(numsAsString) - 1), String.at(numsAsString, 2)}
		else
			{String.replace(numsAsString, "\n", ","), ","}
		end
	end
end
