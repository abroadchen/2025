//
// Created by Psy.C on 2026/9/12.
//
/**
G[u][i]：节点 u 通过字符 i（'a'..'z'）到子节点的边。若为 0 表示无此边。
这是一棵 26 叉字典树，每条边带一个字母
后序遍历，sz[u] = 子树节点数。
p[u] = u 的最重子树根（用于后续合并基准）
把 u 的子树贪心并入 v：对应字母的边若 v 也有则递归合并；若 v 没有则直接挂到 v 下。
s 累计合并过程中的某种计数（这里 s++ 在每次进入 uni 时 +1）
del(u, v) 用于删除之前 uni 在 v 上造成的结构变更，保证 dfs2 的分支之间互不影响（还原现场）
sc[u]：u 的子节点个数（叶子为 0，直接 return）。
对 u 的每个子节点：把所有非重子树用 uni 合并进重子树 p[u]，每次 uni 的 s 累加进 sum。
uni 里每个"无法进一步合并、需单独保留的子树"都会 s++——最终 sum 就是"合并后 u 这层最少保留的 26 叉分支数"（启发式合并：小的并进大的，结果最优）。
f[h] += sum：记录深度 h（到根距离）处这种"合并后分支数"的累积。
del 撤销后递归子节点
建树（以 1 为根，每条边带字母）。
dfs(1) 算 sz 和重儿子；dfs2(1,1) 算每个深度 h 的 f[h]（该深度合并后的最少分支总和）。
找 f 最大的深度 ans。
输出 n - f[ans] 和 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 6e5+10, M = 26;

int sz[N], G[N][M], p[N];
void dfs(int u) {
    sz[u] = 1;
    for (int i = 0; i < M; ++i)
        if (G[u][i]) {
            dfs(G[u][i]);
            if (sz[G[u][i]] > sz[p[u]])
                p[u] = G[u][i];
            sz[u] += sz[G[u][i]];
        }
}

void uni(int u, int v, int& s) {
    s++;
    for (int i = 0; i < M; ++i) {
        if (G[u][i] && G[v][i]) uni(G[u][i], G[v][i], s);//两边都有，递归合并
        else if (G[u][i] && !G[v][i]) G[v][i] = G[u][i];//只在 u 有，挂到 v 下
    }
}

void del(int u, int v) {
    for (int i = 0; i < M; ++i) {
        if (G[u][i] == G[v][i]) G[v][i] = 0;
        else if (G[u][i] && G[v][i]) del(G[u][i], G[v][i]);
    }
}

int sc[N], f[N];
void dfs2(int u, int h) {
    if (!sc[u]) return;//叶子，无可合并
    int sum = 1;
    for (int i = 0; i < M; ++i)
        if (G[u][i] && G[u][i] != p[u])
            uni(G[u][i], p[u], sum);//把所有非重子树合并进重子树
    f[h] += sum;
    for (int i = M-1; i >= 0; --i)
        if (G[u][i] && G[u][i] != p[u])
            del(G[u][i], p[u]);//撤销，恢复现场
    for (int i = 0; i < M; ++i)
        if (G[u][i]) dfs2(G[u][i], h+1);//递归子节点
}

int idx(char c) { return c - 'a'; }

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        char ch[2];
        cin >> u >> v >> ch;
        G[u][idx(ch[0])] = v; sc[u]++;
    }
    dfs(1); dfs2(1, 1);
    int ans = 1;
    for (int i = 2; i <= n; ++i)
        if (f[ans] < f[i]) ans = i;
    cout << n - f[ans] << '\n' << ans;
    return 0;
}