writeln("String-Calculator")

StringCalculator := Object clone do(
    extractNumbers := method(numbers,
        if(numbers beginsWithSeq("/"),
            numbers exSlice(4) split(numbers exSlice(2, 3)),
            numbers split(",", "\n")
        )
    )
    
    add := method(numbers,
        if(numbers isEmpty,
            0,
            self extractNumbers(numbers) map(asNumber) sum
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

    testStringWithCustomSeperator := method(
        assertEquals(calculator add("//-\n1-22-333"), 356)
    )

    testExtractNumbersWithCustomSpec := method(
        assertEquals(calculator extractNumbers("//-\n1-22-333"), list("1", "22", "333"))
    )

    testExtractNumbersWithoutCustomSpec := method(
        assertEquals(calculator extractNumbers("1,22,333"), list("1", "22", "333"))
    )
)

test := clone StringCalculatorTest
test run()
