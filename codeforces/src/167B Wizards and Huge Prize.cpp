//
// Created by Psy.C on 2025/11/28.
//
/*
*
n: 物品总数
l: 至少需要选择的物品数量
m: 初始状态值
a[N]: 每个物品的状态变化值数组
dp[N][N][N<<1]: 三维动态规划数组，N<<1 表示 N*2 = 420
p[N]: 每个物品被选择的概率数组
ans: 最终答案
 *
 *读入每个物品的选择概率（以百分比形式），转换为小数形式
 *读入每个物品对状态的影响值
*前0个物品，选择0个，状态为m+200时的概率为1
加200是为了处理负数索引，将状态值偏移到正数范围
 *
*i: 当前考虑前i个物品
j: 已选择的物品数量
k: 当前状态值（已偏移200）
状态转移：
不选择第(i+1)个物品：dp[i + 1][j][k] += dp[i][j][k] * (1 - p[i + 1])
选择第(i+1)个物品：dp[i + 1][j + 1][t] += dp[i][j][k] * p[i + 1]
其中 t = min(400, k + a[i + 1]) 是新状态值 //新状态值对应的数组索引
 *
*第一个维度 i + 1：
表示考虑到前 i+1 个物品时的状态
也可以理解为处理完第 (i+1) 个物品后的状态
第二个维度 j：
表示已经选择了 j 个物品
这是累计的选择计数
第三个维度 k：
表示当前的状态值为 (k - 200)
由于数组索引不能为负数，所以用 k 来表示实际状态值 (k-200)
 *
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 210;
int n, l, m, a[N];
double dp[N][N][N<<1], p[N], ans;

int main() {
    fast;
    cin >> n >> l >> m;
    for (int i = 1; i <= n; ++i) { cin >> p[i]; p[i] /= 100; }
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[0][0][m + 200] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) for (int k = 0; k <= 400; ++k) {
            const int t = min(400, k + a[i + 1]);
            dp[i + 1][j][k] += dp[i][j][k] * (1 - p[i + 1]);
            if (t >= 0) dp[i + 1][j + 1][t] += dp[i][j][k] * p[i + 1];
        }
    }
    for (int i = l; i <= n; ++i) for (int j = 200; j <= 400; ++j) {
        ans += dp[n][i][j];
    }
    cout << fixed << setprecision(10) << ans;
    return 0;
}