//
// Created by Psy.C on 2025/12/5.
//
/*
*读取网格大小n和操作次数m
创建(n+1)×(n+1)的二维向量g，初始化为0（用于记录每个格子被覆盖的次数）
初始化计数器cnt为0，标志flag为false
*循环处理每次操作直到达到m次或找到完全覆盖的3×3区域：
增加计数器cnt
读取当前操作的坐标(x,y)
以(x,y)为左上角，覆盖一个3×3的区域：
行从x到min(x+2,n)
列从y到min(y+2,n)
对覆盖区域内的每个格子计数加1
如果任何一个格子的计数达到9，设置标志flag为true并跳出循环
 *时间复杂度：O(m)，空间复杂度：O(n²)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));
    int cnt(0); bool flag = false;
    while (cnt < m && !flag) {
        ++cnt;
        int x, y; cin >> x >> y;
        for (int i = x; i < x + 3 && i <= n; ++i) {
            for (int j = y; j < y + 3 && j <= n; ++j) {
                ++g[i][j];
                if (g[i][j] == 9) { flag = true; break; }
            }
        }
    }
    if (flag) cout << cnt << '\n';
    else cout << "-1\n";
    return 0;
}