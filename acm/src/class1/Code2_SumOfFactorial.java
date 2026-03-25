/**
 * Created by June on ${fmdate} ...
 */
package class1;

public class Code2_SumOfFactorial {
/*
方法 f1：
朴素方法：对每个 $i$（从1到N）单独计算 $i!$
时间复杂度：O(N²)，因为每个factorial调用需要O(i)时间
空间复杂度：O(1)
方法 f2：
优化方法：利用前一个阶乘计算下一个阶乘（$i! = (i-1)! \times i$）
时间复杂度：O(N)，只需一次遍历
空间复杂度：O(1)
关键区别：
f1 重复计算了很多阶乘（计算3!时重新计算了1!×2!×3!）
f2 重用了之前的计算结果（$3! = 2! \times 3$）
*/
    public static long f1(int N) {
        long ans = 0;
        for (int i = 1; i <= N; ++i) {
            ans += factorial(i);
        }
        return ans;
    }

    public static long factorial(int N) {
        long ans = 1;
        for (int i = 1; i <= N; ++i) {
            //N! = 1 * 2 * 3 * ... * N
            ans *= i;
        }
        return ans;
    }

    public static long f2(int N) {
        //ans存储总和，cur存储当前阶乘值
        long ans = 0, cur = 1;
        for (int i = 1; i <= N; ++i) {
            cur *= i;//计算i!，利用前面的(i-1)!来计算
            ans += cur;//将当前阶乘加到总和中
        }
        return ans;
    }
    public static void main(String[] args) {
        int N = 10;
        System.out.println(f1(N));
        System.out.println(f2(N));
    }
}
