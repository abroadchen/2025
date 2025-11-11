//
// Created by Psy.C on 2025/11/10.
//
/*
*n：多项式的次数
i, j：循环变量
a[101]：存储多项式系数的数组
z：临时计算结果
ans：最终答案
 *
 */
#include <cstdio>
using namespace std;

int n, i, j;
double a[101], z, ans;

int main() {
    scanf("%d",&n);
    for (i = 0; i <= n; ++i) scanf("%lf",&a[i]);
    for (i = 0; i <= n/2; ++i) {
        for (j = n/2+1; j <= n; ++j) {
            z = (a[i]*(2*j-n)+a[j]*(n-2*i))/2/(j-i);
            if (z > ans) ans = z;
        }
    }
    printf("%.10lf\n",ans);
    return 0;
}