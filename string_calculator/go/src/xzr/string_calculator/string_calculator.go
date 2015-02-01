package string_calculator

import "strconv"

func Add(numbers string) (num int, err error) {
	num, err = strconv.Atoi(numbers)
	if err != nil {
		return
	}
	return num, nil
}
