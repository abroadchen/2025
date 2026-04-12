//
// Created by Psy.C on 2026/4/11.
//
/**
l1: 从1开始（奇数：1, 3, 5, 7, ...）
l2: 从l1结束处继续（接下来的奇数）
r1: 从2开始（偶数：2, 4, 6, 8, ...）
r2: 从r1结束处继续（接下来的偶数）

遍历从1到n的所有索引
对于每个索引，按顺序检查：l2, l1, r2, r1
只输出≤ m的数值
在需要时添加空格
use跟踪已打印的数字数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105;
int n, m, l1[N], l2[N], r1[N], r2[N];
int main() {
    fast;
    cin >> n >> m;
    int s = 1;
    for (int i = 1; i <= n; ++i) { l1[i] = s; s += 2; }
    for (int i = 1; i <= n; ++i) { l2[i] = s; s += 2; }
    s = 2;
    for (int i = 1; i <= n; ++i) { r1[i] = s; s += 2; }
    for (int i = 1; i <= n; ++i) { r2[i] = s; s += 2; }
    int use = 0;
    for (int i = 1; i <= n; ++i) {
        if (l2[i] <= m) {
            if (use) cout << ' ';
            use++;
            cout << l2[i];
        }
        if (l1[i] <= m) {
            if (use) cout << ' ';
            use++;
            cout << l1[i];
        }
        if (r2[i] <= m) {
            if (use) cout << ' ';
            use++;
            cout << r2[i];
        }
        if (r1[i] <= m) {
            if (use) cout << ' ';
            use++;
            cout << r1[i];
        }
    }
    cout << '\n';
    return 0;
}