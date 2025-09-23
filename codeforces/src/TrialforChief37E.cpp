//
// Created by Psy.C on 2025/9/23.
//
/*
*n, m: 棋盘的行数和列数
M[50][50]: 用于标记每个位置属于哪个连通块
cnt: 连通块计数器
inf=1e9: 初始化为无穷大，用于记录最小步数
lev[2500]: 记录BFS遍历时每个节点的层次
tot: 当前遍历的最大层数
vv[51][51]: 存储输入的棋盘状态
color[2500]: 记录每个连通块的颜色('B'或'W')
fo[2500]: 邻接表，记录每个连通块相邻的其他连通块
q: BFS使用的队列
 *
*使用深度优先搜索标记同一颜色的连通块
如果当前位置颜色不匹配则返回
将当前位置标记为当前连通块编号
递归检查四个方向的相邻位置
 *
 *
*从连通块p开始进行广度优先搜索
初始化层次数组和队列
层次遍历所有相邻的连通块
根据起始块的颜色调整最终步数（B块要求奇数步，W块要求偶数步）
更新全局最小步数
 *
 *
 */

#include <iosfwd>
#include <iostream>
#include <set>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstdio>
#define rep(i,a) for(int i=0;i<(a);++i)
using namespace std;

int n, m, M[50][50], cnt, inf=1e9, lev[2500], tot;
char vv[51][51], color[2500];
set<int> fo[2500];
queue<int> q;

bool ok(int x, int y) { return (x >= 0 && x < n && y >= 0 && y < m); }

void dfs(int x, int y, char col) {
    if (vv[x][y] != col) return;
    M[x][y] = cnt;
    if (ok(x - 1, y) && M[x - 1][y] == 0) dfs(x - 1, y, col);
    if (ok(x + 1, y) && M[x + 1][y] == 0) dfs(x + 1, y, col);
    if (ok(x, y - 1) && M[x][y - 1] == 0) dfs(x, y - 1, col);
    if (ok(x, y + 1) && M[x][y + 1] == 0) dfs(x, y + 1, col);
}

void add(int f, int t) {
    fo[f].insert(t);
    fo[t].insert(f);
}

void bfs(int p) {
    memset(lev, 0, sizeof(lev));
    tot = 1;
    while (!q.empty()) q.pop();
    q.push(p);
    lev[p] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (set<int>::iterator it = fo[u].begin(); it != fo[u].end(); ++it) {
            int v = *it;
            if (lev[v] == 0) {
                lev[v] = lev[u] + 1;
                tot = max(tot, lev[v]);
                q.push(v);
            }
        }
    }
    tot--;
    if (color[p] == 'B' && tot % 2 == 0) tot++;
    if (color[p] == 'W' && tot % 2 == 1) tot++;
    inf = min(inf, tot);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    scanf("%d%d", &n, &m);

    rep (i, n) scanf("%s", &vv[i]);
    rep (i ,n)
        rep (j, m) {
            if (M[i][j] == 0) {
                ++cnt;
                dfs(i, j, vv[i][j]);
            }
        }
    rep (i, n)
        rep (j, m) {
            color[M[i][j]] = vv[i][j];
            if (ok(i - 1, j) && M[i - 1][j] != M[i][j]) add(M[i - 1][j], M[i][j]);
            if (ok(i + 1, j) && M[i + 1][j] != M[i][j]) add(M[i + 1][j], M[i][j]);
            if (ok(i, j - 1) && M[i][j - 1] != M[i][j]) add(M[i][j - 1], M[i][j]);
            if (ok(i, j + 1) && M[i][j + 1] != M[i][j]) add(M[i][j + 1], M[i][j]);
        }

    for (int i = 1; i <= cnt; ++i) bfs(i);
    cout << inf << '\n';
    return 0;
}