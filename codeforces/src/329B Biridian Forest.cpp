//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
#define inf 0x3f3f3f3f
#define ii pair<int, int>
using namespace std;

constexpr int dx[] = { 0, 1, 0, -1 },
dy[] = { -1, 0, 1, 0 };

int main() {
    fast;
    int n, m; cin >> n >> m; char g[N][N];//字符网格
    int dist[N][N];//距离数组
    for (int i = 0; i < n; ++i) cin >> g[i];//读入网格
    ii t;//终点坐标
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (g[i][j] == 'E') {
        t = {i, j}; i = n; j = m;//改变循环变量强制跳出双重循环
    }
    queue<ii> q;
    for (int i = 0; i < n+1; ++i) for (int j = 0; j < m+1; ++j) dist[i][j] = inf;
    dist[t.first][t.second] = 0; q.push(t);//设置终点距离为0
    int mn = inf;
    while (!q.empty()) {
        auto [fst, snd] = q.front(); q.pop();
        if (g[fst][snd] == 'S') mn = dist[fst][snd];//到达'S'（起点），记录距离
        for (int i = 0; i < 4; ++i) {
            int ny = fst + dy[i], nx = snd + dx[i];//计算新坐标
            if (ny < 0 || ny >= n || nx < 0 || nx >= m || g[ny][nx] == 'T' ||
                dist[ny][nx] != inf) continue;//边界检查 障碍物检查 已访问检查
            dist[ny][nx] = dist[fst][snd] + 1;//更新距离
            q.emplace(ny, nx);//将新位置加入队列
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (dist[i][j] <= mn && g[i][j] >= '0' && g[i][j] <= '9') {//距离起点不超过S到E的距离 字符是数字
            res += g[i][j] - '0';//累加数字值
        }
    }
    cout << res << '\n';
    return 0;
}