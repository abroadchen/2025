//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
l = 当前段起点。
r = 当前段能最远覆盖到的位置（初始为 a[1]）
每轮 ans++ 表示多跳一步。
在当前可覆盖区间 [l, r] 内，扫描所有点并不断用 max(r, a[i]) 扩大最远可达位置。
扫完后，下一段的起点 l = r+1，并重置 r = a[l]

当循环内 r 被扩展到 ≥ n 时，l = r+1 可能超过 n（甚至超过数组下标范围 1e4）。
随后执行 r = a[l]——若 l > n，则访问 a[l] 越界（读取到未初始化/越界内存）。
虽然 while (l <= n) 会在下次判断时退出，但 r = a[l] 在判断前已经执行，可能导致未定义行为（UB）或读到垃圾值。
更安全的写法是：在 l = r+1 后先判断 l > n 就 break，再访问 a[l]。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e4+5;
int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 1, r = a[1];
    while (l <= n) {
        ans++;
        for (int i = l; i <= r; i++) r = max(r, a[i]);
        l = r + 1, r = a[l];
    }
    cout << ans << '\n';
    return 0;
}