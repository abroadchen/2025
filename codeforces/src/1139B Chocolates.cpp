//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
末尾元素：无条件取 a[n-1]，now 设为它。
从后往前，对每个 a[i]：
若 a[i] < now：取 a[i]，now 更新为 a[i]。
若 a[i] ≥ now：不能取 a[i]（会破坏递减限制），于是退而取 now-1（比当前最大值小 1），并把 now 减 1。
一旦 now == 1，因为取到 1 之后不能再减，就 break 结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, inf = 1e9+10;
ll n, a[N];
int main() {
    fast;
    cin >> n;
    ll now = inf, ans = 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = n-1; i >= 0; i--) {
        if (now == 1) break;
        if (i == n-1) { ans += a[i]; now = a[i]; }
        else {
            if (a[i] < now) { ans += a[i]; now = a[i]; }
            else { ans += now-1; now -= 1; }
        }
    }
    cout << ans << '\n';
    return 0;
}