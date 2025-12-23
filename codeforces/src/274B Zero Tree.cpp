//
// Created by Psy.C on 2025/12/22.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

int vis[N];
vector<int> adj[N];//存储与节点i相邻的所有节点
pair<ll, ll> f[N];//存储节点i的两个状态值
ll lab[N];//存储节点i的权值
void dfs(const int u) {//当前访问的节点
    vis[u] = 1;
    ll inc = 0, dcr = 0;
    for (const int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
            inc = max(inc, f[v].first);
            dcr = max(dcr, f[v].second);
        }
    }
    lab[u] += inc - dcr;//加上子树的净贡献(inc-dcr)
    if (lab[u] >= 0) dcr += lab[u]; else inc += abs(lab[u]);
    f[u] = {inc, dcr};
}


int main() {
    fast;
    int n; cin>>n;
    for (int i = 1, u, v; i <= n - 1; ++i) {
        cin>>u>>v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        vis[i] = 0; cin>>lab[i]; f[i] = {0, 0};
    }
    ll ans = 0;
    dfs(1);
    ans = f[1].first + f[1].second;//根节点状态
    cout<<ans<<'\n';
    return 0;
}