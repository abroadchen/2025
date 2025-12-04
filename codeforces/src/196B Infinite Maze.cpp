//
// Created by Psy.C on 2025/12/3.
//
/*
*n, m: 地图的行数和列数
sx, sy: 起点'S'的坐标
dt[4][2]: 方向数组，表示四个方向：右(0,1)、左(0,-1)、下(1,0)、上(-1,0)
 *
 *使用(value % size + size) % size确保结果为正数
 *
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2000
#define inf 0x3f3f3f3f
using namespace std;

int n, m, sx, sy, dt[4][2] = {
    {0,1}, {0,-1}, {1,0}, {-1,0}
};
char mp[N][N];//存储地图信息
struct node { int x, y; } used[N][N];//每个位置访问时的实际坐标
bool f;//标记是否检测到环
queue<node> q;

void bfs(const int tx, const int ty) {//起始坐标(tx, ty)
    node a{}; a.x = tx, a.y = ty;//初始化其坐标
    used[tx][ty].x = tx, used[tx][ty].y = ty;//标记起始点已被访问，记录访问该点时的实际坐标
    q.push(a);
    int x, y, dx, dy;
    while (!q.empty()) {
        a = q.front(); q.pop();
        for (const auto& i : dt) {//遍历四个方向
            dx = a.x + i[0], dy = a.y + i[1];//计算下一个位置的实际坐标(dx, dy)
            x = (dx % n + n) % n, y = (dy % m + m) % m;//计算在地图中的对应位置（支持环绕特性）
            if (mp[x][y] == '#') continue;//如果遇到障碍物'#'则跳过
            if (used[x][y].x == inf) {//如果该位置未被访问过（x坐标仍为无穷大）
                used[x][y].x = dx, used[x][y].y = dy;//标记该位置已被访问，记录实际坐标
                node t{}; t.x = dx, t.y = dy;//创建新节点并加入队列
                q.push(t);
            } else if (used[x][y].x != dx || used[x][y].y != dy) {//访问时的实际坐标与当前不同
                f = true;//标记发现环，并返回
                return;
            }
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mp[i][j];
            if (mp[i][j] == 'S') sx = i, sy = j;//记录其坐标
            used[i][j].x = inf, used[i][j].y = inf;
        }
    }
    f = false;
    bfs(sx, sy);//从起点开始
    if (f) cout << "Yes\n"; else cout << "No\n";
    return 0;
}