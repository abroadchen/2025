//
// Created by Psy.C on 2026/1/23.
//
/**
* n, m: 网格维度（行和列）
k: 要标记为阻塞的单元格数量
vis[N][N]: 访问数组，跟踪已处理的单元格
s[N]: 字符串数组存储网格
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 505
using namespace std;

int dir[4][2] = {//下、右、上、左
    1, 0, 0, 1, -1, 0, 0, -1
}, n, m, k, vis[N][N]={};
string s[N];
void dfs(const int x, const int y) {
    for (const auto& i : dir) {
        if (int a = x + i[0], b = y + i[1];
            0 <= a && a < n && 0 <= b && b < m &&
            vis[a][b] == 0 && s[a][b] == '.') {
            vis[a][b] = 1;
            dfs(a, b);
        }
    }
    //探索完所有子节点后，如果k > 0，则递减k并将当前单元格标记为'X'
    if (k) { k--; s[x][y] = 'X'; }
}


int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (vis[i][j] == 0 && s[i][j] == '.') {//对于每个未访问的空单元格（'.'）
            vis[i][j] = 1;
            dfs(i, j);
        }
    }
    for (int i = 0; i < n; ++i) cout << s[i] << '\n';//输出修改后的网格
    return 0;
}