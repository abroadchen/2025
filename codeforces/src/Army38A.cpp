//
// Created by Psy.C on 2025/9/23.
//
/*
 *
*tmp用于临时存储每年的时间间隔
curr用于存储起始年份
rank用于存储结束年份
 *
*计算前缀和：years[i]等于前一年的累积值加上当前年份的时间间隔
这样years数组就存储了从第1年到第i年的总时间跨度
 *
 *
 *通过前缀和的差值直接计算区间和
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {

    int n; scanf("%d", &n);
    int* years = new int[n + 1];//动态分配一个大小为n+1的整型数组years，用于存储累积年份数据
    years[0] = years[1] = 0;

    int tmp(0), curr(0), rank(0);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &tmp);
        years[i] = years[i - 1] + tmp;
    }
    scanf("%d %d", &curr, &rank);
    printf("%d", years[rank] - years[curr]);

    return 0;
}