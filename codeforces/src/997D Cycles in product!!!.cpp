//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
e[N<<1]：邻接表，因为无向边要存两份；N=4005。
f[M][N]、g[M][N]：M=80，即 m ≤ 80。f[i][v]、g[i][v] 存"长度为 i 的某种路径数量"。
ans[M]：最终每棵树按长度统计的路径数。
vis：点分治中标记已删除（选为重心）的点
经典树的重心：使删掉该点后剩余最大连通块最小
把当前连通块的所有点按 DFS 序收集到 a[1..tot]，并算好各子树大小 sz
这里 f、g 是长度 i 的路径计数的 DP。g[i][y] 表示"从 y 出发、在整个当前连通块内、长度为 i 的路径数"；f[i][y] 限制在 y 的子树内（即不经过重心 x 的路径）。
转移 g[i][y] += g[i-1][邻接点]：从邻接点长度 i-1 的路径延长一步到 y
对重心 x 本身：把 g[j][x]（以 x 为一端的路径）计入 ans[j]。
对非重心点 y：用两段路径拼接——f[j][y]（y 子树内向下的路径）与 g[k][y]（y 出发全连通块的路径）卷起来形成一条新路径，长度 j+k，计入 ans[j+k]。
f（子树内路径）与 g（全块路径）区分开，目的是避免同一路径被重复计数（不经过重心的路径只在子问题里算，经重心的路径由拼接得到）
这就是标准点分治：删重心后对每个子树连通块递归处理，保证总复杂度 O(N log N)。

solve()：sum=n; rt=0; get_rt(1,0); calc(rt); —— 从整棵树开始
阶乘/逆元：inv[i] = (mod-mod/i)*inv[mod%i]%mod 是线性求逆元公式（mod 为质数），再乘前缀得到阶乘逆元，供组合数用。

读入两棵树的所有边。

solve() 各跑一遍点分治。

合并：s = Σ_i t1.ans[i] * t2.ans[m-i] * C(m,i)。这是把第一条树的长度为 i 的路径、与第二条树长度为 (m-i) 的路径配对，路径内部顺序固定，但两段路径之间（或整体的 m 个"选择单位"）用二项式系数 C(m,i) 分配 —— 相当于把 m 个东西拆成 i 和 m-i 两份分别交给两棵树。

这本质上是一个卷积搭配组合方案：枚举第一棵路径长度 i，剩下的 m−i 给第二棵，再用 C(m,i) 计入"哪些单位给第一棵"的选择数
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i = 1; i <= n; i++)
#define f0(i,j) for(int i=0; i < j; i++)
#define ll long long
using namespace std;

constexpr int N = 4e3+5, M = 80, mod = 998244353;

int m;
struct node {
    struct edge { int to, nxt; } e[N<<1];
    int cnt, head[N], sz[N], w[N], sum, rt, a[N], tot, f[M][N], g[M][N], ans[M], n;
    bool vis[N];
    void add(int u, int v) {
        e[++cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
        e[++cnt].to = u; e[cnt].nxt = head[v]; head[v] = cnt;
    }
    void get_rt(int x, int fa) {
        sz[x] = 1; w[x] = 0;
        for (int i = head[x]; i; i = e[i].nxt) {
            if (e[i].to == fa || vis[e[i].to]) continue;//邻接点是父节点或已被删除
            get_rt(e[i].to, x);
            sz[x] += sz[e[i].to];
            w[x] = max(w[x], sz[e[i].to]);
        }
        w[x] = max(w[x], sum-sz[x]);
        if (!rt || w[x] < w[rt]) rt = x;//取"最大子树最小"的点为重心
    }
    void get(int x, int fa) {
        a[++tot] = x; sz[x] = 1;
        for (int i = head[x]; i; i = e[i].nxt) {
            if (e[i].to != fa && !vis[e[i].to])
                get(e[i].to, x), sz[x] += sz[e[i].to];
        }
    }
    void calc(int x) {
        tot = 0; get(x, 0);//收集以 x 为根的当前连通块全部点
        rep(i,tot) f[0][a[i]] = 0;//长度 0 的清零
        f[0][x] = g[0][x] = 1;//空路径：从重心出发长度 0 的路径=1
        rep(i,m) rep(j,tot) {
            int y = a[j]; f[i][y] = g[i][y] = 0;
            for (int k = head[y]; k; k = e[k].nxt) {
                if (vis[e[k].to]) continue;//跳过已删点
                (g[i][y] += g[i-1][e[k].to]) %= mod;//g：所有子树路径计数
                if (y != x) (f[i][y] += f[i-1][e[k].to]) %= mod;//f：仅子树的路径计数
            }
        }
        rep(i,tot) {
            int y = a[i];
            if (y == x) {
                f0(j,m+1) (ans[j] += g[j][x]) %= mod;
                continue;
            }
            f0(j,m+1) f0(k,m-j+1) (ans[j+k] += (ll)f[j][y]*g[k][y]%mod) %= mod;
        }
        vis[x] = 1;//删除重心
        for (int i = head[x]; i; i = e[i].nxt) {
            if (vis[e[i].to]) continue;
            rt = 0; sum = sz[e[i].to];
            get_rt(e[i].to, x);//在子连通块里找新重心
            calc(rt);//递归处理
        }
    }
    void solve() { sum = n; rt = 0; get_rt(1, 0); calc(rt); }
} t1, t2;

int jc[M], inv[M];
int C(int n, int m) { return (ll)jc[n]*inv[m]%mod*inv[n-m]%mod; }
int main() {
    scanf("%d%d%d", &t1.n, &t2.n, &m);
    jc[0] = jc[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i <= m; i++) jc[i] = (ll)jc[i-1]*i%mod, inv[i] = (ll)(mod-mod/i)*inv[mod%i]%mod;
    for (int i = 2; i <= m; i++) inv[i] = (ll)inv[i-1]*inv[i]%mod;
    for (int i = 1, x, y; i < t1.n; i++) { scanf("%d%d", &x, &y); t1.add(x, y); }
    for (int i = 1, x, y; i < t2.n; i++) { scanf("%d%d", &x, &y); t2.add(x, y); }
    t1.solve(); t2.solve();//各自点分治得到 t1.ans[], t2.ans[]
    int s = 0;
    for (int i = 0; i <= m; i++) (s += (ll)t1.ans[i]*t2.ans[m-i]%mod*C(m,i)%mod) %= mod;
    printf("%d", s);
    return 0;
}