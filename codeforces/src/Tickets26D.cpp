//
// Created by Psy.C on 2025/9/19.
//
/*
 *
*从n+1个数中选择k+1个数
要求至少有一个数大于等于m的概率
具体来说：

tmp计算的是所有选择的数都小于m的概率
1-tmp就是至少有一个数大于等于m的概率
数学公式：

P(至少一个≥m) = 1 - C(m-1, k+1)/C(n+1, k+1)
 *
 *
 *时间复杂度：O(k) 空间复杂度：O(1)
 *
 *
 */
#include <cstdio>
using namespace std;

int n, m, k;

int main() {

    scanf("%d%d%d", &n, &m, &k);

    if (m <= k) puts("1");
    else if (m > n + k) puts("0");
    else {
        double tmp = 1;

        for (int i = 0; i <= k; ++i)
            tmp = tmp * (m - k + i) / (n + 1 + i);

        printf("%.6lf\n", 1 - tmp);
    }
    return 0;
}