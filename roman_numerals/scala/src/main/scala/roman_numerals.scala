package xzr.coding_dojo.roman_numerals

package imperativ {

  class ArabicToRoman {

    def convert(arabic: Int) = {
      var roman = ""
      var count = arabic
      symbolTable foreach { arabicRomanPair =>
	while(count >= arabicRomanPair._1) {
	  roman += arabicRomanPair._2
	  count -= arabicRomanPair._1
	}
      }
      roman
    }

    private val symbolTable = Vector(
      (1000 -> "M"),
      (900 -> "CM"),
      (500 -> "D"),
      (400 -> "CD"),
      (100 -> "C"),
      (90 -> "XC"),
      (50 -> "L"),
      (40 -> "XL"),
      (10 -> "X"),
      (9 -> "IX"),
      (5 -> "V"),
      (4 -> "IV"),
      (1 -> "I"))
  }

}

package functional {

  class ArabicToRoman {

    def digitsOf(num: Int) = {
      num.toString map{_.asDigit} padTo(4, 0)
    }

    def toRomanSymbols(digits: Traversable[Int]) = {
      (digits, symbolTable).zipped map{(digit, symbols) => symbols(digit)}
    }

    def concatSymbols(symbols: Traversable[String]) = {
      symbols.foldLeft(""){_ ++ _}
    }

    def convert(arabic: Int) = {
      concatSymbols(toRomanSymbols(digitsOf(arabic)))
    }
  
    private val ones = Vector("", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX")
    private val tens = Vector("", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC")
    private val hundreds = Vector("", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM")
    private val thousands = Vector("", "M", "MM", "MMM")
    private val symbolTable = Vector(thousands, hundreds, tens, ones)

  }

}
