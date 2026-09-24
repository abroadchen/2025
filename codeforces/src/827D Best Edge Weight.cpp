//
// Created by Psy.C on 2026/9/24.
//

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5, M = 17, inf = 0x3f3f3f3f;

struct edge { int u, v, w, id; } E[N];

inline bool cmp(const edge& a, const edge& b) {
    return a.w < b.w;
}
inline bool cmp2(const edge& a, const edge& b) {
    return a.id < b.id;
}
int fa[N];
inline int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int anc[N][M+3], dep[N], w[N][M], e[N];
vector<int> to[N], W[N];
void dfs(int u, int f) {
    anc[u][0] = f; dep[u] = dep[f] + 1;
    for (int i = 1; i < M; ++i) {
        anc[u][i] = anc[anc[u][i-1]][i-1];
        w[u][i] = max(w[u][i-1], w[anc[u][i-1]][i-1]);
    }
    int sz = to[u].size();
    for (int i = 0; i < sz; ++i) {
        int v = to[u][i];
        if (v == f) continue;
        e[v] = W[u][i]; w[v][0] = E[W[u][i]].w;
        dfs(v, u);
    }
}

int query(int u, int v, int& lca) {
    if (dep[u] < dep[v]) swap(u, v);
    int ret = -inf, d = dep[u] - dep[v];
    for (int i = 0; d; d >>= 1, ++i)
        if (d&1) {
            ret = max(ret, w[u][i]);
            u = anc[u][i];
        }
    if (u == v) { lca = u; return ret; }
    for (int i = M-1; i >= 0; --i) {
        if (anc[u][i] != anc[v][i]) {
            ret = max(ret, w[u][i]);
            ret = max(ret, w[v][i]);
            u = anc[u][i]; v = anc[v][i];
        }
    }
    ret = max(ret, w[u][0]);
    ret = max(ret, w[v][0]);
    lca = anc[u][0];
    return ret;
}

int ans[N];
void modify(int u, int v, int val) {
    u = find(u);
    if (dep[u] < dep[v]) return;
    while (dep[u] > dep[v]) {
        ans[e[u]] = val-1;
        int nxt = find(anc[u][0]);
        fa[find(u)] = nxt;
        u = nxt;
    }
}


int n, m;
vector<int> NT;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
        E[i].id = i;
    }
    sort(E+1, E+m+1, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        int u = E[i].u, v = E[i].v;
        int fx = find(u), fy = find(v);
        if (fx != fy) {
            fa[fx] = fy;
            to[u].push_back(v); to[v].push_back(u);
            W[u].push_back(E[i].id);
            W[v].push_back(E[i].id);
        } else NT.push_back(E[i].id);
    }
    sort(E+1, E+m+1, cmp2);
    memset(w, 0x3f, sizeof w);
    memset(ans, 0x3f, sizeof ans);
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int sz = NT.size();
    for (int i = 0; i < sz; ++i) {
        int t = NT[i], lca;
        ans[t] = query(E[t].u, E[t].v, lca) - 1;
        modify(E[t].u, lca, E[t].w);
        modify(E[t].v, lca, E[t].w);
    }
    for (int i = 1; i <= m; ++i) {
        if (ans[i] >= inf-1) printf("-1 ");
        else printf("%d ", ans[i]);
    }
    return 0;
}