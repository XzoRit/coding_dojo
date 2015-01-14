writeln("String-Calculator")

StringCalculator := Object clone do(
    extractNumbers := method(numbers,
        if(numbers beginsWithSeq("//"),
            numbers afterSeq("\n") split(numbers betweenSeq("//", "\n")),
            numbers split(",", "\n")
        )
    )
    
    add := method(numbers,
        if(numbers isEmpty,
            0,
            ints := extractNumbers(numbers) map(asNumber)
            negs := ints select(i, i < 0)
            if(negs isEmpty,
                ints sum,
                Exception raise("Negative numbers not allowed")
            )
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

    testStringWithCommaSeparatedNumbersReturnsSum := method(
        assertEquals(calculator add("1,22,333"), 356)
    )

    testStringWithCommaOrNewlineAsSeparators := method(
        assertEquals(calculator add("1,22\n333"), 356)
    )

    testStringWithCustomSeparator := method(
        assertEquals(calculator add("//-\n1-22-333"), 356)
    )

    testExtractNumbersWithCustomSpec := method(
        assertEquals(calculator extractNumbers("//-\n1-22-333"), list("1", "22", "333"))
    )

    testExtractNumbersWithoutCustomSpec := method(
        assertEquals(calculator extractNumbers("1,22,333"), list("1", "22", "333"))
    )

    testCustomSeparatorCanContainManyChars := method(
        assertEquals(calculator add("//*T*\n1*T*22*T*333"), 356)
    )

    testExtractNumbersWithCustomMultiCharSpec := method(
        assertEquals(calculator extractNumbers("//*T*\n1*T*22*T*333"), list("1", "22", "333"))
    )

    testNegativeNumbersShallRaiseAnException := method(
        assertRaisesException(calculator add("1,-22,333"))
    )
)

test := clone StringCalculatorTest
test run()
