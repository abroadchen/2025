//
// Created by Psy.C on 2026/9/12.
//
/**
col 数组存放颜色，col[1]=1（根节点颜色 1），col[0]=0（虚父节点作哨兵）。
DFS 从 u 遍历所有邻居 v（跳过父节点 fa）。
cnt 从 1 开始：
while (cnt == col[u] || cnt == col[fa]) cnt++：跳过与 u 的颜色、与父节点 u 的父节点颜色相同的值，从而保证 v 与父 u、邻居不撞色。
col[v] = cnt++：给 v 赋值第一个可用且不与父/祖父冲突的颜色。
递归染子树。
这样保证每条边的两端颜色不同（因为染 v 时避开了父 u 的颜色，且通过 cnt 递增避开已用色
k = 所有颜色中的最大值（即用到的颜色种数）。
输出 k，再输出每个节点的颜色
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5;
struct node { int v, nxt; } e[(N<<1)+5];
int tot, head[N+5];
void add(int u, int v) {
    e[++tot].v = v; e[tot].nxt = head[u]; head[u] = tot;
}

int col[N+5] = {0, 1};
void dfs(int u, int fa) {
    int cnt = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        while (cnt == col[u] || cnt == col[fa]) cnt++;
        col[v] = cnt++;
        dfs(v, u);
    }
}

signed main() {
    fast;
    int n, k; cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y; add(x, y); add(y, x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) k = max(k, col[i]);
    cout << k << '\n';
    for (int i = 1; i <= n; ++i) cout << col[i] << ' ';
    return 0;
}