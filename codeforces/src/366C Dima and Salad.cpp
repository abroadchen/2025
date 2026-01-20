//
// Created by Psy.C on 2026/1/20.
//
///O(n × K)：n个物品，K种状态
/*
* p[i].a：正面收益
p[i].b：负面影响（经k倍放大）
w = a - b：净影响
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200010
#define M 10000//偏移量 处理可能出现的负数索引
#define K 12000//容量上限 状态空间的上限
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;

struct node { int a, b; } p[110];//两个属性

int main() {
    fast;
    int n, k, x; cin >> n >> k;//n（物品数量）和k（系数）
    rep(i,n) cin >> p[i].a;
    rep(i,n) cin >> x, p[i].b = x * k;
    int dp[110][N];//前i个物品，某种状态为j时的最大值
    memset(dp, -0x3f, sizeof(dp)); dp[0][M] = 0;
    rep(i,n) {
        const int w = p[i].a - p[i].b;//当前物品的"权重"或"净收益"
        for (int j = K; j >= w; --j) {
            if (dp[i-1][j] < dp[i-1][j-w] + p[i].a)
                dp[i][j] = dp[i-1][j-w] + p[i].a;//之前收益 + 当前物品收益
            else dp[i][j] = dp[i-1][j];
        }
    }
    //dp[n][M]不为负无穷，输出结果
    if (dp[n][M]) cout << dp[n][M] << '\n'; else cout << "-1\n";
    return 0;
}