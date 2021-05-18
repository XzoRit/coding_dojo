arabics = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
romans = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]


def to_arabic(roman):
    arabic = 0
    while len(roman) != 0:
        for i in range(len(romans)):
            if roman.startswith(romans[i]):
                arabic += arabics[i]
                roman = roman[len(romans[i]):]
    return arabic


def to_roman(arabic):
    roman = ""
    while arabic > 0:
        for i in range(len(arabics)):
            while arabic >= arabics[i]:
                roman += romans[i]
                arabic -= arabics[i]
    return roman


def test_to_arabic():
    assert(to_arabic("I") == 1)
    assert(to_arabic("II") == 2)
    assert(to_arabic("III") == 3)
    assert(to_arabic("V") == 5)
    assert(to_arabic("VIII") == 8)
    assert(to_arabic("IV") == 4)
    assert(to_arabic("XXX") == 30)
    assert(to_arabic("IX") == 9)
    assert(to_arabic("XXVIII") == 28)
    assert(to_arabic("MDCL") == 1650)


def test_to_roman():
    assert(to_roman(1) == "I")
    assert(to_roman(2) == "II")
    assert(to_roman(3) == "III")
    assert(to_roman(5) == "V")
    assert(to_roman(8) == "VIII")
    assert(to_roman(4) == "IV")
    assert(to_roman(30) == "XXX")
    assert(to_roman(9) == "IX")
    assert(to_roman(28) == "XXVIII")
    assert(to_roman(1650) == "MDCL")
