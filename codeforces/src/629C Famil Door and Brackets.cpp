//
// Created by Psy.C on 2026/3/29.
//
/**
dp[i][j] 表示长度为i且最小平衡值为j的有效括号序列的方案数
dp[0][0] = 1: 基础情况 - 空序列有一种方案
对于每个位置i，我们可以添加开括号或闭括号
dp[i][0] = dp[i-1][1]: 当处于0层级时，只能从1层级用一个闭括号转移而来
dp[i][j] = dp[i-1][j+1] + dp[i-1][j-1]: 从前一状态转移

n（总长度），m（给定前缀的长度），s（前缀字符串）
计算处理前缀后的当前平衡值(cnt)
跟踪前缀过程中达到的最小平衡值(mn)
len = n - m: 剩余待填充的字符数
双重循环遍历所有可能的分割方式
i: 第一部分的字符数
j: 第一部分后的平衡值
检查条件：
j + mn < 0: 如果最小值小于0则无效（不能出现负平衡）
len - i < j + cnt: 字符不够达到所需的最终平衡
添加有效组合：dp[i][j] * dp[len-i][j+cnt]

1. 放置开括号 (
如果在位置i放置开括号，它的贡献是+1
要使最终平衡值为j，那么前i-1个字符的平衡值应该是 j-1
所以前驱状态是 dp[i-1][j-1]
2. 放置闭括号 )
如果在位置i放置闭括号，它的贡献是-1
要使最终平衡值为j，那么前i-1个字符的平衡值应该是 j+1
所以前驱状态是 dp[i-1][j+1]

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2005, mod = 1e9+7, inf = 0x3f3f3f3f;

void add(ll &x, ll y) { x += y; x %= mod; }

ll dp[N][N];
void get() {
    dp[0][0] = 1;
    for (int i = 1; i <= N-5; ++i) {
        dp[i][0] = dp[i-1][1];
        for (int j = 1; j <= i; ++j)
            add(dp[i][j], (dp[i-1][j+1]+dp[i-1][j-1])%mod);
    }
}
int n, m;
string s;
int main() {
    fast; get();
    cin >> n >> m >> s;
    int cnt = 0, mn = inf;
    for (int i = 0; i < m; ++i) {
        if (s[i] == '(') cnt++; else cnt--;
        mn = min(mn, cnt);
    }
    int len = n - m; ll ans = 0;
    for (int i = 0; i <= len; ++i)
        for (int j = 0; j <= i; ++j) {
            if (j + mn < 0 || len - i < j + cnt) continue;
            add(ans, dp[i][j]*dp[len-i][j+cnt]);
        }
    cout << ans << '\n';
    return 0;
}