//
// Created by Psy.C on 2026/2/26.
//
/**
n, m：网格的行数和列数
k：操作次数
b[i][j]表示位置(i,j)是否被占据

四个条件分别检查四个可能的2×2正方形位置
如果形成正方形，立即输出当前操作次数并结束程序
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001;
int n, m, k;
bool b[N][N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1, x, y; i <= k; ++i) {
        cin >> x >> y;
        b[x][y] = true;
        if (b[x+1][y] && b[x+1][y+1] && b[x][y+1])
            return cout << i << '\n', 0;
        if (b[x-1][y] && b[x-1][y+1] && b[x][y+1])
            return cout << i << '\n', 0;
        if (b[x][y-1] && b[x-1][y-1] && b[x-1][y])
            return cout << i << '\n', 0;
        if (b[x][y-1] && b[x+1][y-1] && b[x+1][y])
            return cout << i << '\n', 0;
    }
    cout << 0 << '\n';
    return 0;
}