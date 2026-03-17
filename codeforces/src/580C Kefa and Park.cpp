//
// Created by Psy.C on 2026/3/16.
//
/**
a[]:节点属性值，m:最大允许连续错误数，tot:符合条件的叶子节点数
邻接表存储树结构
s:当前节点，sum:当前连续错误数
如果a[s]为真则连续错误数+1，否则重置为0
如果连续错误数超过限制，返回 连续遇到值为非0的节点数
如果不是根节点且是叶子节点（只有一个邻接点）
递归访问所有邻居节点
统计所有可达的叶子节点数量（除了根节点外，只有1个邻居的节点）

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

bool vis[N];
ll a[N], m, tot;
vector<ll> e[N];
void dfs(ll s, ll sum) {
    if (vis[s]) return;
    vis[s] = true;
    if (a[s]) sum++; else sum = 0;
    if (sum > m) return;
    if (s != 1 && e[s].size() == 1) tot++;
    for (int i = 0; i < e[s].size(); ++i)
        dfs(e[s][i], sum);
}

ll n;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0, u, v; i < n-1; ++i) {
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1, 0);
    cout << tot;
    return 0;
}