package string_calculator

import (
	"testing"
	"strconv"
)

func TestAddWithEmptyStringReturns0(t *testing.T) {
	actual, _ := Add("")
	expected := 0
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
