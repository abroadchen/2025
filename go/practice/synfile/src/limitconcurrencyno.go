package main

import "fmt"

func QuickSortThread(arr []int, lastarr chan int, level int, threads int) {
	level = level * 2
	if len(arr) == 0 {
		close(lastarr)
		return
	} else if len(arr) == 1 {
		lastarr <- arr[0]
		close(lastarr)
		return
	} else {
		less := make([]int, 0)
		greater := make([]int, 0)
		midder := make([]int, 0)
		left := arr[0]
		midder = append(midder, left)
		for i := 1; i < len(arr); i++ {
			if arr[i] < left {
				less = append(less, arr[i])
			} else if arr[i] > left {
				greater = append(greater, arr[i])
			} else {
				midder = append(midder, arr[i])
			}
		}
		left_ch := make(chan int, len(less))
		right_ch := make(chan int, len(greater))
		if level <= threads {
			go QuickSortThread(less, left_ch, level, threads)
			go QuickSortThread(greater, right_ch, level, threads)
		} else {
			QuickSortThread(less, left_ch, level, threads)
			QuickSortThread(greater, right_ch, level, threads)
		}
		close(lastarr)
		return
	}
}

func main() {
	arr := []int{1, 9, 2, 0, 3, 7, 6, 4, 5, 10}
	lastarr := make(chan int)
	go QuickSortThread(arr, lastarr, 1, 10)
	for v := range lastarr {
		fmt.Println(v)
	}
}
