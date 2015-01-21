/* compile with scalac-2.11 -cp <jar-files> <script-name> */
/* run test with scala-2.11 -cp <jar-files> org.scalatest.rung <test-class-name> */
import org.scalatest._

// println("1,22,333".split(",").map(_.toInt).foldLeft(0)(_+_))
// println("1,22,333".split(",").map{_.toInt}.foldLeft(0){_+_})
// println("1,22,333".split(",").foldLeft(0)(_+_.toInt))

class StringCalculator {

  def extractNumbers(numbers: String): (String, String) = {
    if(numbers.startsWith("//")) {
      (numbers(2).toString, numbers.drop(4))
    }
    else {
      (""",|\n""", numbers)
    }
  }

  def add(numbers: String) = {
    if(numbers.isEmpty) 0 else {
      val (seperator, nums) = extractNumbers(numbers)
      val (negs, pos) = seperator.r.split(nums).map{_.toInt}.partition{_ < 0}
      if(negs.isEmpty) pos.foldLeft(0){_ + _} else throw new IllegalArgumentException()
    }
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

  "add with comma seperator" should "return sum of numbers" in {
    calculator.add("1,22,333") should be (356)
  }

  "numbers seperated with comma or newline" should "be summed up" in {
    calculator.extractNumbers("1,22\n333") should be (""",|\n""", "1,22\n333")
    calculator.add("1,22\n333") should be (356)
  }

  "if seperator specification is present it" should "be used to sum up numbers" in {
    calculator.extractNumbers("//;\n1;22;333") should be (";", "1;22;333")
    calculator.add("//;\n1;22;333") should be (356)
  }

  "add with negative numbers" should "throw an exception with negative numbers listed" in {
    intercept[IllegalArgumentException] {
      calculator.add("1,-22,-333")
    }
  }

}
