//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
p：记录每个要画的十字（中心坐标 x,y，大小 w），最多 N*N 个。
g：网格字符数组（* / .）。
n,m：网格行列
dfs 不是标准"四方向"，而是朝单一方向 w 一直走到底，统计这一条直线上连续 * 的格子数：

越界或遇到 . → 返回 0。
w==1：往上（x-1），递归加 1。
w==2：往下（x+1）。
w==3：往左（y-1）。
w==4：往右（y+1）。
返回值 = 从 (x,y) 出发朝方向 w 连续 * 的数量（包含起点）。函数末尾没有 return，但四个分支都会 return，只要 g[x][y]!='.' 且未越界，必中一支，故不会落空
dfs2 从中心 (x,y) 朝单一方向 d 标记 vis，长度限制为 w：

越界 / 遇到 . / w==0（已到长度上限）→ 返回。
否则把当前格 vis[x][y]=1（标记为"已覆盖"）。
沿方向 d 递归，w-1（长度递减）。
作用是：把一个以 (x,y) 为中心、向方向 d 延伸 w 格的直线段全部标记覆盖
对每个 * 格子：

s,z,x,y = 从该点向上、左、下、右四个方向的连续 * 长度。
mn =  四者的最小值：这决定了以 (i,j) 为中心的十字最大能画多大（须四面都至少有 mn 格，否则会覆盖到 .）。
若 mn > 1（至少半径为 1，是一个真正的十字而非单个点）：
记录一个十字 p[++cnt] = {i,j, mn-1}（半径 mn-1）。
rep(k,4)（k=1..4）调用 dfs2(i,j,mn,k) 分别向四个方向各标记 mn 格为已覆盖。
也就是说：对每个可作为十字中心的格子，用其最大可能半径画十字，并把覆盖范围标记进 vis
若存在某个 * 格子 vis[i][j]==0（从未被任何十字覆盖）→ 输出 -1 结束，表示无法用十字覆盖全部 *。
记录 flg 表示网格中是否有 *。
若 cnt==0（没画出任何十字）但网格里确实有 *（flg==1）→ 也输出 -1（有 * 却没画出任何十字，不可能覆盖）。
否则输出十字数量 cnt
输出每个记录的中心 (x,y) 和半径 w
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e3+5;

struct node { int x, y, w; } p[N*N];

int n, m;
char g[N][N];
int dfs(int x, int y, int w) {
    if (x < 1 || x > n || y < 1 || y > m || g[x][y] == '.') return 0;
    if (w == 1) return dfs(x-1,y,1) + 1;
    if (w == 2) return dfs(x+1,y,2) + 1;
    if (w == 3) return dfs(x,y-1,3) + 1;
    if (w == 4) return dfs(x,y+1,4) + 1;
}

int vis[N][N];
void dfs2(int x, int y, int w, int d) {
    if (x < 1 || x > n || y < 1 || y > m || g[x][y] == '.' || w == 0) return;
    vis[x][y] = 1;
    if (d == 1) dfs2(x-1,y,w-1,1);
    if (d == 2) dfs2(x+1,y,w-1,2);
    if (d == 3) dfs2(x,y-1,w-1,3);
    if (d == 4) dfs2(x,y+1,w-1,4);
}

int cnt;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> g[i][j];
    rep(i,n) rep(j,m) {
        if (g[i][j] == '.') continue;
        int s = dfs(i,j,1), x = dfs(i,j,2);
        int z = dfs(i,j,3), y = dfs(i,j,4);
        int mn = min(min(s, z), min(x, y));
        if (mn > 1) {
            p[++cnt] = {i,j,mn-1};
            rep(k,4) dfs2(i,j,mn,k);
        }
    }
    bool flg = 0;
    rep(i,n) rep(j,m) {
        if (g[i][j] == '*' && vis[i][j] == 0) { cout << -1; return 0; }
        if (g[i][j] == '*') flg = 1;
    }
    if (cnt == 0 && flg == 1) { cout << -1; return 0; }
    cout << cnt << '\n';
    rep(i,cnt) cout << p[i].x << ' ' << p[i].y << ' ' << p[i].w << '\n';
    return 0;
}