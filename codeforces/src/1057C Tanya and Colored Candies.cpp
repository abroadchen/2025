//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
N=110：糖果数上限
M=3010：f 第二维上限，对应"累计能量 j"的最大值（可设到 3000 左右）
inf=0x3f3f3f3f："无限大"，用于初始化和表示不可达
f[i][j]：停在糖果 i、累计获得能量为 j 时，最少的花费步数
r[N] 能量，col[N] 颜色
初始化：在起点 s，第一次先走到糖果 i（花费 abs(i-s)），收集它得到 r[i] 能量。所以状态 (i, 能量=r[i]) 的初始步数就是 abs(i-s)
外层枚举当前累计能量 j（从 1 到 m+50）
中层枚举当前所在糖果 i
内层枚举要去的下一个糖果 k
转移条件：col[i] != col[k]（颜色不同）且 r[i] < r[k]（能量严格递增）——完全符合移动规则
转移式：
f[k][j + r[k]] = min(旧值, f[i][j] + abs(i-k))
从 (i, j) 走到 k，额外花 abs(i-k) 步，落在 k 上累计能量变为 j + r[k]
这本质是一个 DAG 上的最短路径 DP：能量 j 单调递增，所以按 j 从小到大不会产生循环依赖。
只要累计能量 ≥ m 就算达成目标，所以对每个 i，在 j = m .. m+50 这一段（能量达标且还没溢出 M 的范围）里找最小步数
m+50 是给"目标值 m 附近"留一点缓冲，避免恰好不达标
若任何达标状态都不可达（ans 仍是 inf）输出 -1，否则输出最小步数
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 110, inf = 0x3f3f3f3f, M = 3010;

int n, s, m, r[N], f[N][M];
char col[N];
int main() {
    scanf("%d%d%d",&n,&s,&m);
    rep(i,n) scanf("%d",&r[i]);
    scanf("%s", col+1); memset(f, 0x3f, sizeof f);
    rep(i,n) f[i][r[i]] = abs(i-s);
    rep(j,m+50) rep(i,n) rep(k,n) if (col[i] != col[k] && r[i] < r[k])
        f[k][j+r[k]] = min(f[k][j+r[k]], f[i][j]+abs(i-k));
    int ans = inf;
    rep(i,n) for (int j = m; j <= m+50; j++)
        if (f[i][j] < ans) ans = f[i][j];
    if (ans == inf) cout << "-1\n"; else cout << ans << '\n';
    return 0;
}