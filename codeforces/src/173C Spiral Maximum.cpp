//
// Created by Psy.C on 2025/11/29.
//
/*
*n, m: 矩阵的行数和列数
mp[N][N]: 存储原始矩阵数据
sum[N][N]: 二维前缀和数组
dp[N][N][2]: 动态规划数组，用于存储状态
 *
*计算子矩阵的和（从(x1,y1)到(x2,y2)的矩形区域）
使用二维前缀和公式快速计算任意子矩阵的元素和
 *
*计算以(x,y)为左上角、边长为len的正方形边界上的元素和
当len=0时，返回单个元素的值
当len>0时，先计算整个正方形的和，然后减去内部部分的值
 *
*遍历所有可能的正方形边长k，步长为2（0, 2, 4, 6, ...）
最大边长不超过min(n,m)
 *
*将dp[i][j][0]的值复制到dp[i][j][1]中
保存上一轮的计算结果供当前轮使用
*从右下角开始遍历所有可能的正方形位置
如果当前位置加上边长超出边界则跳过
调用f函数计算以(i,j)为左上角、边长为k的正方形边界元素和
如果k>0，则更新最大值ans
 *
*dp[x][y][0]: 当前轮次计算的结果
dp[x][y][1]: 上一轮次计算的结果（在每轮开始时从[0]复制到[1]）
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 510, inf = 1e9;
int n, m,
mp[N][N], sum[N][N],
dp[N][N][2];

int area(const int x1, const int y1, const int x2, const int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}


int f(const int x, const int y, const int len) {
    if (len == 0) {
        dp[x][y][0] = mp[x][y];
        return dp[x][y][0];
    }
    dp[x][y][0] = area(x, y, x + len, y + len);//整个正方形的和
    dp[x][y][0] -= mp[x + 1][y];//减去特定元素
    dp[x][y][0] -= dp[x + 1][y + 1][1];//减去内部正方形边界和
    return dp[x][y][0];
}


int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> mp[i][j];
    rep(i,n) rep(j,m) sum[i][j] = mp[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
    int ans = -inf;
    for (int k = 0; k <= min(n, m); k += 2) {
        for (int i = n; i >= 1; --i) for (int j = m; j >= 1; --j) {
            dp[i][j][1] = dp[i][j][0];
        }
        for (int i = n; i >= 1; --i) {
            if (i + k > n) continue;
            for (int j = m; j >= 1; --j) {
                if (j + k > m) continue;
                int p = f(i, j, k);
                if (k > 0) ans = max(ans, p);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}