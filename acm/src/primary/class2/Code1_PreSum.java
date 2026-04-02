package primary.class2;

/**
 * Created by June on 2026/3/30 ...
 */
public class Code1_PreSum {

    public static class RangeSum1 {
        private int[] arr;
        public RangeSum1(int[] array) {
            arr = array;//存储原始数组
        }

        /// 时间复杂度：O(R-L+1)，最坏情况下可达O(n)
        /// 空间复杂度：O(1)
        /// 每次查询都直接对索引L到R之间的元素求和
        public int rangeSum(int L, int R) {
            int sum = 0;
            for (int i = L; i <= R; ++i)
                sum += arr[i];
            return sum;
        }
    }

    ///时间复杂度：O(n) 用于预处理
    ///空间复杂度：O(n) 用于前缀和数组
    ///构建前缀和数组
    public static class RangeSum2 {
        private int[] preSum;
        public RangeSum2(int[] array) {
            int n = array.length;
            preSum = new int[n];
            preSum[0] = array[0];
            for (int i = 1; i < n; ++i)
                preSum[i] = preSum[i-1] + array[i];
        }
        ///时间复杂度：O(1) 每次查询
        /// 空间复杂度：O(1)
        /**
         如果 L == 0：区间从开头开始，所以返回 preSum[R]
         否则：返回 preSum[R] - preSum[L-1]
         这样工作是因为 preSum[R] 包含从0到R的总和
         preSum[L-1] 包含从0到L-1的总和
         它们的差值就是从L到R的和
         */
        public int rangeSum(int L, int R) {
            return L == 0 ? preSum[R] : preSum[R] - preSum[L-1];
        }
    }


    public static void main(String[] args) {

    }
}
