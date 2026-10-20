//
// Created by Psy.C on 2026/10/20.
//
/**
以 1 为根（fa=0）。
sz[u]：u 的子树大小，初始 1，累加每个孩子的 sz[v]。
j[u]、o[u]：某种奇偶相关的组合计数。
初始 o[u] = 1（把 u 自己算作一个"偶项"），j[u]=0。
对每个孩子 v：j[u] += o[v]，o[u] += j[v]——这是深度奇偶交替累乘：
若 v 子树贡献"偶数类"到 u 变成"奇数类"，反之亦然。
因此 o[u] 统计的是：以 u 为某端点、方向朝下的路径中，终结点深度与 u 奇偶性相反（或含自身）的方案数；j[u] 是奇偶性相同部分的对应量。
dep[v] = dep[u]+1 记录深度。
翻译：o[u]、j[u] 记录以 u 为根的子树内、奇偶深度交替形成的两类计数（可理解为"黑白染色"下的两类计数，常用于统计"长度为奇的链/异色点对"）
ns 统计以 u 为"某一端点 / 分界点"的所有合法点对数量（模 mod）。
x：根据 dep[u] 奇偶，取 o[1]-o[u]+1 或 j[1]-o[u]+1——这是换根用"全树根 1 的信息 − u 子树信息"得到"u 子树之外"的那部分贡献。
若干 add/mns 把"u 内部"和"u 外部（补集）"的交叉点对数量组合成 ns。
遍历孩子 v：
先递归 dfs2(v,u)（先处理子树，再反过来用它结果——即换根的"后序"计算）。
add(ns, j[v]*(sz[u]-sz[v]-1))：用孩子的 j/o 与"u 除去该孩子以外的其余部分大小"相乘，统计跨该孩子的点对。
最后 mns(ns, 1)：减去一个自身的重复计数（把 u 自身那 1 个点对去除）。
add(ans, ns * V[u] % mod)：该点的点对数 ns 乘权值 V[u]，累加入全局答案。
翻译：dfs2 以换根方式，对每个点 u 算出"以 u 参与的合法（奇偶/异色）点对总数 ns"，再按点权 V[u] 加权求和得到最终答案 ans
读 n、点权 V、n-1 条边建无向树。
dfs(1,0) 预处理，dfs2(1,0) 计算答案。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+7, mod = 1e9+7;

int sz[N], j[N], o[N], dep[N];
vector<int> g[N];
void dfs(int u, int fa) {
    sz[u] = 1; j[u] = 0; o[u] = 1;
    for (auto v : g[u]) {
        if (v != fa) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            j[u] += o[v]; o[u] += j[v];
        }
    }
}
void add(int &x, int y) { x = (x + y + mod) % mod; }
void mns(int &x, int y) { x = (x - y + mod) % mod; }

int n, ans, V[N];
void dfs2(int u, int fa) {
    int ns = 0, x;
    if (dep[u]%2 == 0) x = o[1] - o[u] + 1;
    else x = j[1] - o[u] + 1;
    add(ns, x*sz[u]%mod);
    mns(ns, (n-sz[u]+1-x)*sz[u]%mod);
    add(ns, o[u]*(n-sz[u]+1)%mod);
    mns(ns, j[u]*(n-sz[u]+1)%mod);
    for (auto v : g[u])
        if (v != fa) {
            dfs2(v, u);
            add(ns, j[v]*(sz[u]-sz[v]-1)%mod);
            mns(ns, o[v]*(sz[u]-sz[v]-1)%mod);
        }
    mns(ns, 1);
    add(ans, ns*V[u]%mod);
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> V[i];
    for (int i = 1, u, v; i <= n-1; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, 0); dfs2(1, 0);
    cout << ans;
}

signed main() {
    fast;
    solve();
    return 0;
}