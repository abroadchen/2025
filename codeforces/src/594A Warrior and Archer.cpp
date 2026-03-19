//
// Created by Psy.C on 2026/3/19.
//
/**
a[i+(n>>1)]：后半部分的第i个元素
a[i]：前半部分的第i个元素
a[i+(n>>1)] - a[i]：对应位置元素的差值
min(..., ans)：更新最小差值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 1<<30;
    for (int i = 1; i <= n>>1; ++i)
        ans = min(a[i+(n>>1)] - a[i], ans);
    cout << ans << '\n';
    return 0;
}