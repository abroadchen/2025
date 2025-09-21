//
// Created by Psy.C on 2025/9/21.
//
/*
 *
 *A是系数，B是结果，n是指数
 *
 *
 *
 */
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    long A(0), B(0), n(0); scanf("%ld %ld %ld", &A, &B, &n);
    bool ok(1);
    int X(0);// 解变量，初始化为0

    if (A == 0 && B == 0) puts("1");//方程0*x^n = 0，任何x都是解
    else if (A == 0 && B != 0) puts("No solution");//方程0 = B(非0)，无解
    else if (A != 0 && B == 0) puts("0");//方程A*x^n = 0，解为x=0
    else if (B % A != 0) puts("No solution");//B不能被A整除，说明解不是整数
    else if (A * B < 0 && (n % 2 == 0)) puts("No solution");//x^n总是非负的，无法使Ax^n与B同号
    else {
        int sgn = 2 * (A * B > 0) - 1;// 计算符号因子：如果A*B>0(同号)则sgn=1，否则sgn=-1
        int sol = sgn * pow(1.0 * sgn * B / A, 1.0 / n);// 计算理论解：x = sgn * (|B/A|)^(1/n)
        // 先计算B/A的绝对值，然后开n次方根，最后乘以符号

        int lhs(A), lhsP(A), lhsN(A);// 初始化三个变量用于验证解
        for (int i = 0; i < n; ++i) {// 计算A*sol^n, A*(sol+1)^n, A*(sol-1)^n
            lhs *= sol;
            lhsP *= (sol + 1);
            lhsN *= (sol - 1);
        }

        if (lhs == B) printf("%d\n", sol);
        else if (lhsP == B) printf("%d\n", sol + 1);
        else if (lhsN == B) printf("%d\n", sol - 1);
        else puts("No solution");
    }

    return 0;
}