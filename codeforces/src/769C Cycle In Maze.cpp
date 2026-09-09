//
// Created by Psy.C on 2026/9/8.
//
/**
N=1e3+5：地图尺寸上限。
inf = 0x3f3f3f3f：极大值，作为"未访问"标记。
node{x,y,r}：队列元素，记录坐标和从起点过来的步数 r。
dx/dy：四个移动方向（下、左、右、上）。
dis[N][N]：记录从起点 X 到每格的最短步数。
mp[N][N]：存储地图字符

从起点 X 出发（已入队），向上下左右扩展。
只进入：边界内、不是墙 '*'、且还没访问过（dis == inf）的格子。
每进入一格就记下最短步数 dis[tx][ty] = ur+1 并入队。
最终 dis[i][j] 等于 X 到 (i,j) 的最短步数；不通的格子仍为 inf

use[] = {"D","L","R","U"}：与 dx/dy 顺序对应的方向字母（下/左/右/上），形成字典序 D < L < R < U。
dfs(x, y, r)：当前在 (x,y)，已走了 r 步。
终止条件 if (r > k)：走满 k 步，直接输出当前路径 s 并 exit(0) 结束整个程序（这是字典序优先——第一条 DFS 走出的合法路径即为字典序最小答案）。
扩展四个方向，进入条件为：边界内、非墙、且 dis[tx][ty] <= k-r+1——即从该格回到起点的最短距离，不超过剩余的步数 k-r+1，保证剩余步数足够"走回"/不浪费。
进入时把方向字母追加到 s，递归下一格

读入 n、m、k（迷宫行列数和要求的步数）。
if (k%2) { cout << "IMPOSSIBLE"; }：如果 k 是奇数，直接判无解返回——因为从 X 出发并回到 X 形成闭环，往返必然需要偶数步，奇数步不可能恰好回到起点。
双重循环读入整个地图：遇到 'X'（起点）就入队、把 dis 置 0、记录起点坐标 (sx, sy)，同时 q 已含起点。
先 bfs() 求出全图最短距离，再 dfs(sx, sy, 1) 从起点尝试构造字典序路径（从第 1 步开始）。
若 BFS 后 DFS 没能输出路径退出，最后补输出 IMPOSSIBLE
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5, inf = 0x3f3f3f3f;
struct node { int x, y, r; };
queue<node> q;
int dx[] = {1, 0, 0, -1}, dy[] = {0, -1, 1, 0}, n, m, dis[N][N];
char mp[N][N];
void bfs() {
    while (!q.empty()) {
        int ux = q.front().x, uy = q.front().y, ur = q.front().r; q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = dx[i] + ux, ty = dy[i] + uy;
            if (tx > 0 && ty > 0 && tx <= n &&
                ty <= m && mp[tx][ty] != '*' && dis[tx][ty] == inf)
                dis[tx][ty] = ur+1, q.push({.x = tx, .y = ty, .r = ur+1});
        }
    }
}

string s, use[] = {"D", "L", "R", "U"};
int k;
void dfs(int x, int y, int r) {
    if (r > k) { cout << s; exit(0); }
    for (int i = 0; i < 4; ++i) {
        int tx = dx[i] + x, ty = dy[i] + y;
        if (tx > 0 && ty > 0 && tx <= n && ty <= m &&
            mp[tx][ty] != '*' && dis[tx][ty] <= k-r+1)
            s += use[i], dfs(tx, ty, r+1);
    }
}

int sx, sy;
int main() {
    fast;
    memset(dis, 0x3f, sizeof dis);
    cin >> n >> m >> k;
    if (k%2) { cout << "IMPOSSIBLE"; return 0; }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> mp[i][j];
            if (mp[i][j] == 'X')
                q.push({i, j, 0}), dis[i][j] = 0, sx = i, sy = j;
        }
    bfs(); dfs(sx, sy, 1);
    cout << "IMPOSSIBLE";
    return 0;
}