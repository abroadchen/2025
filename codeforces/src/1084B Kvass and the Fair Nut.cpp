//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
n 个数，s 是某目标总削减量，
若能削减（sum >= s），求 ①每个数最多同时被削减到的下限，且 ②不把某个数削成负的——于是答案是：
min( 原最小值 mn,  平均削减量 (sum-s)/n )
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e9-1;

ll n, s, t, mn = N, sum;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> t;
        mn = min(mn, t);
        sum += t;
    }
    if (sum < s) cout << -1 << '\n';
    else cout << min(mn, (sum-s)/n) << '\n';
    return 0;
}