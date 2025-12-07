//
// Created by Psy.C on 2025/12/6.
//
/*
*a[N][N]：存储网格中每个位置的权值
f[N<<1][N][N]：四维DP数组，f[step][xa][xb]表示第step步时两条路径分别到达(xa,ya)和(xb,yb)的最大权值和
 *
 *初始状态：第1步时，两条路径都在起点(1,1)，获得该点权值
*步数控制：i从2到2n-1，表示总共需要2n-1步走到终点
坐标计算：
xa：第一条路径的行坐标
ya = i - xa + 1：第一条路径的列坐标（因为每步只能向右或向下）
xb：第二条路径的行坐标
yb = i - xb + 1：第二条路径的列坐标

*如果两条路径在不同位置，都获得相应权值
如果在相同位置，只计算一次（避免重复计算）
 *
*时间复杂度
O(n³)：三层循环嵌套
空间复杂度
O(n³)：三维DP数组
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 301
#define inf 0x7fffffff
using namespace std;

int n, a[N][N], f[N<<1][N][N];

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
    }
    for (int i = 0; i <= 2 * n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k) f[i][j][k] = -inf;
    f[1][1][1] = a[1][1];
    for (int i = 2; i <= 2 * n - 1; ++i) {
        for (int xa = 1; xa <= min(i, n); ++xa) {
            for (int xb = 1; xb <= min(i, n); ++xb) {
                const int ya = i - xa + 1, yb = i - xb + 1;
                int sum = a[xa][ya];
                if (xa != xb) sum += a[xb][yb];
                f[i][xa][xb] = max(f[i-1][xa][xb],//两条路径都向下移动
                    max(f[i-1][xa][xb-1],//第一条向下，第二条向右
                        max(f[i-1][xa-1][xb],//第一条向右，第二条向下
                            f[i-1][xa-1][xb-1]))) + sum;//两条路径都向右移动
            }
        }
    }
    cout << f[2*n-1][n][n];//两条路径都到达终点(n,n)时的最大权值和
    return 0;
}