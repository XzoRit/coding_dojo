package xzr.coding_dojo.roman_numerals

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

  val symbolTable = List(
    (10 -> "X"),
    (9 -> "IX"),
    (5 -> "V"),
    (4 -> "IV"),
    (1 -> "I"))
}
