package xzr.coding_dojo.roman_numerals.test

import xzr.coding_dojo.roman_numerals._
import org.scalatest._


class TestArabicToRoman extends FlatSpec with Matchers with BeforeAndAfter {

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

}
