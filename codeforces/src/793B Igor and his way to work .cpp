//
// Created by Psy.C on 2026/9/15.
//
/**
n×m 网格，S 起点，T 终点，* 是障碍。
每次可向上下左右移动一格。
限制：总共最多只能转 2 次方向（直走随便走，但方向一改变就算一次"转弯"）。
问能否从 S 到达 T
(x,y) 坐标
di：当前朝向（0=右,1=上,2=左,3=下，对应 dx/dy）
dis：到目前为止已经转向的次数
这比普通 BFS 多维护了方向和转次数两个维度，用来限制"最多转 2 次"
从起点出发，四个方向都作为初始朝向入队（这样最开始的直走不算"转方向"），转向次数 dis 初始为 0
对每个弹出的状态：

若已转超过 2 次，直接跳过（不再扩展）。
枚举四个方向 i：
nd = (i==p.di ? 0 : 1) + p.dis —— 若方向不变则转弯数不变（+0），方向改变则转弯数 +1。
若新格子在界内、未访问过、且不是障碍，则标记并入队。
这样 BFS 保证在固定转弯次数上限下能到终点即可
终点 T：只要四个方向里任意一个，其转弯次数为 0/1/2 之一被访问到（即转弯不超过 2 次能到达），就返回 YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+10;

struct node { int x, y, di, dis; };

int n, m;
int f(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

queue<node> q;
int vis[N][N][4][11], dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0}, ex, ey;
char a[N][N];
string bfs(int x, int y) {
    for (int i = 0; i < 4; ++i) {
        q.push({.x = x, .y = y, .di = i, .dis = 0});
        vis[x][y][i][0] = 1;
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        if (p.dis > 2) continue;
        for (int i = 0; i < 4; ++i) {
            int nx = dx[i] + p.x, ny = dy[i] + p.y, nd = (i==p.di?0:1)+p.dis;
            if (f(nx, ny) && !vis[nx][ny][i][nd] && a[nx][ny] != '*') {
                vis[nx][ny][i][nd] = 1;
                q.push({.x = nx, .y = ny, .di = i, .dis = nd});
            }
        }
    }
    for (int i = 0; i < 4; ++i)
        if (vis[ex][ey][i][0] || vis[ex][ey][i][1] || vis[ex][ey][i][2])
            return "YES";
    return "NO";
}

int sx, sy;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 'S') sx = i, sy = j;
            if (a[i][j] == 'T') ex = i, ey = j;
        }
    }
    cout << bfs(sx, sy);
    return 0;
}