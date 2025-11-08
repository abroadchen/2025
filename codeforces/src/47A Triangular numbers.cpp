//
// Created by Psy.C on 2025/10/10.
//
/*
 *
*三角数是指可以排成等边三角形的点的数量，其通项公式为：T(k) = k(k+1)/2

判断方法：

如果 n 是三角数，则存在整数 k 使得 n = k(k+1)/2
通过数学变换得到：k² + k - 2n = 0
使用求根公式：k = (-1 + √(1 + 8n)) / 2
因此 n 是三角数当且仅当 1 + 8n 是完全平方数且 √(1 + 8n) 是奇数
代码通过检查 1 + 8 * n 是否为完全平方数来判断 n 是否为三角数。
 *
 */
#include <cstdio>
#include <cmath>
using namespace std;

int main() {

    int n(0); scanf("%d",&n);
    int tmp = sqrt(1 + 8 * n);
    if (tmp * tmp == 1 + 8 * n) puts("YES");
    else puts("NO");
    return 0;
}