defmodule StringCalculatorTest do
  use ExUnit.Case

  test "empty string returns 0" do
    assert StringCalculator.add("") == 0
  end

	test "string with one number returns that number" do
		assert StringCalculator.add("1234567890") == 1234567890
	end
end
