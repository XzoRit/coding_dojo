defmodule StringCalculator do
	def add (numsAsString) do
		case String.length(numsAsString) do
			0 ->	0
			_ -> if String.starts_with?(numsAsString, "//") do
						 String.split(String.slice(numsAsString, 4 .. String.length(numsAsString) - 1), String.at(numsAsString, 2))
						 |> Enum.map(&(String.to_integer/1))
						 |> Enum.reduce(&(+/2))
					 else
						 String.replace(numsAsString, "\n", ",")
						 |> String.split(",")
						 |> Enum.map(&(String.to_integer/1))
						 |> Enum.reduce(&(+/2))
					 end
		end
	end
end
