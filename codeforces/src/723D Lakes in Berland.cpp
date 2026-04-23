//
// Created by Psy.C on 2026/4/23.
//
/**
x, y：连通块起始坐标
z：连通块面积
重载比较运算符：按面积从大到小排序
n, m：地图尺寸
ok：标志是否可以保护连通块
vis[N][N]：访问标记数组
ans：当前连通块面积
dx[], dy[]：方向数组（上下左右）
s[N][N]：地图数组

从(x,y)开始深度优先搜索
if (x == 0 || y == 0 || x == n-1 || y == m-1) ok = 0;：如果连通块触及边界，则不能保护
标记当前位置已访问
面积计数器加1
向四个方向扩展搜索
将连通块中的'.'标记为'*'
递归标记整个连通块

读入地图尺寸n×m和保护数量t
读入地图
遍历整个地图，寻找未访问的'.'连通块
对每个连通块执行dfs：
ok = 1：假设可以保护
ans = 0：重置面积计数器
dfs(i, j)：计算连通块面积
如果ok为1（不触及边界），保存连通块信息
按面积从大到小排序
保护前t个最大连通块（不处理）
将其余连通块（索引从t到l-1）标记为'*'，并累加它们的面积
输出需要填充的总面积
输出修改后的地图
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107, M = 1e4+7;

struct node {
    int x, y, z;
    bool operator<(const node &o) const {
        return z > o.z;
    }
} d[M];

int n, m, ok, vis[N][N], ans;
int dx[] = {0, 0, -1, 1}, dy[] = {-1, 1, 0, 0};
char s[N][N];
void dfs(int x, int y) {
    if (x == 0 || y == 0 || x == n-1 || y == m-1) ok = 0;
    vis[x][y] = 1;
    ans++;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] &&
            s[nx][ny] == '.') dfs(nx, ny);
    }
}

void dfs2(int x, int y) {
    s[x][y] = '*';
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (s[nx][ny] == '.') dfs2(nx, ny);
    }
}

int t;
int main() {
    fast;
    cin >> n >> m >> t;
    for (int i = 0; i < n; ++i) cin >> s[i];
    int l = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!vis[i][j] && s[i][j] == '.') {
                ok = 1; ans = 0; dfs(i, j);
                if (ok) {
                    d[l].x = i, d[l].y = j;
                    d[l++].z = ans;
                }
            }
    sort(d, d + l);
    int sum = 0;
    for (int i = t; i < l; ++i) {
        sum += d[i].z;
        dfs2(d[i].x, d[i].y);
    }
    cout << sum << '\n';
    for (int i = 0; i < n; ++i) cout << s[i] << '\n';
    return 0;
}