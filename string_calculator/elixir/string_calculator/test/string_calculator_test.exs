defmodule StringCalculatorTest do
  use ExUnit.Case

  test "empty string returns 0" do
    assert StringCalculator.add("") == 0
  end
end
