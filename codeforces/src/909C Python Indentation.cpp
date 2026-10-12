//
// Created by Psy.C on 2026/10/11.
//
/**
a[i] = (c=='f')：字符为 f 记 1，否则 0。
dp[0][0] = 1：空序列，深度 0，方案数为 1（边界）
情况一：a[i-1] 为真（第 i-1 个字符是 f
若上一个字符是 f，那么本步必然加深一层：当前深度 j 只能从上一层的深度 j-1 转移而来。
即 dp[i][j] = dp[i-1][j-1]（硬转移，深一层
情况二：a[i-1] 为假（第 i-1 个字符不是 f）
若上一个字符不是 f，深度可以选择保持或回退：
dp[i][j] = dp[i][j+1] + dp[i-1][j]
dp[i][j+1]：从更深一层"下降"到 j（后缀和累计，允许每次回退一层）；
dp[i-1][j]：保持当前深度。
用 per（从高到低）遍历，是为了让 dp[i][j+1] 是本层已算好的值，从而把"连续回退多层"累加起来（等价于后缀和压缩
把第 n 步所有可能的最终深度求和取模输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

constexpr int N = 5e3+5, mod = 1e9+7;

int n, a[N], dp[N][N], ans;
char c;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) { cin >> c; a[i] = c == 'f'; }
    dp[0][0] = 1;
    rep(i,1,n) {
        if (a[i-1]) rep(j,1,n-1) dp[i][j] = dp[i-1][j-1];
        else per(j,i-1,0) dp[i][j] = (dp[i][j+1] + dp[i-1][j]) % mod;
    }
    rep(j,0,n-1) ans = (ans + dp[n][j]) % mod;
    cout << ans << '\n';
    return 0;
}