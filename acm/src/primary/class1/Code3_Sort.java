/**
 * Created by June on ${date} ...
 */
package primary.class1;
/**
 *
 排序算法	时间复杂度	空间复杂度	稳定性	特点
 选择排序	O(n²)	O(1)	不稳定	每次选择最小值
 冒泡排序	O(n²)	O(1)	稳定	相邻元素比较交换
 插入排序	O(n²)	O(1)	稳定	将元素插入已排序部分
 */

public class Code3_Sort {

    public static void swap(int[] arr, int i, int j) {
        int t = arr[j];
        arr[j] = arr[i];
        arr[i] = t;
    }

    public static void selectSort(int[] arr) {
        if (arr == null || arr.length < 2) return;
        int n = arr.length;
        for (int i = 0; i < n; ++i) {//确定未排序部分的起始位置
            int idx = i;
            for (int j = i + 1; j < n; ++j) {//在未排序部分找到最小元素的索引
                idx = arr[j] < arr[idx] ? j : idx;
            }
            swap(arr, i, idx);//将最小元素与当前位置交换
        }
    }

    public static void bubbleSort(int[] arr) {
        if (arr == null || arr.length < 2) return;
        int n = arr.length;
        for (int ed = n - 1; ed >= 0; --ed) {//确定未排序部分的结束位置
            for (int i = 1; i <= ed; ++i) {//相邻元素比较，将最大元素"冒泡"到末尾
                if (arr[i-1] > arr[i])
                    swap(arr, i-1, i);
            }
        }
    }

    public static void insertSort1(int[] arr) {
        if (arr == null || arr.length < 2) return;
        int n = arr.length;
        for (int ed = 1; ed < n; ++ed) {
            int j = ed;//从当前位置向前比较并交换，直到找到合适位置
            while (j-1 >= 0 && arr[j-1] > arr[j]) {
                swap(arr, j-1, j);
                j--;
            }
        }
    }

    public static void insertSort2(int[] arr) {
        if (arr == null || arr.length < 2) return;
        int n = arr.length;
        for (int ed = 1; ed < n; ++ed) {//使用for循环实现
            for (int pre = ed-1; pre >= 0 && arr[pre] > arr[pre+1]; --pre)
                swap(arr, pre, pre+1);
        }
    }

    public static void printArray(int[] arr) {
        for (int j : arr) System.out.print(j + ' ');
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = {7, 1, 3, 5, 1, 6, 8, 1, 3, 5, 7, 5, 6};

    }
}
