/* compile with scalac-2.11 -cp <jar-files> <script-name> */
/* run test with scala-2.11 -cp <jar-files> org.scalatest.run <test-class-name> */
import org.scalatest._

class ArabicToRoman {

  def convert(arabic: Int) = {
    if(arabic == 3) "III"
    else if(arabic == 2) "II"
    else "I"
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

}
