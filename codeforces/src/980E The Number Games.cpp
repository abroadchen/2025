//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
fa[u][i]：u 的 2^i 级祖先（树上倍增）。
dep[u]：深度。
G[u]：邻接表。
vis[u]：u 是否被"选中/访问"（1=选中）。
ans：最终未选中的节点集合（从小到大输出）
以 n 为根（dfs(n,0)），每个节点记录父节点和深度，并预处理 2^i 级祖先（LCA/倍增表，最多 20 层，覆盖 1e6 规模）。
可确证：以 n 为根的 DFS，预处理倍增祖先表 fa[·][0..20] 和深度
注：代码里 dist 第一行 int x=u; 之后 u 被循环改写，最后 dep[x]-dep[u] 用最早保存的 x 计算。但该版本里"若 vis[u] 直接 return 0"。循环把 u 尽量向上提到一个未访问祖先，再取 u 的父节点，返回 x 与 u 的深度差
update(u)：从 u 向上沿父指针，把一路上未 vis 的节点全部标记为 1，直到碰到已 vis 的祖先为止
n-k：题目要求最终未选节点数至少为 k（或恰好 k）。已选节点数 cnt。
对每个 i（从大到小），dist(i) 是从 i 向上到最近已选祖先之间未访问节点的个数（即若选择 i，会新增多少个已选节点）。
若选上 i 后已选总数仍 ≤ n-k（即有足够节点剩下当"未选点"），则选中 i（update 标记路径）；否则 i 进 ans（成为未选点）。
最终输出所有未选点，升序
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; i++)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; i--)
using namespace std;

constexpr int N = 1e6+10;

int fa[N][21], dep[N];
vector<int> G[N];
void dfs(int u, int f) {
    fa[u][0] = f, dep[u] = dep[f] + 1;
    rep(i,1,20) fa[u][i] = fa[fa[u][i-1]][i-1];
    for (auto v : G[u]) if (v != f) dfs(v, u);
}

int vis[N];
int dist(int u) {
    int x = u;
    if (vis[u]) return 0;
    per(i,20,0) if (fa[u][i] && !vis[fa[u][i]]) u = fa[u][i];
    return u = fa[u][0], dep[x] - dep[u];
}
void update(int u) { while (vis[u] == 0) vis[u] = 1, u = fa[u][0]; }

int n, k, u, v, cnt;
vector<int> ans;
int main() {
    fast;
    cin >> n >> k;
    rep(i,1,n-1) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(n, 0); vis[n] = 1, cnt = 1;
    per(i,n-1,1) {
        if (cnt+dist(i) <= n-k) cnt += dist(i), update(i);
        else ans.push_back(i);
    }
    ranges::sort(ans);
    for (auto x : ans) cout << x << ' ';
    return 0;
}