package xzr.coding_dojo.roman_numerals.test

import org.scalatest._

package imperativ {

  import xzr.coding_dojo.roman_numerals.imperativ.ArabicToRoman

  class TestArabicToRoman extends FlatSpec with Matchers {

    val arabicToRoman = new ArabicToRoman

    "given a 1 convert" should "return I" in {
      arabicToRoman.convert(1) should be ("I")
    }

    "given a 2 convert" should "return II" in {
      arabicToRoman.convert(2) should be ("II")
    }

    "given a 3 convert" should "return III" in {
      arabicToRoman.convert(3) should be ("III")
    }

    "given a 5 convert" should "return V" in {
      arabicToRoman.convert(5) should be ("V")
    }

    "given a 8 convert" should "return VIII" in {
      arabicToRoman.convert(8) should be ("VIII")
    }

    "given a 10 convert" should "return X" in {
      arabicToRoman.convert(10) should be ("X")
    }

    "given a 30 convert" should "return XXX" in {
      arabicToRoman.convert(30) should be ("XXX")
    }

    "given a 4 convert" should "return IV" in {
      arabicToRoman.convert(4) should be ("IV")
    }

    "given a 9 convert" should "return IX" in {
      arabicToRoman.convert(9) should be ("IX")
    }

    "given a 1999 convert" should "return MCMXCIX" in {
      arabicToRoman.convert(1999) should be ("MCMXCIX")
    }

  }

}

package functional {

  import xzr.coding_dojo.roman_numerals.functional.ArabicToRoman

  class TestArabicToRoman extends FlatSpec with Matchers {

    val arabicToRoman = new ArabicToRoman

    "digits of 0" should "return (0, 0, 0, 0)" in {
      arabicToRoman.digitsOf(0) should be (Vector(0, 0, 0, 0))
    }

    "digits of 1234" should "return (1, 2, 3, 4)" in {
      arabicToRoman.digitsOf(1234) should be (Vector(1, 2, 3, 4))
    }

  }

}
