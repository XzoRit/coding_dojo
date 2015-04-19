defmodule StringCalculator do
	def add("") do
		0
	end

	def add(numsAsString) do
		numsAsString
		|> extractSepAndNums
		|> splitNumsBySep
		|> Enum.map(&(String.to_integer/1))
		|> Enum.partition(&(&1 < 0))
		|> sumPositives
	end

	defp extractSepAndNums("//" <> rest) do
		String.split(rest)
	end

	defp extractSepAndNums(numsAsString) do
		[",", String.replace(numsAsString, "\n", ",")]
	end

	defp splitNumsBySep([sep, nums]) do
		String.split(nums, sep)
	end

	defp sumPositives({[], pos}) do
		Enum.reduce(pos, &(+/2))
	end

	defp sumPositives({negs, _}) do
		errorMsg =
			negs
		  |> Enum.map(&(to_string/1))
			|> Enum.reduce("negative numbers not allowed:", &(&2 <> " " <> &1))
		raise(ArgumentError, message: errorMsg)
	end
end
