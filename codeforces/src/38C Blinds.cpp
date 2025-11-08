//
// Created by Psy.C on 2025/9/23.
//
/*
*n: 数组元素个数
l: 最小长度限制
 *
*i代表当前考虑的矩形高度
从l开始确保满足最小长度限制
 *
*a[j] / i: 计算长度为a[j]的木板最多能切出多少段长度为i的小段
i * (a[j] / i): 每段长度为i，共有(a[j]/i)段，所以面积为i*(a[j]/i)
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

const long M = 101;

int main() {

    long n, l; scanf("%ld %ld", &n, &l);
    vector<long> a(n);
    for (int i = 0; i < n; ++i) scanf("%ld", &a[i]);

    long maxArea(0);
    for (long i = l; i < M; ++i) {
        long area(0);
        for (long j = 0; j < n; ++j)
            area += i * (a[j] / i);
        maxArea = (maxArea > area) ? maxArea : area;
    }

    printf("%ld\n", maxArea);
    return 0;
}