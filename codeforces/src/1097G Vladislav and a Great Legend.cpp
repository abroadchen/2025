//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
N = 1e5+5（点数），M = 205（k 上界），mod = 1e9+7。
sz[u]：u 子树大小。
f[u][i]：u 子树内的 DP 数组，f[u][i] = 在以 u 为根的子树里做某种选择后、已形成 i 个"组/块" 的方案数（模 mod）。
g[i]：临时备份（见下），ans[i]：整棵树最终"恰好 i 个块"的方案数。
G[u]：邻接表
初始 f[u][0]=1：单个点看作已有一个集合。
每合并一个邻居子树 v，先把合并前的 f[u] 存到 g（因为下面要同时用到新旧值）。
合并 v 时，树上一条边 (u,v) 有两种选择：
(1) 边被"断开" / v 自成一组或与 u 分属不同块
直接把 v 子树的 f[v][i] 并进来（块数不变，边不合并成同一连通块）
2) 边把 u 与 v 的某块连成一块（块数 +1 但本身算一块）：
这表示"v 里的某一组与 u 合并"发生的转移。
真正的多项式卷积部分（合并 v 前的旧状态 g × v 的新状态 f[v]）
这里 g 与 f[v] 卷积，两种"边状态"分别生成 +0 和 +1 的块数增量，对应"边断开"和"边连接"两种形态，是 0/1 二态卷积。
ans[i] 同步累加所有"恰好 i 块"的出现次数，用于最后回答。
sz 上限裁剪： 用 min(k, sz-1)、min(k-i, sz[v]-1) 等把卷积限制在 k 内、且保证每侧至少留 1 个元素可组成新块，正确控制复杂度到
O(nk)。

组合计数收尾（solve 里）：

s[i][j] 是第二类斯特林数（s[i][j] = j·s[i-1][j] + s[i-1][j-1]），表示把 i 个对象分成 j 个非空集合的方案数【这里用它的递推正是斯特林数递推式】。
最后：
整棵树能被"恰好 i 组"覆盖的方式有 ans[i] 种，而把这 i 组再 "给 k 个不同标签/颜色" 分块，方案数是
i!⋅S(k,i)（先把 k 个对象划分成 i 个非空组，再给 i 组排序配对）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<=n; ++i)
#define rep1(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e5+5, M = 205, mod = 1e9+7;

int sz[N], f[N][M], k, g[M], ans[M];
vector<int> G[N];
void dfs(int u, int fa) {
    sz[u] = 1, f[u][0] = 1;
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        rep(i,min(k,sz[u]-1)) g[i] = f[u][i];
        rep(i,min(k,sz[v])) {
            (f[u][i] += f[v][i]) %= mod;
            (f[u][i+1] += f[v][i]) %= mod;
        }
        rep(i,min(k,sz[u]-1)) rep(j,min(k-i,sz[v]-1)) {
            int w = 1ll*g[i]*f[v][j]%mod;
            //边断开：i+j 块  边合并成一块：i+j+1 块
            (f[u][i+j] += w) %= mod; (f[u][i+j+1] += w) %= mod;
            (ans[i+j] += w) %= mod; (ans[i+j+1] += w) %= mod;
        }
        sz[u] += sz[v];
    }
}

int n, s[M][M];
void solve() {
    cin >> n >> k;
    rep1(i,n-1) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    s[0][0] = 1;
    rep1(i,k) rep1(j,i) s[i][j] = (1ll*j*s[i-1][j]+s[i-1][j-1])%mod;
    dfs(1,0);
    int res = 0, fc = 1;
    rep1(i,k) {
        fc = 1ll*fc*i%mod;
        (res += 1ll*fc*s[k][i]%mod*ans[i]%mod) %= mod;
    }
    cout << res << '\n';
}


int main() {
    fast;
    solve();
    return 0;
}