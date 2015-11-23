package xzr.coding_dojo.roman_numerals

class ArabicToRoman {

  def convert(arabic: Int) = {
    var roman = ""
    var count = arabic
    while(count >= 10) {
      roman += "X"
      count -= 10
    }
    if(count >= 5) {
      roman += "V"
      count -= 5
    }
    while(count > 0)  {
      roman += "I"
      count -= 1
    }

    roman
  }

}
