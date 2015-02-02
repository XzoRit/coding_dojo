package string_calculator

import (
	"strconv"
	"strings"
)

func extractSeparator(numbers string) (sep string, nums string) {
	if numbers[0] == '/' {
		return numbers[2:3], numbers[4:]
	}
	return ",", strings.Replace(numbers, "\n", ",", -1)
}

func Add(numbers string) (sum int, err error) {
	if len(numbers) == 0 {
		return 0, nil
	}
	sep, nums := extractSeparator(numbers);
	splitted := strings.Split(nums, sep)
	for _, n := range splitted {
		num, e := strconv.Atoi(n)
		if e != nil {
			return -1, e
		}
		sum += num
	}
	return sum, nil
}
