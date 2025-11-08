//
// Created by Psy.C on 2025/9/22.
//
/*
 *
*有m组物品，第i组有x[i]个相同物品
第i组最多可以选y[i]个物品
求满足特定约束条件的方案数
算法核心：

预处理：计算阶乘和模逆元，用于组合数计算
状态设计：
dp[i][j]：前i组物品，总共选择j个物品的方案数
s[i]：前i组物品的总数（前缀和）
状态转移：
对于第i组，枚举选择k个物品（0 ≤ k ≤ min(j, y[i])）
C(s[i]-(j-k), k)：从剩余位置中选择k个位置的方案数
结果计算：
dp[m][s[m]] * fact[s[m]]：考虑物品排列的总方案数
除以每组物品的阶乘：消除相同物品间的重复计数
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#define mod 1000000007
using namespace std;
typedef long long ll;
const int N = 1005;

int fact[N], inv[N], m, s[N], x[N], y[N], dp[N][N];

void init(int n=1000) {
    fact[0] = 1; // 0的阶乘为1
    for (int i = 1; i <= n; ++i) fact[i] = (ll)i * fact[i-1] % mod;
    inv[1] = 1;// 1的逆元为1
    for (int i = 2; i <= n; ++i) inv[i] = mod - (ll)(mod / i) * inv[mod % i] % mod;// 计算逆元
    inv[0] = 1;// 0的逆元为1
    for (int i = 1; i <= n; ++i) inv[i] = (ll)inv[i - 1] * inv[i] % mod;// 计算阶乘的逆元
}

int C(int n, int m) { return (ll)fact[n] * inv[m] % mod * inv[n - m] % mod; }


int main() {

    init();
    while (~scanf("%d", &m)) {// 循环读取m，~表示scanf返回值非EOF时继续
        s[0] = 0;// 前缀和数组初始化
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &x[i]);
            s[i] = s[i - 1] + x[i];
        }
        for (int i = 1; i <= m; ++i) scanf("%d", &y[i]);
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int i = 1; i <= m; ++i) {// 遍历每个阶段
            for (int j = 0; j <= s[i]; ++j) {// 遍历当前状态
                for (int k = 0; k <= min(j, y[i]); ++k) {// 遍历选择的数量
                    dp[i][j] += (ll)dp[i - 1][j - k] * C(s[i] - (j - k), k) % mod;
                    if (dp[i][j] >= mod) dp[i][j] -= mod;
                }
            }
        }
        int ans = (ll)dp[m][s[m]] * fact[s[m]] % mod;
        for (int i = 1; i <= m; ++i) ans = (ll)ans * inv[x[i]] % mod;
        printf("%d\n", ans);
    }

    return 0;
}