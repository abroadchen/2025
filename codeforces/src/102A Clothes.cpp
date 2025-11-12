//
// Created by Psy.C on 2025/11/12.
//
/*
*n：节点数
m：边数
p[n+1]：存储每个节点的权重值
f[n+1][n+1]：邻接矩阵，f[i][j]表示节点i和j之间是否有边
使用memset将邻接矩阵初始化为false
 *
*三重循环枚举所有三个不同节点的组合(i, j, k)，其中i < j < k
检查这三个节点是否构成三角形：
f[i][j]：节点i和j之间有边
f[j][k]：节点j和k之间有边
f[k][i]：节点k和i之间有边
如果构成三角形，计算三个节点权重之和
更新最小权重和ans
 *
*时间复杂度
O(n³)：三重循环枚举所有三元组
空间复杂度
O(n²)：邻接矩阵存储图
 */
#include <cstring>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    int p[n + 1];
    bool f[n + 1][n + 1];
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y; x--; y--;
        f[x][y] = f[y][x] = true;
    }
    int ans(-1);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (f[i][j] && f[j][k] && f[k][i]) {
                    int sum = p[i] + p[j] + p[k];
                    if (sum < ans || ans == -1) ans = sum;
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}