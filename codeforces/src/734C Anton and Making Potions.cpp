//
// Created by Psy.C on 2026/4/27.
//
/**
使用upper_bound在数组d[1...k]中查找第一个大于s的位置
计算找到的索引，然后用c数组对应位置的值
计算(n - c[索引])*x作为初始答案
循环遍历数组a和b的所有元素
如果b[i] > s，则跳过这个元素
计算y = s - b[i]（剩余资源）
在d数组中查找小于等于y的最大索引
计算(n - c[索引])*a[i]，并与当前ans比较取最小值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;
ll n, m, k, x, s, a[N], b[N], c[N], d[N];
int main() {
    fast;
    cin >> n >> m >> k >> x >> s;
    for (ll i = 0; i < m; ++i) cin >> a[i];
    for (ll i = 0; i < m; ++i) cin >> b[i];
    for (ll i = 1; i <= k; ++i) cin >> c[i];
    for (ll i = 1; i <= k; ++i) cin >> d[i];
    ll ans = (n - c[upper_bound(d+1, d+k+1, s)-d-1])*x;
    for (ll i = 0; i < m; ++i) {
        if (b[i] > s) continue;
        ll y = s - b[i];
        ans = min(ans, (n-c[upper_bound(d+1, d+k+1, y)-d-1])*a[i]);
    }
    cout << ans << '\n';
    return 0;
}