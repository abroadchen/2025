//
// Created by Psy.C on 2026/9/28.
//
/**
能连续读 n，读到文件结束为止。每轮重新填 a[1..n]（下标 1 起始）。
当只有 2 个元素时，直接输出 a[2] - a[1] + a[2]，即 2*a[2] - a[1]。
含义：把 a[2] 当作"公差"，a[2]-a[1] 是公差 d，则下一项 = a[2] + d = a[2] + (a[2]-a[1])。
也就是把输入当作等差数列，往后推算下一项。（等差数列下一项 = 末项 + 公差）
x = a[2] - a[1]：先假设公差为前两项差。
遍历相邻项，检查每一对相邻差是否都等于 x。
只要有一处不等，flag 置 0 并提前 break。
这样 flag == 1 表示整个数组构成等差数列，公差为 x
是等差数列：输出 x + a[n]，即"下一项 = 末项 + 公差"。这与 n=2 时的公式完全一致（n=2 时必然等差，就是 2 项，下一项 = a[2] + 公差）。
不是等差数列：输出 a[n]（末项原样）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int a[N], n;
int main() {
    fast;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) cin >> a[i];
        if (n == 2) cout << a[2]-a[1]+a[2] << '\n';
        else {
            int x = a[2] - a[1];
            bool flag = 1;
            for (int j = 2; j <= n; ++j) {
                if (a[j] - a[j-1] != x) {
                    flag = 0; break;
                }
            }
            if (flag) cout << x+a[n] << '\n';
            else cout << a[n] << '\n';
        }
    }
    return 0;
}