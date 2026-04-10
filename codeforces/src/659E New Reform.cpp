//
// Created by Psy.C on 2026/4/10.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
bool vis[N], flag;
vector<int> G[N];
void dfs(int u, int rt, int fa) {
    if (vis[u]) {
        flag = true;//发现环
        return;
    }
    vis[u] = true;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == fa) continue;
        dfs(v, rt, u);
    }
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        G[i].clear();
    }
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        flag = false;
        dfs(i, i, -1);
        ans += flag == false;//没有发现环
    }
    cout << ans << '\n';
    return 0;
}