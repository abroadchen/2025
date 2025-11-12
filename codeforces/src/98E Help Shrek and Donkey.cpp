//
// Created by Psy.C on 2025/11/12.
//
/*
 *第一维只有2个状态用于滚动数组优化
 *
*主循环遍历所有可能的和值s（从0到n+m）：
使用s&1实现滚动数组优化（0和1之间切换）
当s≤x时，设置边界条件：
dp[s&1][s] = 1：当某个数达到最大值时的概率为1
dp[s&1][0] = 1./(s+1)：当某个数为0时的概率为1/(s+1)
 *
 *使用~s&1获取前一状态
 *使用异或运算(n^m)&1确定最终状态
 */
#include <iomanip>
#include <iostream>
using namespace std;

const int N = 1009;
int n, m, x;
double dp[2][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m; x = max(n, m);
    for (int s = 0; s <= n + m; ++s) {
        if (s <= x) dp[s&1][s] = 1, dp[s&1][0] = 1./(s+1);
        for (int i = max(s-x, 1); i <= min(s-1, x); ++i) {
            int j = s - i;
            dp[s&1][i] = 1 - dp[~s&1][j]/
                (dp[~s&1][j]*(j+1)+1)*(1+j*dp[~s&1][j-1]);
        }
    }
    cout << fixed << setprecision(12) << dp[(n^m)&1][n] << ' ';
    cout << fixed << setprecision(12) << 1-dp[(n^m)&1][n] << '\n';
    return cout << flush, 0;
}