package string_calculator

import (
	"strconv"
	"strings"
)

func Add(numbers string) (sum int, err error) {
	noNewLines := strings.Replace(numbers, "\n", ",", -1)
	splitted := strings.Split(noNewLines, ",")
	for _, n := range splitted {
		num, e := strconv.Atoi(n)
		if e != nil {
			return
		}
		sum += num
	}
	return sum, nil
}
