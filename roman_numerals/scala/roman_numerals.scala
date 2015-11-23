/* compile with scalac-2.11 -cp <jar-files> <script-name> */
/* run test with scala-2.11 -cp <jar-files> org.scalatest.run <test-class-name> */
import org.scalatest._

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
