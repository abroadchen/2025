package class1;

import static class1.Code3_Sort.swap;

/**
 * Created by June on ${fmdate} ...
 */
public class Code5_BubbleSort {

    public static void bubbleSort(int[] arr) {
        if (arr == null || arr.length < 2) return;
        for (int ed = arr.length-1; ed > 0; --ed)
            for (int i = 0; i < ed; ++i)
                if (arr[i] > arr[i+1])
                    swap(arr, i, i+1);
    }
}
