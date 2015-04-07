defmodule StringCalculator do
	def add (numsAsString) do
		case String.length(numsAsString) do
			0 ->	0
			_ -> String.split(String.replace(numsAsString, "\n", ","), ",") |> Enum.map(&(String.to_integer/1)) |> Enum.reduce(&(+/2))
		end
	end
end
