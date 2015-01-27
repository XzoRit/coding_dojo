/* compile with scalac-2.11 -cp <jar-files> <script-name> */
/* run test with scala-2.11 -cp <jar-files> org.scalatest.run <test-class-name> */
import org.scalatest._

class StringCalculator {

  def extractNumbers(numbers: String) = {
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
      if(negs.isEmpty) pos.foldLeft(0){_ + _} else {	
	throw new IllegalArgumentException(negs.map{_.toString}.foldLeft("Negative numbers not allowed: "){_ ++ _ ++ " "})
      }
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
    the [IllegalArgumentException] thrownBy calculator.add("1,-22,-333") should have message ("Negative numbers not allowed: -22 -333 ")
  }

}
