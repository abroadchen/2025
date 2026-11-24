//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
a=节点标号 c[x][1/2]=子树内1/2个数 s1/s2=全局总数
初始化自身计数，递归子树并累加子树统计
c[x][2]==s2 && c[x][1]==0：子树含全部 2 且无 1 → 割开后另一边全 1，合法。
c[x][1]==s1 && c[x][2]==0：子树含全部 1 且无 2 → 另一边全 2，合法

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 3e5+5;

int a[N], c[N][3], s1, s2, ans;
vector<int> g[N];
inline void dfs(int x, int lst) {
    if (a[x] == 1) c[x][1]++;
    if (a[x] == 2) c[x][2]++;
    for (auto u : g[x]) if (u != lst) {
        dfs(u,x);
        c[x][1] += c[u][1]; c[x][2] += c[u][2];
    }
    if (c[x][1] == 0 && c[x][2] == s2 ||
        c[x][2] == 0 && c[x][1] == s1) ans++;
}

int n;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) s1++;
        if (a[i] == 2) s2++;
    }
    for (int i = 2, u, v; i <= n; i++)
        cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    dfs(1,0);
    cout << ans;
    return 0;
}