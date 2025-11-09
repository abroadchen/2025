//
// Created by Psy.C on 2025/9/25.
//
/*
 *a[i]存储第i个元素的"需求量"或"比例值"
 *b[i]存储第i个元素的"价值"或"收益值"
 *
*计算每个元素的收益比例 r = b[i]/a[i]（单位需求的收益）
如果当前元素的收益比例小于当前x，则更新x为这个更小的收益比例
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    //n表示元素个数，v表示总体积限制
    long n, v; scanf("%ld %ld\n", &n, &v);

    vector<double> a(n, 0), b(n, 0);
    double sum(0);
    for (long i = 0; i < n; ++i) {
        scanf("%lf", &a[i]);
        sum += a[i];
    }

    for (long i = 0; i < n; ++i) scanf("%lf", &b[i]);
    double x(v/sum);

    for (long i = 0; i < n; ++i) {
        double r = b[i] / a[i];
        if (r < x) x = r;
    }

    printf("%.5lf\n", x * sum);
    return 0;
}