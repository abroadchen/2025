//
// Created by Psy.C on 2026/4/17.
//
/**
邻接表，存储树的边关系，v[i]包含节点i的所有相邻节点

累加经过这条边的路径数量。
siz[v[x][i]]表示以子节点为根的子树中有多少个目标节点。
2*k-siz[v[x][i]]表示除了这棵子树外还有多少个目标节点。
取两者的最小值，表示通过这条边连接两部分的最少路径数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

vector<int> v[N];
int siz[N], k;
ll ans;
void dfs(int x, int pre) {
    for (int i = 0; i < v[x].size(); ++i) {
        if (v[x][i] == pre) continue;
        dfs(v[x][i], x);
        siz[x] += siz[v[x][i]];//更新当前节点的子树大小，加上子节点的子树大小
        ans += min(siz[v[x][i]], 2*k-siz[v[x][i]]);
    }
}

int n;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, x; i <= 2*k; ++i) {
        cin >> x; siz[x]++;//标记这些节点为目标节点
    }
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs(1, -1);
    cout << ans;
    return 0;
}