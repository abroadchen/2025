//
// Created by Psy.C on 2025/11/13.
//
/*
*n：总人数/总球数
m：颜色种类数
h：目标颜色
 *a[i]表示第i种颜色的球数
 *
 *如果总球数小于需要选择的球数n，输出"-1"（不可能完成）
 *
*计算选出的n个球中没有目标颜色h球的概率s
结果为1 - s（至少有一个目标颜色球的概率）
 *
*总的选法数：C(sum, n)
不包含目标颜色的选法数：C(sum - a[h], n)
不包含目标颜色的概率：C(sum - a[h], n) / C(sum, n)
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n, m, h; scanf("%d%d%d", &n, &m, &h);
    vector<int> a(m + 1, 0); int sum = 0;

    for (int i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if (sum < n) puts("-1");
    else {
        double s = 1.;
        for (int i = 1; i < n; ++i)
            s = s * (sum + 1 - a[h] - i) / (sum - i);
        printf("%.10f\n", 1 - s);
    }
    return 0;
}