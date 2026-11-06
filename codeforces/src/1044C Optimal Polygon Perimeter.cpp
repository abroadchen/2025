//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
维护 4 个极值点：

a[0] = x 最大的点
a[1] = y 最小的点
a[2] = x 最小的点
a[3] = y 最大的点
dist(i,j)：极值点 i、j 之间曼哈顿距离（j%=4 允许 j 越界取模，所以 dist(i,i+1) 也合法）。
dis(i,k)：极值点 i 到原始点 k 的曼哈顿距离。
对每个极值点对 (i,j)，加上任意原始点 k，取 t + tmp 的最大值
dist(i,i+1) 因为 j%=4，所以是4个极值点按顺序围成的闭圈周长（a0→a1→a2→a3→a0）
第 4 个点输出 res（枚举极值点对的最大值）。
第 5..n 个点输出 ans（4 极值点闭环周长）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+10;

ll a[4][2];
ll dist(int i, int j) {
    j %= 4;
    return abs(a[i][0]-a[j][0]) + abs(a[i][1]-a[j][1]);
}

int xi[N], yi[N];
ll dis(int i, int j) {
    return abs(a[i][0]-xi[j]) + abs(a[i][1]-yi[j]);
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y; xi[i] = x, yi[i] = y;
        if (i == 1) {
            for (auto &j : a) j[0] = x, j[1] = y;
        } else {
            if (x > a[0][0]) a[0][0] = x, a[0][1] = y;
            if (y < a[1][1]) a[1][0] = x, a[1][1] = y;
            if (x < a[2][0]) a[2][0] = x, a[2][1] = y;
            if (y > a[3][1]) a[3][0] = x, a[3][1] = y;
        }
    }
    ll res = 0;
    rep(i,4) rep(j,4) {
        ll t = dist(i,j);
        if (i == j) continue;
        for (int k = 1; k <= n; k++) {
            ll tmp = dis(i,k) + dis(j,k);
            res = max(res, t + tmp);
        }
    }
    ll ans = 0;
    rep(i,4) ans += dist(i,i+1);
    cout << res;
    for (int i = 4; i <= n; i++) cout << ' ' << ans;
    return 0;
}