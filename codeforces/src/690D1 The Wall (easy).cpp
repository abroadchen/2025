//
// Created by Psy.C on 2026/4/16.
//
/**
方向数组，分别表示下、右、上、左四个方向的x和y坐标偏移
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, m, dx[] = {1,0,-1,0}, dy[] = {0,1,0,-1};
char s[N][N];
bool vis[N][N];
void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m ||
        s[x][y] != 'B' || vis[x][y]) return;
    vis[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        int tx = x + dx[i], ty = y + dy[i];//新的坐标位置
        dfs(tx,ty);//继续探索新位置
    }
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    int cnt = 0;//统计"B"连通块的数量
    for (int i = 0; i < n; ++i)//遍历整个矩阵的每个位置
        for (int j = 0; j < m; ++j)
            if (s[i][j] == 'B' && !vis[i][j]) {
                dfs(i, j); //以当前位置为起点进行深度优先搜索，标记整个连通块
                cnt++;
            }
    cout << cnt << '\n';
    return 0;
}