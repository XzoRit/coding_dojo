writeln("String-Calculator")

StringCalculator := Object clone do(
    extractSeparation := method(textWithSeps,
        if(textWithSeps beginsWithSeq("/"),
            textWithSeps exSlice(2, 3),
            "," .. "\n"
        )
    )
    
    add := method(numbers,
        if(numbers isEmpty,
            0,
            numbers split(",", "\n") map(asNumber) sum
            // negs := ints select(i, i < 0)
            // if(negs size == 0,
            //     ints sum,
            //     Exception raise ("negative numbers not allowed: " .. negs)
            // )
        )
    )
)

StringCalculatorTest := UnitTest clone do(
    setUp := method(
        super(setUp)
        self calculator := StringCalculator clone
    )

    testEmptyStringReturns0 := method(
        assertEquals(calculator add(""), 0)
    )

    testStringWithOneNumberReturnsThatNumber := method(
        assertEquals(calculator add("1234567890"), 1234567890)
    )

    testStringWithCommaSeperatedNumbersReturnsSum := method(
        assertEquals(calculator add("1,22,333"), 356)
    )

    testStringWithCommaOrNewlineAsSeperators := method(
        assertEquals(calculator add("1,22\n333"), 356)
    )

    testExtractSeparatorWithoutCustomSpec := method(
        assertEquals(calculator extractSeparation("1,22,333"), ",\n")
    )

    testExtractSeparatorWithCustomSpec := method(
        assertEquals(calculator extractSeparation("//-\n"), "-")
    )
)

test := clone StringCalculatorTest
test run()

/*
stringCalculator extractSeparation("1,22,333")
stringCalculator extractSeparation("//-\n")

stringCalculator add("1,22,333") println
stringCalculator add("1\n22\n333") println
stringCalculator add("1\n22,333") println

e := try(stringCalculator add("1,-22,-333"))
e catch(Exception, e error println)

stringCalculator add("//-\n1-22-333") println
*/
