/**
 * Created by June on ${fmdate} ...
 */
package class1;

import static class1.Code3_Sort.swap;

public class Code4_SelectionSort {

    public static void selectionSort(int[] arr) {
        if (arr == null || arr.length < 2) return;
        //每轮确定位置 i 的最终元素
        //< arr.length-1：最后一个元素自动就位，无需比较
        for (int i = 0; i < arr.length-1; ++i) {
            int idx = i;//假设当前位置元素最小
            for (int j = i+1; j < arr.length; ++j) {
                //idx 指向未排序部分的最小元素
                if (arr[j] < arr[idx]) idx = j;//更新最小值索引
            }
            swap(arr, i, idx);//确保位置 i 的元素是未排序部分的最小值
        }
    }
    public static void main(String[] args) {

    }
}
