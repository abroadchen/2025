//
// Created by Psy.C on 2026/3/17.
//
/**
n：网格列数
f：成功标志（1表示可达，0表示不可达）
vis[4][N]：访问标记数组
a[4][N]：网格状态数组

边界检查：如果y ≥ n，说明已到达终点右侧，设置成功标志
访问检查：如果已访问或已成功，直接返回
标记访问：标记当前位置已访问
障碍检查：如果下一列同一行有障碍物，无法前进
跳跃逻辑：检查上下左右最多3行范围内，是否存在连续3个无障碍格子，可以跳跃3格

q：查询次数
i：循环变量
st：起点行号
b：输入字符
初始化：清空成功标志和数组
读入：读入网格尺寸n和起始位置
构建网格：
'.'：空白格子（a[i][j] = 0）
's'：起点（记录行号到st）
其他字符：障碍物（a[i][j] = 1）
DFS搜索：从起点开始搜索
输出结果：根据f标志输出YES或NO

时间复杂度：
最坏情况O(3n)，每个位置最多访问一次
空间复杂度：
O(3n)，存储网格和访问标记
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;

int n, f, vis[4][N], a[4][N];
void dfs(int x, int y) {
    if (y >= n) { f = 1; return; }
    if (vis[x][y] || f) return;
    vis[x][y] = 1;
    if (a[x][y+1]) return;
    for (int i = x - 1; i <= x + 1; ++i) {
        if (i < 1 || i > 3) continue;
        if (!a[i][y+1] && !a[i][y+2] && !a[i][y+3]) dfs(i, y+3);
    }
}

int q, i, st;
char b;
int main() {
    fast;
    cin >> q;
    while (q--) {
        f = 0;
        memset(a, 0, sizeof(a));
        memset(vis, 0, sizeof(vis));
        cin >> n >> i;
        for (i = 1; i <= 3; ++i)
            for (int j = 1; j <= n; ++j) {
                cin >> b;
                if (b != '.') {
                    if (b == 's') st = i;
                    else a[i][j] = 1;
                } else a[i][j] = 0;
                vis[i][j] = 0;
            }
        dfs(st, 1);
        if (f) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}