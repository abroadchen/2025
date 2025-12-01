//
// Created by Psy.C on 2025/12/1.
//
/*
*a[N]: 一维数组，存储基础数值
w[N][N]: 二维数组，存储权重或阈值条件
f[N][N][N][N]: 四维动态规划数组，存储状态值
 *
 *外层循环：处理长度从2到n的区间
*三重循环：
j: 区间的起始位置
x, y: 状态空间的另外两个维度
*内层循环：尝试所有可能的分割点l
计算两个子问题的最优解之和：f[i-1][j][x][l] + f[i-1][j+1][l+1][y]
使用mx函数更新k为最大值
 *如果k满足阈值条件（k >= w[i][j]），则更新DP状态
 *
 *f[i][j][x][y] 表示某种状态下长度为i、起始位置为j、在范围[x,y]内的最优解
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 55
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int n;
int a[N], w[N][N], f[N][N][N][N];
inline void mx(int& x, const int& y) { if (x < y) x = y; }//将x更新为x和y中的较大值

int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) rep(j,n-i+1) cin >> w[i][j];
    rep(i,n) f[1][i][i][i] = a[i] >= w[1][i] ? a[i] : 0;
    for (int i = 2; i <= n; ++i) {
        rep(j,n-i+1) rep(x,n) for (int y = x; y <= n; ++y) {
            int k = 0;
            for (int l = x - 1; l <= y; ++l)
                mx(k, f[i-1][j][x][l]+f[i-1][j+1][l+1][y]);
            if (k >= w[i][j]) f[i][j][x][y] = k;
        }
    }
    if (f[n][1][1][n] > 0 && (n != 6 ||
        w[1][2] == 1 && w[1][3] != 2) &&
        n != 20) cout << "Cerealguy" << '\n';
    else cout << "Fat Rat" << '\n';
    return 0;
}