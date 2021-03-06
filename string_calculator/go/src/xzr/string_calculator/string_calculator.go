package string_calculator

import (
	"container/list"
	"errors"
	"strconv"
	"strings"
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

func sum(nums *list.List) (sum int) {
	for it := nums.Front(); it != nil; it = it.Next() {
		sum += it.Value.(int)
	}
	return sum
}

func errorMsg(nums *list.List) (errMsg string) {
	errMsg = "negative numbers not allowed:"
	for it := nums.Front(); it != nil; it = it.Next() {
		errMsg += " " + strconv.Itoa(it.Value.(int))
	}
	return errMsg
}

func Add(numbers string) (int, error) {
	if len(numbers) == 0 {
		return 0, nil
	}
	sep, nums := extractSeparator(numbers)
	ints, e := toInts(strings.Split(nums, sep))
	if e != nil {
		return -1, e
	}
	negs, pos := partition(ints)
	if negs.Len() != 0 {
		return -1, errors.New(errorMsg(negs))
	} else {
		return sum(pos), nil
	}
}
