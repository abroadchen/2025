//
// Created by Psy.C on 2026/10/16.
//
/**
条件 (n-i) % i == 0 等价于 n % i == 0（因为 n-i 与 n 对 i 同余，n % i 与 (n-i)%i 相同）。

所以实际是在数 n 的"非平凡正因子"的个数——即所有能整除 n 的 i（且 i < n）。

例如：

n=15：因子 1, 3, 5, 15；满足 i<15 的有 1,3,5 → ans=3。
n=6：因子 1,2,3,6 → i<6 的三... 1,2,3 → ans=3。
但注意 i 从 1 到 n-1，所以排除 i=n 自身，等价于"n 的正因子个数 - 1"

等价于 i | n，即 i 是 n 的因子
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

signed main() {
    fast;
    int n; cin >> n;
    int ans = 0;
    for (int i = 1; i < n; ++i)
        if ((n-i)%i == 0) ans++;
    cout << ans;
    return 0;
}