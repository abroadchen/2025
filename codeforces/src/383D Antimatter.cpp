//
// Created by Psy.C on 2026/1/27.
//
/**
* dp[0][inf-val[0]] = 1: 第一个元素取负值时的方案数为1
inf-val[0] 表示和为 -val[0] 的状态（加上偏移量）
dp[0][inf+val[0]] = 1: 第一个元素取正值时的方案数为1
inf+val[0] 表示和为 +val[0] 的状态（加上偏移量）
dp[0][inf] = 1: 第一个元素取0（不操作）时的方案数为1
inf 表示和为 0 的状态（加上偏移量）

如果 j - val[i] >= 0，说明可以从 j-val[i] 状态转移过来
这表示从前一个和为 j-val[i] 的状态，加上当前元素 val[i]，得到和为 j 的状态
将 dp[i-1][j-val[i]] 的方案数加到 dp[i][j]

如果 j + val[i] <= N-1，说明可以从 j+val[i] 状态转移过来
这表示从前一个和为 j+val[i] 的状态，减去当前元素 val[i]，得到和为 j 的状态
将 dp[i-1][j+val[i]] 的方案数加到 dp[i][j]
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 20001
#define inf 10000//偏移量，用于处理负数索引
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> val(n);
    for (int i = 0; i < n; ++i) cin >> val[i];
    //n 行，每行有 N 个 long long 类型的元素
    vector dp(n, vector<ll>(N, 0));//处理前 i 个元素，当前和为 j-inf 时的方案数
    dp[0][inf-val[0]] = 1, dp[0][inf+val[0]] = 1, dp[0][inf] = 1;
    for (int i = 1; i < n; ++i) for (int j = 0; j <= N-1; ++j) {//处理每个元素 枚举所有可能的和值
        if (j == inf) dp[i][j]++;//对当前元素不操作 方案数加1
        if (j - val[i] >= 0) dp[i][j] += dp[i-1][j-val[i]];//从前一个状态减去当前值转移而来
        if (j + val[i] <= N-1) dp[i][j] += dp[i-1][j+val[i]];
        dp[i][j] %= mod;
    }
    ll tot = -n;//初始状态包含了n个不操作的情况
    for (int i = 0; i < n; ++i) tot = (tot + dp[i][inf]) % mod;//处理前 i 个元素，和为0的方案数
    cout << tot << '\n';
    return 0;
}