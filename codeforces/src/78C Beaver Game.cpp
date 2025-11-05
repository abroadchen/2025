//
// Created by Psy.C on 2025/11/5.
//
/*
 *循环遍历从1到√m的所有整数
 *如果i不是m的因子，则跳过本次循环
 *如果i是m的因子，那么m/i也是m的因子
 *
*可以将长度为m的段分割成大小为i的部分，每部分长度为m/i
要求每部分长度至少为k，且分割数大于1
*可以将长度为m的段分割成大小为m/i的部分，每部分长度为i
要求每部分长度至少为k，且分割数大于1
O(√m)：只需要遍历到m的平方根来找因子
 */
#include <cstdio>
using namespace std;

int main() {

    int n, m, k; scanf("%d %d %d\n", &n, &m, &k);
    if (n % 2 == 0) { puts("Marsel"); return 0; }
    else {
        bool p(0);
        for (int i = 1; i * i <= m; ++i) {
            if (m % i > 0) continue;
            if ((k <= m / i && i > 1) ||
                (k <= i && m / i > 1)) {
                p = 1;
                break;
            }
        }
        puts(p ? "Timur" : "Marsel");
    }
    return 0;
}