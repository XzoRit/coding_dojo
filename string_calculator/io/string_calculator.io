writeln("String-Calculator")

StringCalculator := Object clone
StringCalculator extractSeparation := method(textWithSeps,
		 if(textWithSeps at(0) != "/", "," .. "\n", textWithSeps at(2)))

StringCalculator add := method(numbers,
		 ints := numbers split(self extractSeparation(numbers)) map(asNumber)
		 negs := ints select(i, i < 0)
		 if(negs size == 0,
		    ints sum,
		    Exception raise ("negative numbers not allowed: " .. negs)))

stringCalculator := StringCalculator clone

"//-\n" at(0) println

stringCalculator extractSeparation("1,22,333") println
stringCalculator extractSeparation("//-\n") println


stringCalculator add("1,22,333") println
stringCalculator add("1\n22\n333") println
stringCalculator add("1\n22,333") println

e := try(stringCalculator add("1,-22,-333"))
e catch(Exception, e error println)

stringCalculator add("//-\n1-22-333") println


