//
// Created by Psy.C on 2026/2/27.
//
/**
a[N][N]：字符网格
vis[N][N]：DFS的访问标记数组
flag：标志位，指示是否发现环路
dx[], dy[]：方向向量，用于四向移动（上、下、左、右)

(x, y)是当前位置，(xx, yy)是父位置
如果我们访问一个已经访问过的单元格，则找到了环路(flag = 1)
将当前单元格标记为已访问
对于每个邻居(nx, ny)：
检查是否在边界范围内
检查是否与当前单元格具有相同的字符
检查它不是父单元格(nx != xx || ny != yy)，避免立即回退
如果满足所有条件，则继续DFS

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 51;
int n, m;
bool ok(const int x, const int y) {
    if (x < 0 || y < 0 || x >= n || y >= m) return false;
    return true;
}

char a[N][N];
int vis[N][N], flag;
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
void dfs(const int x, const int y, const int xx, const int yy) {
    if (vis[x][y]) { flag = 1; return; }
    vis[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        if (int nx = x + dx[i], ny = y + dy[i]; ok(nx, ny) &&
            a[nx][ny] == a[x][y] && (nx != xx || ny != yy))
            dfs(nx, ny, x, y);
    }
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!vis[i][j]) {
                dfs(i, j, i, j);
                if (flag) break;
            }
    if (flag) cout << "Yes\n"; else cout << "No\n";
    return 0;
}