package string_calculator

import (
	"testing"
	"strconv"
)

func TestAddWithEmptyStringReturns0(t *testing.T) {
	expected := 0
	actual, _ := Add("")
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d", expected, actual)
	}
}

func TestAddWithANumberShouldReturnThatNumber(t *testing.T) {
	expected := 1234567890
	actual, _ := Add(strconv.Itoa(expected))
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d", expected, actual)
	}
}

func TestAddWithCommaSeparatedNumberShouldReturnTheSum(t *testing.T) {
	expected := 356
	actual, _ := Add("1,22,333")
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d", expected, actual)
	}
}
