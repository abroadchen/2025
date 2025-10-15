//
// Created by Psy.C on 2025/10/14.
//
/*
 *"%d %d\n"是格式字符串，表示读取两个整数，后面可能跟换行符
 *
 *计算在m×n网格中可以放置的1×2多米诺骨牌的最大数量
 *
 */
#include <cstdio>
using namespace std;

int m(0), n(0);

int main() {
    scanf("%d %d\n", &m, &n);
    printf("%d\n", m * n / 2);
    return 0;
}