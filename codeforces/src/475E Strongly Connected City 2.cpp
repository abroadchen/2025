//
// Created by Psy.C on 2026/2/15.
//
/**
dfn[u]: 节点u的访问序号
low[u]: 节点u能到达的最小序号
ins[u]: 节点u是否在栈中
w[col]: 强连通分量col的节点数
scc[u]: 节点u所属的强连通分量编号
k: 所有强连通分量内部连接数的总和

f: 位集，表示可达的子树大小
f |= f<<siz[j]: 状态转移，考虑加入子树j
枚举最优分割点，最大化连接数

时间复杂度: O(n²/64)（bitset优化）
空间复杂度: O(n)
 */
#include <bits/stdc++.h>
#define N 40010
using namespace std;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x<<3)+(x<<1)+(ch&15); ch = getchar(); }
    return x*f;
}

int dfn[N], low[N], tot, ins[N], stk[N], top, w[N], scc[N], k;
vector<int> e[N];
void tarjan(const int u, const int fa) {
    dfn[u] = low[u] = ++tot;
    ins[u] = 1, stk[++top] = u;
    for (const auto v : e[u]) {
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        const int col = ++tot;
        int v = -1;
        do {
            w[col]++;
            v = stk[top--];
            scc[v] = col;
            ins[v] = 0;
        } while (u^v);
        k += w[col] * w[col];
    }
}

int siz[N], res;
vector<int> g[N];
void dfs(const int u, const int fa) {
    siz[u] = w[u];
    for (const auto v : g[u])
        if (v^fa) dfs(v, u), siz[u] += siz[v];
    res += w[u] * (siz[u] - w[u]);//当前分量与子树其他分量的连接数
}

int n, m, ans;
bitset<N> f;
int main() {
    n = read(), m = read();
    for (int i = 1, u, v; i <= m; ++i) {
        u = read(), v = read();
        e[u].push_back(v); e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, 0);//缩点
    for (int i = 1; i <= n; ++i)
        for (const auto j : e[i])
            if (scc[i]^scc[j]) g[scc[i]].push_back(scc[j]);//缩点后的树
    for (int i = 1; i <= tot; ++i) {
        res = k; dfs(i, 0);
        f.reset(), f[0] = 1;
        for (const auto j : g[i]) f |= f<<siz[j];
        for (int j = (siz[i]-w[i])>>1; j >= 0; --j) if (f[j]) {
            res += j*(n-j-w[i]);
            ans = max(ans, res);
            break;
        }
    }
    cout << ans;
    return 0;
}