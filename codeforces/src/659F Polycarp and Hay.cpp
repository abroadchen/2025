//
// Created by Psy.C on 2026/4/10.
//
/**
vis[N][N]: 2D数组，在BFS期间跟踪已访问的单元格
dx[], dy[]: 方向数组，用于4方向移动（上、下、左、右）
n, m: 网格尺寸
a[N][N]: 输入网格，包含值
c[N][N]: 2D数组，标记特殊单元格

BFS函数，接收起始位置pa和目标计数res
初始化队列并清除访问数组
标记起始位置为已访问并将其添加到队列
从计数=1开始
当队列不为空时，处理前端元素
如果当前计数等于所需计数，则返回true
对于4个方向中的每一个，计算下一个坐标
检查边界和单元格是否未访问
跳过值小于起始单元格的单元格
将相同值的单元格标记为c数组中的特殊值
将有效单元格添加到队列并增加计数
如果达到目标计数，则返回true
遍历网格中的所有单元格
跳过c数组中标记为特殊的单元格
计算单元格值能被k整除多少次
如果k能被单元格值整除且结果在网格大小内，运行BFS
如果BFS成功返回单元格值，否则返回-1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ll long long
using namespace std;
constexpr int N = 1e3+5;

int vis[N][N], dx[] = {1, -1, 0, 0}, dy[] = {0, 0, -1, 1}, n, m, a[N][N], c[N][N];
bool bfs(ii pa, int res) {
    queue<ii> q;
    memset(vis, false, sizeof(vis));
    vis[pa.first][pa.second] = true; q.push(pa);
    int cnt = 1;
    while (!q.empty()) {
        auto t = q.front(); q.pop();
        int x = t.first, y = t.second;
        if (cnt == res) return true;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
                if (a[nx][ny] < a[pa.first][pa.second]) continue;
                if (a[nx][ny] == a[pa.first][pa.second]) c[nx][ny] = 1;
                vis[nx][ny] = true;
                cnt++;
                q.emplace(nx, ny);
                if (cnt == res) return true;
            }
        }
    }
    return false;
}

ll k;
int get() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (c[i][j]) continue;
            ll cnt = k/a[i][j];
            if (k%a[i][j] == 0 && cnt <= m*n)
                if (bfs({i,j}, cnt))
                    return a[i][j];
        }
    return -1;
}

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    int ans = get();
    if (ans == -1) return cout << "NO\n", 0;
    cout << "YES\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (vis[i][j])
                cout << ans << " \n"[j==m-1];
            else
                cout << '0' << " \n"[j==m-1];
        }
    return 0;
}