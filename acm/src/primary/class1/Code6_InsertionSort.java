package primary.class1;

import static primary.class1.Code3_Sort.swap;

/**
 * Created by June on 2026/3/27 ...
 */
public class Code6_InsertionSort {

    public static void insertionSort(int[] arr) {
        if (arr == null || arr.length < 2) return;
        for (int i = 1; i < arr.length; ++i)
            for (int j = i - 1; j >= 0 && arr[j] > arr[j+1]; --j)
                swap(arr, j, j+1);
    }

    public static void main(String[] args) {

    }
}
