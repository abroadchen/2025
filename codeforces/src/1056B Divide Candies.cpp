//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
cnt[i] = 在 1..n 中，x % m == i 的数的个数，初始所有余数都看作 n/m 个（下取整）
处理余数。前 n/m 个整组 1..(n/m)*m 里每个余数恰出现 n/m 次；
剩下的 (n/m)*m+1 .. n 共 n%(m) 个数，逐一把对应余数 i%m 的计数 +1。
于是 cnt[r] = 1..n 中模 m = r 的数字个数。
两重循环枚举所有余数 i、j（0..m-1）。
若 (i² + j²) % m == 0，则该余数组合合法：取到余数 i 的数有 cnt[i] 个，取到余数 j 的有 cnt[j] 个，配对数 = cnt[i]*cnt[j]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1050;

int n, m, cnt[N];
ll ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cnt[i] = n/m;
    for (int i = (n/m)*m+1; i <= n; i++) cnt[i%m]++;
    rep(i,m) rep(j,m) if (((i*i)%m+(j*j)%m)%m == 0)
        ans += (ll)cnt[i]*cnt[j];
    cout << ans << '\n';
    return 0;
}