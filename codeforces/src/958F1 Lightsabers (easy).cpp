//
// Created by Psy.C on 2026/10/20.
//
/**
外层枚举左端点 l，内层枚举右端点 r，覆盖所有连续子数组 [l, r]
对每个枚举到的子数组，清空临时频数数组 t[]，然后统计子数组中每个值出现的次数。t[v] = 值 v 在子数组中出现次数
检查是否对所有 i∈[1,m]，t[i] == k[i]（元素值在 1..m 范围）。若全部相等，说明找到了匹配的子数组，输出 YES 并立即结束
所有子数组都不匹配
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (ll i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 105;

ll n, m, a[N], k[N], t[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> k[i];//目标频数
    rep(l,n) for (ll r = l; r <= n; r++) {
        memset(t, 0, sizeof t);
        for (ll i = l; i <= r; i++) t[a[i]]++;
        bool flg = true;
        rep(i,m) if (t[i] != k[i]) flg = false;
        if (flg) { cout << "YES"; return 0; }
    }
    cout << "NO";
    return 0;
}