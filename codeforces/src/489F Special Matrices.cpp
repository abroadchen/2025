//
// Created by Psy.C on 2026/2/18.
//
/**
时间复杂度：O(n³)
空间复杂度：O(n²)

总'1'的个数计算：

我们考虑前i行（总共要放i行）
每行放2个'1'，所以总共放了 i * 2 个'1'
按列统计'1'的个数：

s0列：每列0个'1' → 贡献 0 个'1'
s1列：每列1个'1' → 贡献 s1 个'1'
s2列：每列2个'1' → 贡献 2*s2 个'1'
总'1'个数 = 0*s0 + 1*s1 + 2*s2
i*2 = 0 + s1 + 2*s2
i*2 = j + 2*s2  (因为s1=j)
2*s2 = i*2 - j
s2 = (i*2 - j) / 2

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2501;
int n, m, mod, p[N], dp[N][N];
char maz[N][N];
signed main() {
    fast;
    cin >> n >> m >> mod;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> maz[i][j];
            p[j] += maz[i][j] == '1';//每列'1'的个数
        }
    int x = 0, y = 0;
    for (int i = 1; i <= n; ++i) {
        if (p[i] == 1) x++;//有1个'1'的列的数量
        else if (p[i] == 2) y++;//有2个'1'的列的数量
    }
    dp[x][y] = 1;//x列有1个'1'，y列有2个'1'
    for (int i = m; i <= n; ++i)//枚举行数从m到n
        for (int j = 0; j <= n; j += 2) {
            //有1个'1'的列数 有2个'1'的列数 有0个'1'的列数
            const int s1 = j, s2 = (i*2-j)/2, s0 = n - s1 - s2;
            if (s0 < 0 || s1 < 0 || s2 < 0) continue;
            if (s0 > 0 && s1 > 0) {//从0个'1'的列和1个'1'的列各选一个，形成新的2个'1'的列
                dp[s1][s2+1] += dp[s1][s2]*s0%mod*s1%mod;
                dp[s1][s2+1] %= mod;
            }
            if (s0 >= 2) {//从2个0个'1'的列中选2个，形成2个新的1个'1'的列
                dp[s1+2][s2] += dp[s1][s2]*(s0*(s0-1)/2%mod)%mod;
                dp[s1+2][s2] %= mod;
            }
            if (s1 >= 2) {//从2个1个'1'的列中选2个，形成2个新的2个'1'的列
                dp[s1-2][s2+2] += dp[s1][s2]*(s1*(s1-1)/2%mod)%mod;
                dp[s1-2][s2+2] %= mod;
            }
        }
    cout << dp[0][n]%mod << '\n';//所有列都有2个'1'的方案数
    return 0;
}