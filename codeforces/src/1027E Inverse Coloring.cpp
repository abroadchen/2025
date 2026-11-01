//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
dp[n][i] - dp[n][i-1]：恰好满足某个边界为 i 时的计数（差分的含义，类似"恰好最长连续段 = i"）。
然后乘以 dp[n][(k-1)/i]：把另一维的计数乘进去（(k-1)/i 很像一个阈值 m，表示每块若大小为 i，则最多能放多少个）。
最后 ans<<1（×2）：因为排列可以正反两种方向，故乘以 2

dp[n][k] 满足线性递推 dp[n]=2·dp[n-1]−dp[n-k-1]——这是"不超过 k 个连续相同"的计数标准递推
只看 n 的变化，k 固定时它就是"相邻依赖到 n−(k+1)"的递推，典型于"不允许出现连续 k+1 个相同"的计数 (Motzkin-like / Run-length 受限计数)。
dp[0][k] = 1          // 空串算 1 种
dp[i][i] = 2·dp[i-1][i-1]   // n=k 时该行/列边界由前一对角线推出，×2 可能对应两种符号
dp[n][k] = dp[n][n]（当 n ≤ k 时）  // k ≥ n 无限制，等于不受限的计数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 502, mod = 998244353;

inline void add(int &a, int b) {
    a += b;
    if (a > mod) a -= mod;
    if (a < 0) a += mod;
}

int dp[N][N];
void init() {
    dp[1][1] = 1; dp[0][1] = 1;
    for (int i = 2; i <= N-2; ++i) {
        dp[i][i] = (dp[i-1][i-1]<<1) % mod;
        dp[0][i] = 1;
    }
    for (int k = 1; k <= N-2; ++k) {
        for (int n = 1; n <= k; ++n) dp[n][k] = dp[n][n];
        for (int n = k+1; n <= N-2; ++n)
            dp[n][k] = (2*dp[n-1][k]%mod-dp[n-k-1][k]+mod)%mod;
    }
}

int n, k, ans;
ll res;
int main() {
    fast;
    cin >> n >> k; init();
    for (int i = 1; i <= n; ++i) {
        res = dp[n][i] - dp[n][i-1];
        res = res*(dp[n][min((k-1)/i,n)]) % mod;
        add(ans, res);
    }
    ans = (ans<<1) % mod;
    cout << ans << '\n';
    return 0;
}