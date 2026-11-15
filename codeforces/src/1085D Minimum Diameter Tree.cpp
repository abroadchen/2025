//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
"树上期望停时定理"：设树上叶子的某些值贡献下，期望步数 = 2*(s')/c，其中 c 是叶子数，2/c 起到归一化作用。
它本质是把"总代价 s"按叶子的可能终点均匀分摊，并用树的双向行走（来回）乘 2 系数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5;

int n, u, v, d[N];
double s, c;
int main() {
    fast;
    cin >> n >> s;
    rep(i,n-1) { cin >> u >> v; d[u]++; d[v]++; }
    rep(i,n) if (d[i] == 1) c++;
    cout << fixed << setprecision(10) << s/c*2;
    return 0;
}