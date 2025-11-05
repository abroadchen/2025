//
// Created by Psy.C on 2025/11/5.
//
/*
*n: 点的数量
i: 循环计数器
x, y: 每个点的坐标
sumx: 所有点x坐标的和
sumy: 所有点y坐标的和
sumxx: 所有点x坐标平方的和
sumyy: 所有点y坐标平方的和
sum: 最终结果
 *
 *计算的是所有点对之间距离平方和的一半
 *
*时间复杂度：O(n)
空间复杂度：O(1)
 *
 */
#include <cstdio>
using namespace std;

typedef unsigned long long ull;
int n, i, x, y;
ull sumx, sumy, sumxx, sumyy, sum;

int main() {
    while (scanf("%d", &n) != EOF) {
        sum = sumx = sumy = sumxx = sumyy = 0;
        for (i = 1; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            sumx += x;
            sumy += y;
            sumxx += x * x;
            sumyy += y * y;
        }
        sum = n * (sumxx + sumyy) - sumx * sumx - sumy * sumy;
        printf("%llu\n", sum);
    }
    return 0;
}