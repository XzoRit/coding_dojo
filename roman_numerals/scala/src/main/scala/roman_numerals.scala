package xzr.coding_dojo.roman_numerals

class ArabicToRoman {

  def convert(arabic: Int) = {
    var roman = ""
    var count = arabic
    while(count >= symbolTable(2)._1) {
      roman += symbolTable(2)._2
      count -= symbolTable(2)._1
    }
    if(count >= symbolTable(1)._1) {
      roman += symbolTable(1)._2
      count -= symbolTable(1)._1
    }
    while(count >= symbolTable(0)._1)  {
      roman += symbolTable(0)._2
      count -= symbolTable(0)._1
    }

    roman
  }

  val symbolTable = List((1 -> "I"), (5 -> "V"), (10 -> "X"))
}
