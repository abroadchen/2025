//
// Created by Psy.C on 2025/11/20.
//
/*
*当棋盘只有一行或一列时
骑士不会相互攻击（因为骑士的移动是L形）
所以可以放置n个骑士
 *
*每4行作为一个周期
2 * (n / 4): 完整周期的数量
(n % 4) < 2 ? n % 4 : 2: 余数部分的处理
 *
*如果总格子数是偶数：两种颜色格子数相等，放m×n/2个
如果总格子数是奇数：一种颜色多一个格子，放(m×n+1)/2个
统一公式：(m×n+1)/2，这等价于m*n - (n*m)/2
 *
*时间复杂度：O(1)
空间复杂度：O(1)
 */
#include <cstdio>
using namespace std;

int main() {
    int n, m; scanf("%d %d", &n, &m);
    if (m > n) { int t = m; m = n; n = t; }
    if (m == 1) printf("%d\n", n);
    else if (m == 2) printf("%d\n", 2 * (2 * (n / 4) +
        ((n % 4) < 2 ? n % 4 : 2)));
    else printf("%d\n", m * n - (n * m) / 2);
    return 0;
}