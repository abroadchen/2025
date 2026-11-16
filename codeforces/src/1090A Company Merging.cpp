//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
k[i].mx：第 i 组的最大值。
mx：所有组中的全局最大值（也是最终目标值）
对每组：把这一组里的每个元素都补齐到 mx，需要 mx - k[i].mx 次操作（因为该组最大值是 k[i].mx，把整个组都抬到 mx，每个元素至少要抬这么多）。
该组有 k[i].len 个元素，所以这一组代价 = len * (mx - k[i].mx)。
累加所有组，输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

struct node { ll mx, len; } k[N];

ll n, m, x, mx, ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> m; k[i].len = m;
        rep(j,m) {
            cin >> x;
            k[i].mx = max(k[i].mx, x);
        }
        mx = max(mx, k[i].mx);
    }
    rep(i,n) ans += k[i].len*(mx-k[i].mx);
    cout << ans;
    return 0;
}