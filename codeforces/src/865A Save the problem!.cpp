//
// Created by Psy.C on 2026/10/4.
//
/**
n/2 + 1 == a 等价于 n = 2*(a-1)。

由于是 n/2（整除），对任意输入 a（a≥1），循环一定会找到一个正整数 n = 2*(a-1) 满足条件（因为右边是偶数，整除不丢精度）。于是：

对输入 a，输出 n = 2a - 2 和 2
然后输出一条边 1 2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, n;
int main() {
    fast;
    while (cin >> a) {
        n = 1;
        while (true) {
            if (n/2+1 == a) {
                cout << n << ' ' << 2 << '\n';
                cout << 1 << ' ' << 2 << '\n';
                break;
            }
            n++;
        }
    }
    return 0;
}