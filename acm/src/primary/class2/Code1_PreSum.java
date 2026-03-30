package primary.class2;

/**
 * Created by June on 2026/3/30 ...
 */
public class Code1_PreSum {

    public static class RangeSum1 {
        private int[] arr;
        public RangeSum1(int[] array) {
            arr = array;
        }
        public int rangeSum(int L, int R) {
            int sum = 0;
            for (int i = L; i <= R; ++i)
                sum += arr[i];
            return sum;
        }
    }

    public static class RangeSum2 {
        private int[] preSum;
        public RangeSum2(int[] array) {
            int n = array.length;
            preSum = new int[n];
            preSum[0] = array[0];
            for (int i = 1; i < n; ++i)
                preSum[i] = preSum[i-1] + array[i];
        }
        public int rangeSum(int L, int R) {
            return L == 0 ? preSum[R] : preSum[R] - preSum[L-1];
        }
    }


    public static void main(String[] args) {

    }
}
