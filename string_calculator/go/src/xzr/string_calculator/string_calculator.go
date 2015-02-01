package string_calculator

import (
	"strconv"
	"strings"
)

func Add(numbers string) (sum int, err error) {
	splitted := strings.Split(numbers, ",")
	for _, n := range splitted {
		num, e := strconv.Atoi(n)
		if e != nil {
			return
		}
		sum += num
	}
	return sum, nil
}
