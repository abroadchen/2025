//
// Created by Psy.C on 2026/9/5.
//
/**
occ[N]：存储每个节点子树中所有节点的编号集合，以位掩码形式保存。
fa[N]：存储每个节点在树中的父节点编号。
T[N]：邻接表，存储第一棵树的边信息
遍历树 T，计算每个节点子树中包含的节点集合 occ。
步骤：
初始化当前节点 u 的集合为仅包含自身（1 << (u-1)）。
记录父节点 fa[u] 为 f。
对于每个相邻节点 v（若不是父节点），递归调用 dfs(v, u)。
将子节点 v 的集合与当前集合进行按位或合并（|=），得到完整的子树集合

第一个维度 N：表示根节点编号（以该节点为根）。
第二个维度 M：表示子集掩码（即哪些颜色/编号已经被使用）。
第三个维度 13：表示当前根节点的颜色编号（范围
[
1
,
m
]
[1,m]）。
m：第二棵树中的节点数量。
ans：最终答案累计器。
G[N]：邻接表，存储第二棵树的边信息。
vc[N]：用于记录特定约束的向量，其中 vc[i] 存储与节点 i 相连的 (相连节点, 掩码) 对

初始化：对于每个可能的颜色 i，将只包含该颜色的状态设为 1。
递归遍历：对每个子节点 v 执行 dfs2。
状态转移：
从大到小枚举当前节点的子集掩码 S。
枚举当前根节点的颜色 i（要求 i 在 S 中）。
遍历 vc[i] 中的约束 (tt, mask)
tt：相连节点的颜色。
s：mask 与 S 的交集。
检查 s 是否包含 tt 对应的位。
使用乘法原理累加 DP 值：dp[u][S][i] += dp[u][S-s][i] * dp[v][s][tt]。
答案累计：遍历完后，将根节点 u 包含所有颜色的状态加到 ans 中
dfs3 与 dfs2 类似，但遍历的是第一棵树 T。
最终结果累计到变量 dv 中，而不是 ans

输入读取：
n：第一棵树的节点数。
接下来读取 n-1 条边，构建第二棵树 G（注意顺序）。
m：第二棵树的节点数。
再读取 m-1 条边，构建第一棵树 T。
DFS 处理：
dfs(1, 0)：计算第一棵树 T 的子树集合 occ 和父节点 fa。
遍历 T 的每条边，填充约束向量 vc：
如果是父子关系，则使用反向集合 (1<<m)-1-occ[u]。
否则直接使用子树集合 occ[v]。
DP 计算：
dfs2(1, 0)：基于第二棵树 G 计算答案 ans。
memset(dp, 0, sizeof dp)：重置 DP 表。
dfs3(1, 0)：基于第一棵树 T 计算辅助值 dv。
输出结果：
最终答案为 ans / dv（模意义下），即 ans * dv^(mod-2) % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ll long long
using namespace std;
constexpr int N = 1e3+5, M = (1<<12)+10, mod = 1e9+7;

int occ[N], fa[N];
vector<int> T[N];
void dfs(int u, int f) {
    occ[u] = 1<<(u-1), fa[u] = f;
    for (auto v : T[u])
        if (v != f)
            dfs(v, u), occ[u] |= occ[v];
}

int dp[N][M][13], m, ans;
vector<int> G[N];
vector<ii> vc[N];
void dfs2(int u, int f) {
    for (int i = 1; i <= m; ++i) dp[u][1<<(i-1)][i] = 1;
    for (auto v : G[u]) {
        if (v == f) continue;
        dfs2(v, u);
        for (int S = (1<<m)-1; S >= 0; --S) {
            for (int i = 1; i <= m; ++i) if (S&(1<<(i-1)))
                for (auto pr : vc[i]) {
                    int tt = pr.first, s = pr.second&S;
                    if (!(s&(1<<(tt-1)))) continue;
                    dp[u][S][i] = (dp[u][S][i]+1ll*dp[u][S-s][i]*dp[v][s][tt])%mod;
                }
        }
    }
    for (int i = 1; i <= m; ++i) ans = (ans + dp[u][(1<<m)-1][i])%mod;
}

int dv;
void dfs3(int u, int f) {
    for (int i = 1; i <= m; ++i) dp[u][1<<(i-1)][i] = 1;
    for (auto v : T[u]) {
        if (v == f) continue;
        dfs3(v, u);
        for (int S = (1<<m)-1; S >= 0; --S) {
            for (int i = 1; i <= m; ++i) if (S&(1<<(i-1)))
                for (auto pr : vc[i]) {
                    int tt = pr.first, s = pr.second&S;
                    if (!(s&(1<<(tt-1)))) continue;
                    dp[u][S][i] = (dp[u][S][i]+1ll*dp[u][S-s][i]*dp[v][s][tt])%mod;
                }
        }
    }
    for (int i = 1; i <= m; ++i) dv = (dv+dp[u][(1<<m)-1][i])%mod;
}

ll pw(ll b, int p) {
    ll ans = 1;
    while (p) {
        if (p&1) ans = ans*b%mod;
        b = b*b%mod, p>>=1;
    }
    return ans;
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i <= n-1; ++i) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    cin >> m;
    for (int i = 1, u, v; i <= m-1; ++i) {
        cin >> u >> v;
        T[u].push_back(v); T[v].push_back(u);
    }
    dfs(1, 0);
    for (int u = 1; u <= m; ++u) for (auto v : T[u]) {
        if (v == fa[u]) vc[u].emplace_back(v, (1<<m)-1-occ[u]);
        else vc[u].emplace_back(v, occ[v]);
    }
    dfs2(1, 0), memset(dp, 0, sizeof dp), dfs3(1, 0);
    cout << 1ll*ans*pw(dv, mod-2)%mod;
    return 0;
}