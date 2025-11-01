//
// Created by Psy.C on 2025/11/1.
//
/*
 *
*如果当前元素a[i]大于mid，则按照特定公式累加
公式含义：超出部分乘以(1-f/100)的系数
 *如果当前元素a[i]小于等于mid，则直接累加差值
*根据t的正负性调整二分查找区间
如果t>0，说明mid偏小，将左边界移到mid
否则将右边界移到mid
 */
#include <cstdio>
using namespace std;

const double eps = 1e-9;
const int N = 100001;
int n, i, a[N];
double f, l(0), r(1010), mid, t;

int main() {
    scanf("%d", &n); scanf("%lf", &f);
    for (i = 0; i < n; ++i) scanf("%d", a + i);
    while (r - l > eps) {
        mid = (l + r) / 2.0; t = 0;
        for (i = 0; i < n; ++i) {
            if (a[i] > mid) t += (a[i] - mid) * (1 - f / 100.0);
            else t += a[i] - mid;
        }
        if (t > 0.0) l = mid;
        else r = mid;
    }
    printf("%lf\n", mid);
    return 0;
}