package string_calculator

import (
	"strconv"
	"strings"
	"errors"
	"container/list"
)

func extractSeparator(numbers string) (sep string, nums string) {
	if numbers[0] == '/' {
		sepSpecEndIdx := strings.Index(numbers, "\n")
		return numbers[2:sepSpecEndIdx], numbers[sepSpecEndIdx+1:]
	}
	return ",", strings.Replace(numbers, "\n", ",", -1)
}

func Add(numbers string) (sum int, err error) {
	if len(numbers) == 0 {
		return 0, nil
	}
	sep, nums := extractSeparator(numbers);
	splitted := strings.Split(nums, sep)
	negs := list.New()
	for _, n := range splitted {
		num, e := strconv.Atoi(n)
		if e != nil {
			return -1, e
		}
		if num < 0 {
			negs.PushBack(num)
		}
		sum += num
	}
	if negs.Len() != 0 {
		errorMsg := "negative numbers not allowed:"
		for it := negs.Front(); it != nil; it = it.Next() {
			errorMsg = errorMsg + " " + strconv.Itoa(it.Value.(int))
		}
		return -1, errors.New(errorMsg)
	} else {
		return sum, nil
	}
}
