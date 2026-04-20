//
// Created by Psy.C on 2026/4/19.
//
/**
n: 字符串数量
a[N]: 每个字符串的翻转代价
dp[i][j]: 处理前i个字符串，第i个字符串状态为j时的最小代价
s[i][0]: 第i个字符串的原始形态
s[i][1]: 第i个字符串的翻转形态

j: 前一个字符串的状态（0=未翻转，1=已翻转）
k: 当前字符串的状态（0=未翻转，1=已翻转）
s[i][k] >= s[i-1][j]: 当前字符串必须字典序不小于前一个字符串
dp[i][k] = min(dp[i][k], dp[i-1][j]+k*a[i]): 更新最小代价
dp[i-1][j]: 前一个状态的代价
k*a[i]: 如果翻转当前字符串，需要加上代价
ans = min(dp[n][0], dp[n][1]): 取最后状态的最小代价
如果无解（代价仍为inf），输出-1
O(n × 2 × 2 × 字符串比较): 约为O(n × m)，其中m是字符串平均长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = 1e18;
int n, a[N];
ll dp[N][2];
string s[N][2];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[0][0] = dp[0][1] = 0;//初始状态：前0个字符串的代价都为0
    for (int i = 1; i <= n; ++i) {
        cin >> s[i][0]; s[i][1] = s[i][0];//复制原始字符串
        dp[i][0] = dp[i][1] = inf;
        ranges::reverse(s[i][1]);//翻转字符串
        for (int j = 0; j <= 1; ++j)
            for (int k = 0; k <= 1; ++k)
                if (s[i][k] >= s[i-1][j])
                    dp[i][k] = min(dp[i][k], dp[i-1][j]+k*a[i]);
    }
    ll ans = min(dp[n][0], dp[n][1]);
    cout << (ans == inf ? -1 : ans) << '\n';
    return 0;
}