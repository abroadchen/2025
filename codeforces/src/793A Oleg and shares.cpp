//
// Created by Psy.C on 2026/9/15.
//
/**
读入所有数，并记录最小值 mn。因为只能做"减 k"操作，所有数最终只能降到 mn（再小就没意义），所以目标就是让每个数都变成 mn
对每个数：差值 a[i]-mn 必须能被 k 整除，否则这个数无法通过"每次减 k"精确降到 mn → 无解，标记 f=1 并跳出。
若可行，该数需要的操作次数 = (a[i]-mn)/k，累加到 ans
有任一数不满足整除 → 输出 -1；否则输出总操作次数 ans。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+1, inf = 1e9+1;
ll a[N], ans, f;
int main() {
    fast;
    ll n, k, mn(inf); cin >> n >> k;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < mn) mn = a[i];
    }
    ans = 0, f = 0;
    for (ll i = 0; i < n; ++i) {
        if ((a[i]-mn)%k != 0) { f = 1; break; }
        ans += (a[i]-mn)/k;
    }
    if (f) cout << "-1\n";
    else cout << ans << '\n';
    return 0;
}