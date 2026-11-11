//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
x, y：坐标；
r（right）：已向右走的次数；
s（... 此处是 s 但按代码语义其实是"向左"的次数，对应 ds 数组）。
注意：代码里字段名 s 与字符串数组 s[N][N] 重名，但 node.s 是整型字段、不影响
方向组合 (dx[i], dy[i]) 对应：

(-1,0) 上：dr=0, ds=0（不消耗左右次数）
(0,1) 右：dr=1, ds=0（右移次数 +1）
(0,-1) 左：dr=0, ds=1（左移次数 +1）
(1,0) 下：dr=0, ds=0
所以 dr 表示该方向消耗"向右"配额、ds 表示消耗"向左"配额。上下移动免费，左右移动各有限额
剪枝条件（跳过该状态）：

t[a.x][a.y] <= a.r：该格已被更少右移次数的路径访问过，不再扩张；
a.r > x：向右次数超过限制 x；
a.s > y：向左次数超过限制 y；
s[a.x][a.y] != '.'：当前位置是障碍物。
访问统计：if (t[a.x][a.y] == inf) ans++ 记录第一次访问到的新格子。
松弛记录：t[a.x][a.y] = a.r 记录到达该格的最少右移次数（用于剪枝比较）。
扩展：向四个方向推进，更新 r、s 后入队

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e3+5, inf = 1e9;

struct node { int x, y, r, s; } a, b;


int n, m, r, c, x, y, t[N][N], ans;
int dx[] = {-1,0,0,1}, dy[] = {0,1,-1,0}, dr[] = {0,0,1,0}, ds[] = {0,1,0,0};
char s[N][N];
queue<node> q;
int main() {
    fast;
    cin >> n >> m >> r >> c >> x >> y;
    rep(i,n) rep(j,m) { cin >> s[i][j]; t[i][j] = inf; }
    a.x = r, a.y = c, a.r = 0, a.s = 0; q.push(a);
    while (!q.empty()) {
        a = q.front(); q.pop();
        if (t[a.x][a.y] <= a.r || a.r > x || a.s > y || s[a.x][a.y] != '.') continue;
        if (t[a.x][a.y] == inf) ans++;
        t[a.x][a.y] = a.r;
        for (int i = 0; i < 4; i++) {
            b.x = a.x + dx[i], b.y = a.y + dy[i];
            b.r = a.r + dr[i], b.s = a.s + ds[i];
            q.push(b);
        }
    }
    cout << ans;
    return 0;
}