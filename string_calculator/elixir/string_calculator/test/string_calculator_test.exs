defmodule StringCalculatorTest do
  use ExUnit.Case
	import StringCalculator

  test "empty string returns 0" do
    assert add("") == 0
  end

	test "string with one number returns that number" do
		assert add("1234567890") == 1234567890
	end

	test "string with comma separated numbers returns the sum" do
		assert add("1,22,333") == 356
	end

	test "numbers can be separeted by comma or newline" do
		assert add("0\n1,22\n333") == 356
	end
end
