//
// Created by Psy.C on 2025/11/9.
//
/*
 *n（网格总元素数）、m（每行元素数）、a和b（起点和终点索引）
 *
*一步可达的情况：
m == 1：只有一列，所有点都在同一列
a / m == b / m：a和b在同一行
特殊情况：a在行首且b在行尾（同行末尾或整个网格末尾）
 *
*两步可达的情况：
a % m == 0：a在行首，可以横向移动
b % m == m - 1：b在行尾，可以横向移动
b == n - 1：b在整个网格末尾
m + b % m - a % m + 1 == b - a + 1：特殊的对角线情况
a % m == b % m + 1：a比b正好靠右一列
 *
 */
#include <cstdio>
using namespace std;

int main() {

    int n, m, a, b; scanf("%d %d %d %d\n", &n, &m, &a, &b);
    --a; --b;
    int ans(0);

    if (m == 1 || a / m == b / m || (a % m == 0 &&
        (b % m == m - 1 || b == n - 1))) ans = 1;
    else if (a % m == 0 || b % m == m - 1 || b == n - 1 ||
        m + b % m - a % m + 1 == b - a + 1 ||
        a % m == b % m + 1) ans = 2;
    else ans = 3;
    printf("%d\n", ans);
    return 0;
}