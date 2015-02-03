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

func partition(nums []int) (*list.List, *list.List) {
	negs := list.New()
	pos := list.New()
	for _, n := range nums {
		if n < 0 {
			negs.PushBack(n)
		} else {
			pos.PushBack(n)
		}
	}
	return negs, pos
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
	negs, pos := partition(ints)
	if negs.Len() != 0 {
		errorMsg := "negative numbers not allowed:"
		for it := negs.Front(); it != nil; it = it.Next() {
			errorMsg += " " + strconv.Itoa(it.Value.(int))
		}
		return -1, errors.New(errorMsg)
	} else {
		sum := 0
		for it := pos.Front(); it != nil; it = it.Next() {
			sum += it.Value.(int)
		}
		return sum, nil
	}
}
