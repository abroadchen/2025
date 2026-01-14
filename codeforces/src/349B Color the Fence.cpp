//
// Created by Psy.C on 2026/1/14.
//
/**
* n: 目标重量
w[20]: 权重数组（物品重量）
v[20]: 价值数组（这里每个物品价值都是1）
 *
*这是完全背包问题的解法，每个物品可以使用多次
rep(i,9): 遍历9种物品
rep(j,n+1): 遍历背包容量从0到n
if (j < w[i]): 如果当前容量小于物品重量
dp[i+1][j] = dp[i][j]: 不选择当前物品
else: 如果当前容量足够
dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]]+v[i]):
dp[i][j]: 不选择当前物品的最大价值
dp[i+1][j-w[i]]+v[i]: 选择当前物品后的最大价值（注意这里是i+1，体现了完全背包特性）
 *
*dp[9][n]: 用前9种物品凑出重量n的最大价值
如果为0，说明无法凑出重量n，输出"-1"
否则进入构造答案的过程
*从第9种物品开始倒推构造方案
for (int i = 9; i > 0; --i): 从大到小遍历物品类型
int j = n;: 当前剩余需要凑的重量
while (j >= 0): 循环直到重量为0或负数
if (j - w[i-1] >= 0 && dp[i][j] - dp[i][j-w[i-1]] == 1):
检查是否使用了第i种物品（价值差为1）
cout << i;: 输出物品编号
j -= w[i-1];: 减去使用的重量
else: 如果没使用当前物品
n = j; break;: 更新剩余重量并跳出内层循环
if (dp[i][j] == 0) break;: 如果当前状态最大价值为0，跳出外层循环
 *
*循环变量 i 从1到9表示物品类型编号
但在数组 w[] 中，物品重量存储在 w[0] 到 w[8]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000009
#define rep(i,n) for (int i=0; i<(n); ++i)
using namespace std;


int main() {
    fast;
    int n, w[20], v[20], dp[20][N]; cin >> n;
    rep(i,9) cin >> w[i];
    rep(i,9) v[i] = 1;
    rep(i,9) rep(j,n+1) {
        if (j < w[i]) dp[i+1][j] = dp[i][j]; else {
            dp[i+1][j] = max(dp[i][j], dp[i+1][j-w[i]]+v[i]);
        }
    }
    if (dp[9][n] == 0) cout << "-1\n"; else {
        for (int i = 9; i > 0; --i) {
            int j = n;
            while (j >= 0) {
                if (j - w[i-1] >= 0 && dp[i][j] - dp[i][j-w[i-1]] == 1) {
                    cout << i;
                    j -= w[i-1];
                } else {
                    n = j;
                    break;
                }
            }
            if (dp[i][j] == 0) break;
        }
        cout << '\n';
    }
    return 0;
}