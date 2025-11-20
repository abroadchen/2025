//
// Created by Psy.C on 2025/11/19.
//
/*
*r = 0（计数器）
a = n（被除数）
b = i（除数）
 *
*执行欧几里得算法的变种：
当b > 0时循环：
r += a / b：将商加到计数器r中
a %= b：计算a除以b的余数
swap(a, b)：交换a和b的值
这实际上是计算辗转相除法的步数，但同时累加了每次的商
 *
*如果最终的a等于1（即gcd(n,i) = 1，n和i互质）：
更新c为c和(r-1)的较小值
注意这里是r-1而不是r，因为最后一次循环a变为0时多计算了一次
 *
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, c = 1e9;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int r = 0, a = n, b = i;
        while (b > 0) {
            r += a / b;
            a %= b;
            swap(a, b);
        }
        if (a == 1) c = min(c, r - 1);
    }
    cout << c << '\n';
    return 0;
}