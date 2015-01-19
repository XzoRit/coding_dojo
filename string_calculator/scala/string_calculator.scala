/* compile with scalac-2.11 -cp <jar-files> <script-name> */
/* run test with scala-2.11 -cp <jar-files> org.scalatest.rung <test-class-name> */
import org.scalatest._

// println("1,22,333".split(",").map(_.toInt).foldLeft(0)(_+_))
// println("1,22,333".split(",").map{_.toInt}.foldLeft(0){_+_})
// println("1,22,333".split(",").foldLeft(0)(_+_.toInt))

class StringCalculator {

  def add(numbers: String) = {
    if(numbers.isEmpty()) 0 else numbers.toInt
  }
}

class TestStringCalculator extends FlatSpec with Matchers with BeforeAndAfter {

  val calculator = new StringCalculator

  "add with empty string" should "return 0" in {
    calculator.add("") should be (0)
  }

  "add with a number" should "return that number" in {
    calculator.add("1234567890") should be (1234567890)
  }
}
