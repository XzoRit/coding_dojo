package string_calculator

import (
	"testing"
	"strconv"
)

func TestAddWithEmptyStringReturns0(t *testing.T) {
	expected := 0
	actual, err := Add("")
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestAddWithANumberShouldReturnThatNumber(t *testing.T) {
	expected := 1234567890
	actual, err := Add(strconv.Itoa(expected))
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestAddWithCommaSeparatedNumberShouldReturnTheSum(t *testing.T) {
	expected := 356
	actual, err := Add("1,22,333")
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestNumbersCanBeSparatedByCommaOrNewLine(t *testing.T) {
	expected := 356
	actual, err := Add("0\n1,22\n333")
	if actual !=  expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestSeparatorSpecificationContainsSeparatorCharacter(t * testing.T) {
	expected := 356
	actual, err := Add("//;\n0;1;22;333")
	if actual != expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestSeparatorSpecificationContainsSeparatorString(t * testing.T) {
	expected := 356
	actual, err := Add("//+*+\n0+*+1+*+22+*+333")
	if actual != expected {
		t.Errorf("Expected: %d Actual %d with err = %s", expected, actual, err)
	}
}

func TestNegativeNumbersShouldResultInAnErrorBeingReturned(t *testing.T) {
	_, err := Add("0,-1,22,-333")
	if err == nil {
		t.Error("negativ numbers should be an error")
	}
}
