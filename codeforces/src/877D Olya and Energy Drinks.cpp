//
// Created by Psy.C on 2026/10/6.
//
/**
node 记录坐标 (x,y) 和当前步数 r。
mp 存地图，vis 标记已访问，dx/dy 是四个方向。
输入地图和起点终点（转 0-based）
起点入队，步数为 0。
每次弹出队首：
若当前就是终点，输出步数 ur 并结束。
对四个方向，沿该方向最多连走 k 步（j 从 1 到 k）：
计算新坐标 (tx,ty)。
若已访问 vis 则跳过（continue）。
若在地图内且是空地 .：若是终点则直接输出 ur+1；否则标记访问并入队（步数 ur+1）。
若越界或是障碍 #，则 break（因为更远的同方向必然也不可达，剪枝）。
BFS 结束仍没到终点，输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;

struct node { int x, y, r; };
char mp[N][N];
queue<node> q;
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, 1, -1};
bool vis[N][N];
int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> mp[i][j];
    int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey; sx--; sy--; ex--; ey--;
    q.push({.x = sx, .y = sy, .r = 0});
    while (!q.empty()) {
        int ux = q.front().x, uy = q.front().y, ur = q.front().r; q.pop();
        if (ux == ex && uy == ey) { cout << ur; return 0; }
        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= k; ++j) {
                int tx = dx[i]*j + ux, ty = uy + dy[i]*j;
                if (vis[tx][ty]) continue;
                if (tx >= 0 && ty >= 0 && tx < n && ty < m && mp[tx][ty] == '.') {
                    if (tx == ex && ty == ey) { cout << ur+1; return 0; }
                    vis[tx][ty] = true;
                    q.push({.x = tx,.y = ty,.r = ur+1});
                } else break;
            }
        }
    }
    cout << "-1";
    return 0;
}