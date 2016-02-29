defmodule DiamondTest do
  use ExUnit.Case
	import Diamond
	
  test "letters" do
    assert letters("A") == ["A"]
    assert letters("B") == ["A", "B"]
    assert letters("C") == ["A", "B", "C"]
  end

	test "spaces_after" do
		assert spaces_after(1) == [""]
		assert spaces_after(2) == ["", " "]
		assert spaces_after(3) == ["", " ", "  "]
	end

	test "spaces_before" do
		assert spaces_before(1) == [""]
		assert spaces_before(2) == [" ", ""]
		assert spaces_before(3) == ["  ", " ", ""]
	end

	test "lines" do
		assert lines("A") == ["A"]
    assert lines("B") == [" A", "B "]
    assert lines("C") == ["  A", " B ", "C  "]
	end

	test "mirror_vertical" do
    assert mirror_vertical(lines("A")) == ["A"]
    assert mirror_vertical(lines("B")) == [" A ", "B B"]
    assert mirror_vertical(lines("C")) == ["  A  ", " B B ", "C   C"]
	end

  test "mirror_horizontal" do
    assert mirror_horizontal(lines("A")) == ["A"]
    assert mirror_horizontal(lines("B")) == [" A", "B ", " A"]
    assert mirror_horizontal(lines("C")) == ["  A", " B ", "C  ", " B ", "  A"]
	end

  test "all_lines" do
    assert all_lines("A") == ["A"]
    assert all_lines("B") == [" A ", "B B", " A "]
    assert all_lines("C") == ["  A  ", " B B ", "C   C", " B B ", "  A  "]
	end

  test "print" do
    assert print("A") == "A\n"
    assert print("B") == " A \nB B\n A \n"
    assert print("C") == "  A  \n B B \nC   C\n B B \n  A  \n"
  end
end
