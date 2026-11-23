//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
dfs 生成欧拉序（Euler tour）‍存到 rk[1..tot]，且把节点进入和回溯都记录（tot≈2n）。
dfn[x] 是 x 首次出现的序号（欧拉时间戳），dep[x] 是深度
基于欧拉序的 RMQ 求 LCA：两点的 LCA = 欧拉序区间 [l,r] 内深度最小的那个节点。
cmp(x,y)：返回深度较小者（用于 RMQ 的 min 合并）。
st[20][N<<1] 稀疏表预处理后用 lg 快速查询区间最小值
树上距离 = 两点深度和 − 2×LCA 深度
每次询问 (k, m, r)，读入 k 个点存入 vc。然后按 k 的大小分两路：

A. 小块（k ≤ M=350）：在关键点之间的"压缩图"上做拓扑 DP
用 dis() 判断两点祖先关系：d[rt][i]+d[i][j]==d[rt][j] 表示 i 在根 rt 视角下是 j 的祖先。
据此建 DAG（祖先→后代），拓扑排序得到每个点 f[i] = 它在 DAG 中的层级（即从根到它经过的关键祖先数）。
若 rt 是原本不在集合里而临时加的，恢复时把 k 还原、并把所有 f[i] 减 1（去掉 rt 那一层）
B. 大块（k > M）：直接在原树上 DFS 算每个点深度
g[x] = 从根 r 到 x 路径上被标记（vis=1）的节点数。
大块不能 O(k²) 建图，所以直接 DFS 一遍原树，用 vis 计数，得到相同的 f[i]（每个点在以 r 为根下的祖先关键点个数）。
两种分支殊途同归：都得到数组 f[0..k-1]，表示每个关键点在"以 r 为根"视角下的祖先关键点数量
带权第二类 Stirling 数的 DP，f 数组升序排序（保证处理祖先在前）：

dp[i][j] = 前 i 个点（按祖先层级排序）分成 j 个组，且每组内无祖孙冲突的方案数。
转移：
第 i 个点新开一组：dp[i-1][j-1]（前 i-1 个点分 j-1 组）。
第 i 个点加入已有组：可选组数为 j - f[i-1]——因为它的 f[i-1] 个祖先已经占了不同的组（不能同组），所以可用组数是剩余 j - f[i-1] 组。乘上 dp[i-1][j]。
最终答案 = Σ_{i=0..m} dp[k][i]（至多 m 组）。
关键正确性：j - f[i-1] 里 f[i-1] 是该点在以 rt 为根下的祖先关键点个数，这正是"它已有多少个点在前面且必须分离"的数量

clear()：只把元素清空（size 变 0），但容量 capacity 不变，内存仍被容器持有。
vector<int>().swap(tr[i])：不但 size 变 0，容量也归 0，内存真正释放
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=0; i<n; i++)
#define rep1(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, M = 350, mod = 1e9+7;

int dep[N];
int cmp(int x, int y) { return dep[x] < dep[y] ? x : y; }

int dfn[N], lg[N<<1], st[20][N<<1];
int LCA(int x, int y) {
    int l = dfn[x], r = dfn[y];
    if (l > r) swap(l, r);
    int k = lg[r-l+1];
    return cmp(st[k][l], st[k][r-(1<<k)+1]);
}
int dis(int x, int y) { return dep[x]+dep[y]-2*dep[LCA(x,y)]; }

int rk[N<<1], tot;
vector<int> e[N];
void dfs(int x, int fa) {
    rk[dfn[x]=++tot] = x; dep[x] = dep[fa] + 1;
    for (auto v : e[x]) if (v != fa) {
        dfs(v,x);
        rk[++tot] = x;
    }
}

int g[N], vis[N];
void dfs2(int x, int fa, int h) {
    g[x] = h;
    for (auto v : e[x])
        if (v != fa) dfs2(v,x,h+vis[x]);
}

int ksm(int x, int y) {
    int s = 1;
    while (y) {
        if (y&1) s = 1ll*s*x%mod;
        x = 1ll*x*x%mod;
        y >>= 1;
    }
    return s;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

inline void ins(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }

int n, q, fac[N], inv[N], in[M+10], f[M+10], d[M+10][M+10], dp[N][310];
vector<int> tr[M+10];
int main() {
    read(n,q); fac[0] = 1;
    rep1(i,n) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[n] = ksm(fac[n],mod-2);
    for (int i = n; ~i; --i) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
    for (int i = 1, u, v; i < n; i++) {
        read(u,v); e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1,0);
    rep1(i,tot) st[0][i] = rk[i];
    for (int i = 2; i <= tot; i++) lg[i] = lg[i>>1]+1;
    rep1(i,19) for (int j = 1; j+(1<<i)-1 <= tot; j++)
        st[i][j] = cmp(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    while (q--) {
        int k, m, r; read(k,m, r);
        vector<int> vc;
        for (int i = 1, x; i <= k; i++) read(x), vc.push_back(x);
        if (k <= M) {
            int fl = 0, rt = 0;
            rep(i,k) if (vc[i] == r) fl = 1, rt = i;
            if (!fl) vc.push_back(r), rt = k++;//根 r 必须作为关键点加入
            rep(i,k) vector<int>().swap(tr[i]), in[i] = f[i] = 0;//重置小数组
            rep(i,k) for (int j = i+1; j < k; j++)//建完全图上的"祖先关系边"
                d[i][j] = d[j][i] = dis(vc[i], vc[j]);
            //若 i 是 j 的祖先（且路径经过 rt），建边 i→j，j 入度+1
            rep(i,k) rep(j,k) if (i != j && d[rt][i]+d[i][j] == d[rt][j])
                tr[i].push_back(j), ++in[j];
            //拓扑排序，f[v] = 到 v 的祖先个数层级
            queue<int> q; q.push(rt);
            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (auto v : tr[x]) {
                    --in[v];
                    if (!in[v]) { f[v] = f[x] + 1; q.push(v); }
                }
            }
            if (!fl) { --k; rep(i,k) --f[i]; }//若 rt 是临时加入的，去掉它并调整深度
        } else {
            for (auto x : vc) vis[x] = 1;
            dfs2(r,0,0);
            rep(i,k) f[i] = g[vc[i]], vis[vc[i]] = 0;
        }
        rep(i,k+1) rep(j,i+1) dp[i][j] = 0;
        dp[0][0] = 1; sort(f,f+k);
        rep1(i,k) rep(j,min(i,m)+1) {
            dp[i][j] = j ? dp[i-1][j-1] : 0;
            if (j > f[i-1]) ins(dp[i][j],1ll*dp[i-1][j]*(j-f[i-1])%mod);
        }
        int ans = 0;
        rep(i,m+1) ins(ans,dp[k][i]);
        cout << ans << '\n';
    }
    return 0;
}