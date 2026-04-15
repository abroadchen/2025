//
// Created by Psy.C on 2026/4/15.
//
/**
to: 目标节点
nxt: 下一条边
fr: 起始节点
pre: 反向边指针
in[N]: 入度数组
tp[N]: 拓扑排序结果
tot: 拓扑排序计数器
dfs: 深度优先搜索，标记连通分量

add(y, x)（反向建图）同时更新入度
用vis标记目标节点
如果当前节点在目标序列中
从该节点开始DFS，标记所属连通分量
将该节点加入答案
验证每个节点的父节点是否符合目标序列
如果不符合，输出-1
否则输出答案序列
时间复杂度：O(n+m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct edge { int to, nxt, fr, pre; } e[N<<1];

int head[N], cnt, pre[N];
void add(int x, int y) {
    e[++cnt] = {y, head[x], x, pre[y]}, head[x] = cnt, pre[y] = cnt;
}

int n, in[N], tp[N], tot;
void topo() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); tp[++tot] = u; q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
}

int fa[N];
void dfs(int u, int f) {
    if (fa[u]) return;
    fa[u] = f;
    for (int i = pre[u]; i; i = e[i].pre) {
        int v = e[i].fr;
        dfs(v, f);
    }
}

int m, a[N], ans[N], nt;
bool vis[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y; add(y, x); in[x]++;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; vis[a[i]] = 1;
    }
    topo();
    for (int i = 1; i <= n; ++i) {
        if (vis[tp[i]]) {
            dfs(tp[i], tp[i]);
            ans[++nt] = tp[i];
        }
    }
    for (int i = 1; i <= n; ++i)
        if (fa[i] != a[i]) { cout << -1; return 0; }
    cout << nt << '\n';
    for (int i = 1; i <= nt; ++i) cout << ans[i] << '\n';
    return 0;
}