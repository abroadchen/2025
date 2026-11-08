//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
a[i]：第 i 个位置的某项数值（如每个路口的车流量/拥堵数）；
x：上限/限制值（超标阈值）；
f：每次处理（如派一辆"披斗篷的车"/一次卸载）的花费；
读入数组长度、各位置值、上限 x、单次花费 f。
只处理 a[i] > x 的元素（未超限的不管）。

对每个超标元素，需处理次数
该次数 × f 元 = 该元素的处理费用，累加到 ans

ceil(A / B) = (A + B - 1) / B
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int n, a[N], x, f;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    cin >> x >> f;
    ll ans = 0;
    rep(i,n) if (a[i] > x) ans += 1ll*f*((a[i]+f-1)/(x+f));
    cout << ans << '\n';
    return 0;
}