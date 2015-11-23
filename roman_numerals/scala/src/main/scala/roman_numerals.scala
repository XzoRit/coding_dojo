package xzr.coding_dojo.roman_numerals

class ArabicToRoman {

  def convert(arabic: Int) = {
    var roman = ""
    var count = arabic
    if(arabic >= 5) {
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
