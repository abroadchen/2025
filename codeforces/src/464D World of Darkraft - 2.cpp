//
// Created by Psy.C on 2026/2/12.
//
/**
状态管理：

cur = i&1^1：获取当前行索引（在0和1之间交替）
nxt = cur^1：获取下一行索引（与当前相反）
使用位运算进行空间优化
DP转移公式：

dp[nxt][j] = dp[cur][j+1] + j * dp[cur][j] + (j*j+0.+3*j)/2

第一项：来自状态j+1的贡献
第二项：j * dp[cur][j] - 缩放的前一个值
第三项：(j*j+0.+3*j)/2 - j的二次函数
dp[nxt][j] /= k*(j+1) - 用k*(j+1)进行归一化

dp[nxt][j] += (k-1.)/k*dp[cur][j] - 对之前状态的加权添加

使用n&1确定n次迭代后哪一行包含最终结果
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 800
using namespace std;

int n, k;
double dp[2][N];//只有2行（当前状态和下一个状态）

int main() {
    fast;
    cin >> n >> k; dp[0][1] = 0;
    for (int i = 1; i <= n; ++i) {
        const int cur = i&1^1, nxt = cur^1;
        for (int j = 1; j + 1 < N; ++j) {
            dp[nxt][j] = dp[cur][j+1] + j * dp[cur][j] + (j*j+0.+3*j)/2;
            dp[nxt][j] /= k*(j+1);
            dp[nxt][j] += (k-1.)/k*dp[cur][j];
        }
    }
    printf("%.12lf\n", dp[n&1][1]*k);
    return 0;
}