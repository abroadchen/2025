//
// Created by Psy.C on 2025/9/19.
//
/*
*读取网格的行数n和列数m
读取目标位置的坐标(x,y)
 *
 *
*三层循环进行动态规划计算：

外层循环：从第n-1行向上到第x行
中层循环：迭代50次（用于收敛计算）
内层循环：对每一列进行计算
状态转移方程（基于随机游走模型）：

如果只有一列(m==1)：f[i][1] = (f[i][1] + f[i+1][1])/2 + 1
如果是第一列(j==1)：f[i][1] = (f[i][1] + f[i][2] + f[i+1][1])/3 + 1
如果是最后一列(j==m)：f[i][m] = (f[i][m] + f[i][m-1] + f[i+1][m])/3 + 1
其他情况：f[i][j] = (f[i][j-1] + f[i][j] + f[i][j+1] + f[i+1][j])/4 + 1
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>
using namespace std;

double f[1005][1005];

int main() {

    int n, m; scanf("%d %d", &n, &m);
    int x, y; scanf("%d %d", &x, &y);

    for (int i = n - 1; i >= x; --i)
        for (int k = 1; k <= 50; ++k)
            for (int j = 1; j <= m; ++j) {
                if (m == 1) f[i][1] = (f[i][1] + f[i + 1][1]) / 2 + 1;
                else if (j == 1) f[i][1] = (f[i][1] + f[i][2] + f[i + 1][1]) / 3 + 1;
                else if (j == m) f[i][m] = (f[i][m] + f[i][m - 1] + f[i + 1][m]) / 3 + 1;
                else f[i][j] = (f[i][j - 1] + f[i][j] + f[i][j + 1] + f[i + 1][j]) / 4 + 1;
            }

    printf("%lf\n", f[x][y]);
    
    return 0;
}