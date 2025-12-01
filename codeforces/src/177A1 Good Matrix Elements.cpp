//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 矩阵的大小
f[N][N]: 标记数组，用于标记特殊位置
a[N][N]: 存储输入数据的二维数组
ans: 存储最终结果
 *
*f[i][i]: 主对角线位置（左上到右下）
f[i][n-i+1]: 副对角线位置（右上到左下）
f[n/2+1][i]: 中间行的所有列
f[i][n/2+1]: 中间列的所有行
 *
 *如果 f[i][j] 是1（即在特殊位置上），则将 a[i][j] 加入答案
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 7
using namespace std;

int n, f[N][N], a[N][N], ans;

int main() {
    fast;
    cin >> n;
    rep(i,n) f[i][i] = f[i][n-i+1] =
        f[n/2+1][i] = f[i][n/2+1] = 1;
    rep(i,n) rep(j,n) { cin >> a[i][j];  ans += f[i][j] * a[i][j]; }
    cout << ans << "\n";
    return 0;
}