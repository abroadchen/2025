//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
mtx[i][j]：第 i 个序列的第 j 个元素（i ∈ [0,n)，j ∈ [0,m)）。
len[i][j]：序列 i 与 序列 j 作为相邻时的"差异" —— 定义为两序列逐位对齐的差绝对值的最小值：min_k |mtx[i][k] - mtx[j][k]|。
u[i][j]：序列 i 与 序列 j 作为首尾相接（跨越边界）‍时的差异 —— min_{k=1..m-1} |mtx[i][k]-mtx[j][k-1]|（错位一格，对应环的收尾衔接）。
dp[S][i][j]：状态压缩 DP。S 是已访问点集合（bitmask），i 是路径起点，j 是当前路径终点。其值为"已形成从 i 到 j、恰好覆盖 S 中所有点的路径上，所有相邻差异的最小值（我们要最大化它）"。
v[S][i][j]：布尔表，标记状态 (S,i,j) 是否已可达。
inf：极大值，用于"最大化最小值"时的初始上界。
读入 n 个序列，每个 m 个元素。
只有一个序列时，环退化成"本身首尾相接"。
逐项求相邻元素差，答案就是其中最小值：ans = min_i |mtx[0][i]-mtx[0][i-1]|。
输出该最小值
对每个点 i，状态 S = 1<<i（只含 i 一个点），起点 = 终点 = i，标记为可达。
解释：路径只有 i 一个点，起点终点都是它
对任意两序列 i、j：
i==j：自身差异为 0。
len[i][j]：遍历每个位置 k，取 |mtx[i][k]-mtx[j][k]| 的最小值。这是 i、j 在路径中"正常相邻"（同列对齐）时的"相邻相似度"。
u[i][j]：遍历 k=1..m-1，取 |mtx[i][k]-mtx[j][k-1]| 的最小值。这是 i 后接 j 时"错位一位"（i 的第 k 列对 j 的第 k-1 列）的衔接差异，用于环收尾的那一对衔接。
两个都用 min，因为"最大化所有相邻差异的最小值"，需要知道每对相邻能保证的最小差异
遍历所有状态集合 i：
先数出 cnt = S 中 1 的个数（当前已选点数）。
遍历所有可达状态 (i, j, k)（j=起点，k=当前终点）。
对每个未访问的点 l：
res = i + (1<<l)，新集合（加入 l）。
标记 v[res][j][l] = 1（新状态可达，起点不变 j，终点变为 l）。
转移 dp（更新"路径上相邻差异的最小值"）：
cnt == 1（即当前只有起点一个点）：新路径就是 k -> l，只有一对相邻，差异直接是 len[k][l]，取 dp[res][j][l] = max(.., len[k][l])（因为我们要最大这个值）。
cnt > 1：扩展路径时，新加入的相邻 (k,l) 差异为 len[k][l]，要与已有路径的最小值 dp[i][j][k] 再取 min，得到扩展后整条路径的"最小差异"，再对外层 max（对所有到达该状态的方式取最优）。
本质：这是 HamPath 的"最大化路径中最小边权" DP。每个 dp[S][j][k] 存"从 j 出发、以 k 结束、覆盖 S、路径上最小相邻差异的最大可能值"。
全部点都访问完的状态是 (1<<n)-1（mask 全 1）。
对任意 起点 i、终点 j（i≠j）：
要把路径首尾合成环：闭环那对相邻是 i 与 j，但 i 是起点、j 是终点，它们相接时是"错位一位"的衔接，差异用 u[i][j]（而不是 len）。
所以把整个路径的最小差异限制一下：dp = min(dp, u[i][j])（新增这对闭环相邻，也作为"最小差异"的约束）。
用 ans = max(ans, ...) 在所有可能的起点/终点组合中取最大值
输出最大的"路径最小相邻差异"。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;
constexpr int N = 1e4+5, M = 20;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
ll mtx[M][N], len[M][M], u[M][M], dp[1<<16][M][M];
bool v[1<<16][M][M];
int main() {
    fast;
    int n, m; cin >> n >> m;
    rep(i,n) rep(j,m) cin >> mtx[i][j];
    if (n == 1) {
        ll ans = inf;
        for (int i = 1; i < m; i++) ans = min(ans, abs(mtx[0][i]-mtx[0][i-1]));
        cout << ans << '\n';
        return 0;
    }
    rep(i,n) v[1<<i][i][i] = 1;
    rep(i,n) rep(j,n) {
        if (i == j) { len[i][j] = 0; continue; }
        ll t = inf;
        rep(k,m) t = min(t, abs(mtx[i][k]-mtx[j][k]));
        len[i][j] = t; t = inf;
        for (int k = 1; k < m; k++) t = min(t, abs(mtx[i][k]-mtx[j][k-1]));
        u[i][j] = t;
    }
    rep(i,1<<n) {
        int cnt = 0, S = i;
        while (S) {
            if (S%2) ++cnt;
            S/=2;
        }
        rep(j,n) rep(k,n) {
            if (!v[i][j][k]) continue;
            rep(l,n) {
                if (i&(1<<l)) continue;
                int res = i+(1<<l);
                v[res][j][l] = 1;
                if (cnt == 1) dp[res][j][l] = max(dp[res][j][l], len[k][l]);
                else dp[res][j][l] = max(dp[res][j][l],min(dp[i][j][k],len[k][l]));
            }
        }
    }
    ll ans = 0;
    rep(i,n) rep(j,n) {
        if (i == j) continue;
        dp[(1<<n)-1][i][j] = min(dp[(1<<n)-1][i][j],u[i][j]);
        ans = max(ans, dp[(1<<n)-1][i][j]);
    }
    cout << ans << '\n';
    return 0;
}