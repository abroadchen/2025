//
// Created by Psy.C on 2026/9/3.
//
/**
num[i][j] = 从 i 到 j 这段子串的二进制数值。
如果某位是 '0'，k 里含 0 或前导，只要 k 在 1..20 就记录。注意前导零会让 k 偏小，所以只要 ≤20 就有效。
一旦 k > 20 就 break（因为继续延长只会更大
dp[i][j]：处理到位置 i，已经选用的数集合为 j 的方案数。
从 i 出发，枚举所有可能的段 [i,k]（该段数值 num[i][k] 在 1..20），把该数加入集合 j|(1<<(num[i][k]-1))，转移到 dp[k+1][...]。
【这段是核心：集合必须"不重复"才合法，因为同一数重复加入对 bitmask 无新增，会导致重复数字出现被算入，但题目通常要求好划分数互不相同——这里代码并没有显式去重判断，而是直接 OR
对所有到位置 i 结束、且已用集合恰好填满 1..j（(1<<j)-1 是低 j 位全 1）的方案求和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 80, M = 1<<20, mod = 1e9+7;

int num[N][N], dp[N][M], n;
char s[N];
void init() {
    memset(num, 0, sizeof(num));
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        int k = 0;
        for (int j = i; j < n; ++j) {
            k = (k<<1) + (s[j]-'0');
            if (k > 20) break;
            num[i][j] = k;
        }
    }
}

int main() {
    fast;
    while (cin >> n >> s) {
        init();
        int ans = 0, tot = (1<<20)-1;
        for (int i = 0; i < n; ++i) {
            dp[i][0]++;
            for (int j = 0; j <= tot; ++j) {
                if (dp[i][j]) {
                    for (int k = i; k < n; ++k) if (num[i][k])
                        dp[k+1][j|(1<<(num[i][k]-1))] = (dp[k+1][j|(1<<(num[i][k]-1))]+dp[i][j])%mod;
                }
            }
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= 20; ++j)
                ans = (ans + dp[i][(1<<j)-1])%mod;
        cout << ans << '\n';
    }
    return 0;
}