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

func toInts(numsAsStr []string) ([]int, error) {
	ints := make([]int, len(numsAsStr))
	for idx, n := range numsAsStr {
		num, e := strconv.Atoi(n)
		if e != nil {
			return ints, e
		}
		ints[idx] = num
	}
	return ints, nil
}

func Add(numbers string) (sum int, err error) {
	if len(numbers) == 0 {
		return 0, nil
	}
	sep, nums := extractSeparator(numbers);
	splitted := strings.Split(nums, sep)
	ints, e := toInts(splitted)
	if e != nil {
		return -1, e
	}
	negs := list.New()
	for _, num := range ints {
		if num < 0 {
			negs.PushBack(num)
		}
		sum += num
	}
	if negs.Len() != 0 {
		errorMsg := "negative numbers not allowed:"
		for it := negs.Front(); it != nil; it = it.Next() {
			errorMsg += " " + strconv.Itoa(it.Value.(int))
		}
		return -1, errors.New(errorMsg)
	} else {
		return sum, nil
	}
}
