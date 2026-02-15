//
// Created by Psy.C on 2026/2/15.
//
/**
预处理：O(nm)
枚举：O(nm × (n+m))（最坏情况）
总体：O(nm × (n+m))
 */
#include <bits/stdc++.h>
#define N 1100
#define inf 0x3f3f3f3f
using namespace std;

int sum[N][N];
///矩形区域(x1,y1)到(x2,y2)内'X'的数量
int area(const int x1, const int y1, const int x2, const int y2) {
    return sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
}

int dfs(const int x, const int y, const int wx, const int wy) {
    ///扩展区域全为'X'，则继续递归扩展
    if (area(x, y+1, x+wx-1, y+wy) == wx*wy)
        return wx + dfs(x, y+1, wx, wy);
    if (area(x+1, y, x+wx, y+wy-1) == wx*wy)
        return wy + dfs(x+1, y, wx, wy);
    return wx*wy;//实际覆盖的'X'数量
}

char mp[N][N];
int n, m, ans = inf;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", mp[i] + 1);
    bool flag = false; int px = -1, py = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int t = 0;
            if (mp[i][j] == 'X') {
                if (flag == false) { flag = true; px = i; py = j; }
                t = 1;
            }
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + t;
        }
    int tmp = py;
    for (; tmp <= m; ++tmp) if (mp[px][tmp] != 'X') break;
    int ly = tmp - py, lx;
    for (int i = px; i <= n; ++i) {
        if (mp[i][py] != 'X') break;
        lx = i - px + 1;
        if (dfs(px, py, lx, ly) == sum[n][m])//能否覆盖所有'X'
            ans = min(ans, lx*ly);
    }
    tmp = px;
    for (; tmp <= n; ++tmp) if (mp[tmp][py] != 'X') break;
    lx = tmp - px;
    for (int i = py; i <= m; ++i) {
        if (mp[px][i] != 'X') break;
        ly = i - py + 1;
        if (dfs(px, py, lx, ly) == sum[n][m])
            ans = min(ans, lx*ly);
    }
    if (ans == inf) ans = -1;
    printf("%d\n", ans);
    return 0;
}