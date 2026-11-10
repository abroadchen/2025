//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
用链式前向星存无向图（每条边存两次），head[u] 指向 u 的第一条邻边
sz[u][0], sz[u][1]：子树（相对当前根）中被染成 0 色 / 1 色 的节点数量。
f[u][0], f[u][1]：子树内"配对 / 距离贡献"累计值，两色分别存
"树上二分图/独立集类" DP，0/1 表示节点颜色，要求相邻节点颜色相反（二分染色）。此时：

sz[u][c] = 以 u 为根、u 染成颜色 c 时，子树中 与 u 同奇偶层（颜色 c）的节点数（即合法染色的本颜色节点数）。因为相邻必须异色，u=0 则其孩子必为 1。
f[u][c] = 同样前提下，某种加总值（对应题目的距离和/组合计数，往往是"某种匹配代价"）。
初始 sz[u][0]=1（u 自己算一个 0 色节点），dep[u]=dep[fa]+1 记录深度。

关键转移含义（二分染色 DP）‍：u 若取颜色 0，孩子 v 必须取颜色 1，而 v 作为颜色 1 时它子树里与 v 同色（1色）的节点数 = sz[v][1]，这些计入 u 的 0 色统计 sz[u][0] += sz[v][1]。f 的转移同理，只是额外记录跨边的代价
换根核心思想：父子交换时，u 的新状态 = 原本以 1 为根时 u 的子树结果 + 父分支传来的部分，并且要减去原来的孩子分支（因为那个孩子现在变成独立根，不再属于 u 的"子树"）。

s[fa][0] - sz[u][0]：父分支去掉 u 后剩余的 0 色点数。
g[fa][1] - (f[u][0]+sz[u][0])：父分支去掉 u 这块贡献后,反向补回（颜色取反）。
这就是标准的 换根 DP 的"减去孩子贡献 + 加上父侧"技巧
g[u][0] + g[u][1] = 以 u 为根、合法二分染色时的某种总计数（两色分类合计）。
把所有 u 累进 ans，最后 ans/2 —— 因为每条边 / 每种对称方案被计算了两次（颜色整体翻转 0↔1 被视为同一方案），所以要除 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int e[N<<1], nxt[N<<1], head[N], cnt;
void add(int u, int v) {
    e[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

int sz[N][2], dep[N];
ll f[N][2];
void dfs(int u, int fa) {
    sz[u][0] = 1; dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (v == fa) continue;
        dfs(v, u);
        f[u][0] += f[v][1];//u 为0色时，孩子必须1色才能"合法"
        f[u][1] += f[v][0] + sz[v][0];//u 为1色时，孩子0色，且每个0色孩子节点贡献+1
        sz[u][0] += sz[v][1];//u为0时，合法子树里1色孩子占位
        sz[u][1] += sz[v][0];//u为1时，0色孩子占位
    }
}

ll g[N][2], ans;
int s[N][2];
void dfs2(int u, int fa) {
    g[u][0] = f[u][0]; g[u][1] = f[u][1];
    s[u][1] = sz[u][1]; s[u][0] = sz[u][0];
    if (fa) {//换根：u 从原来的"父"分支吸收 fa 那一侧的信息
        g[u][0] += g[fa][1] - (f[u][0]+sz[u][0]);
        g[u][1] += g[fa][0] - f[u][1] + s[fa][0] - sz[u][1];
        s[u][0] += s[fa][1] - sz[u][0];
        s[u][1] += s[fa][0] - sz[u][1];
    }
    ans += g[u][0] + g[u][1];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (v == fa) continue;
        dfs2(v, u);
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    dfs(1, 0); dfs2(1, 0);
    cout << ans/2 << '\n';
    return 0;
}