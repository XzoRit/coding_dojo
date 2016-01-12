defmodule Diamond do
	def letters(char) do
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		|> String.codepoints
		|> Enum.take_while &(&1 <= char)
	end

	def spaces_after(amount) do
		0..amount
		|> Enum.map &(String.duplicate " ", &1)
	end

	def spaces_before(amount) do
		spaces_after(amount)
		|> Enum.reverse
	end

	def lines(char) do
		chars = letters char
		spaces = Enum.count(chars) - 1
		for {front, letter, back} <-
		List.zip(
			[
				spaces_before(spaces),
				chars,
				spaces_after(spaces)
			]),
		do: front <> letter <> back
	end

	def mirror_vertical(lines) do
		reversed = lines
		|> Enum.map(&(String.reverse(&1)))
		|> Enum.map(&(String.slice(&1, 1..-1)))
		
		for {a, b} <- Enum.zip(lines, reversed), do: a <> b
	end

	def mirror_horizontal(lines) do
		lines ++ tl(Enum.reverse(lines))
	end

	def all_lines(char) do
		lines(char)
		|> mirror_vertical
		|> mirror_horizontal
	end

	def print(char) do
		Enum.join(all_lines(char), "\n") <> "\n"
	end
end
