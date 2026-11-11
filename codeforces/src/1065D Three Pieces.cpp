//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
check：判断 (x,y) 是否在棋盘内
node：状态 = 坐标 (x,y) + 当前棋子类型 z + 换棋次数 t + 当前已走到的数字 s。
f[x][y][z][t][s]：到达该状态的最少步数，未访问为 -1。
v：棋盘每个格子的数字
fm：马（骑士）8 个日字走法。
fc：车，4 个直线方向（可走任意距离）。
fx：象，4 个对角线方向（可走任意距离）
起点为数字 1 所在格。三种棋子类型（z=0,1,2）各作为一个初始状态，步数都是 0，已走数字 s=1，换棋次数 t=0。
压入队列
取出队首状态
换棋操作：站在同一格，把棋子从 z 换成 i（i≠z），步数 +1，换棋次数 t+1
马移动 8 步。若目标格数字恰好等于 s+1（下一个要走的数字），则进度 ss 增加为 s+1。
关键：ss 就是已依次走到的最新数字，这是该题的状态核心
车、象分别沿方向走 1-10 步（棋盘最大 10×10），逻辑同马
找到起点（数字1）和终点（数字 n²）的坐标。
BFS 从起点开始。
在所有到达终点且进度 s == n*n（走完所有数字）的状态里，找最少步数 ans
在达到最少步数的状态中，找最小的换棋次数 t，输出 ans 和 t。
（这里按 t 从小到大遍历，首次匹配即最小 t。）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int inf = 0x3f3f3f3f;

int n;
int check(int x, int y) {
    if (x <= n && x >= 1 && y <= n && y >= 1) return 1;
    return 0;
}
struct node { int x, y, z, t, s; };

int f[12][12][3][203][102], v[12][12];
int fm[][2] = {-2,-1,-2,1,2,-1,2,1,-1,-2,-1,2,1,-2,1,2};
int fc[][2] = {-1,0,1,0,0,1,0,-1};
int fx[][2] = {-1,-1,-1,1,1,-1,1,1};
void bfs(int x, int y) {
    queue<node> q; memset(f, -1, sizeof(f));
    f[x][y][0][0][1] = f[x][y][1][0][1] = f[x][y][2][0][1] = 0;
    q.push({x,y,0,0,1}); q.push({x,y,1,0,1}); q.push({x,y,2,0,1});
    while (!q.empty()) {
        node o = q.front(); q.pop();
        int nx = o.x, ny = o.y, z = o.z, t = o.t, s = o.s;
        rep(i,3) {
            if (i == z) continue;
            if (f[nx][ny][i][t+1][s] != -1) continue;
            f[nx][ny][i][t+1][s] = f[nx][ny][z][t][s] + 1;
            q.push({nx,ny,i,t+1,s});
        }
        if (z == 0) {
            for (const auto &i : fm) {
                int tx = nx + i[0], ty = ny + i[1], ss = s;
                if (!check(tx, ty)) continue;
                if (v[tx][ty] == ss+1) ss++;
                if (f[tx][ty][z][t][ss] != -1) continue;
                f[tx][ty][z][t][ss] = f[nx][ny][z][t][s] + 1;
                q.push({tx,ty,z,t,ss});
            }
        }
        if (z == 1) {
            for (int j = 1; j <= 10; j++) for (const auto &i : fc) {
                int tx = nx + i[0]*j, ty = ny + i[1]*j, ss = s;
                if (!check(tx, ty)) continue;
                if (v[tx][ty] == ss+1) ss++;
                if (f[tx][ty][z][t][ss] != -1) continue;
                f[tx][ty][z][t][ss] = f[nx][ny][z][t][s] + 1;
                q.push({tx,ty,z,t,ss});
            }
        }
        if (z == 2) {
            for (int j = 1; j <= 10; j++) for (const auto &i : fx) {
                int tx = nx + i[0]*j, ty = ny + i[1]*j, ss = s;
                if (!check(tx, ty)) continue;
                if (v[tx][ty] == ss+1) ss++;
                if (f[tx][ty][z][t][ss] != -1) continue;
                f[tx][ty][z][t][ss] = f[nx][ny][z][t][s] + 1;
                q.push({tx,ty,z,t,ss});
            }
        }
    }
}

int sx, sy, ex, ey, ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> v[i][j];
            if (v[i][j] == 1) sx = i, sy = j;
            if (v[i][j] == n*n) ex = i, ey = j;
        }
    bfs(sx, sy); ans = inf;
    rep(z,3) rep(t,204) if (f[ex][ey][z][t][n*n] != -1) ans = min(ans, f[ex][ey][z][t][n*n]);
    rep(t,204) rep(z,3) if (f[ex][ey][z][t][n*n] == ans) { cout << ans << ' ' << t; return 0; }
    return 0;
}