//
// Created by Psy.C on 2026/4/2.
//
/**
n: 扩展长度
k: 字符种类数
s[N/2]: 输入字符串
dp[N]: DP数组，dp[i]表示前i个字符的不同子序列数量
cnt[M]: 记录每个字母最后出现的位置
q: 优先队列（使用负数模拟最小堆）
dp[0] = 1: 空字符串有1种子序列（空子序列本身）
dp[i] = dp[i-1]*2%mod: 如果没有重复，每个已有的子序列都可以选择包含或不包含s[i]
idx = s[i] - 'a': 字符转换为索引
if (cnt[idx]): 如果该字符之前出现过
dp[i] = (dp[i] - dp[cnt[s[i]-'a']-1]+mod)%mod: 减去重复计算的子序列
dp[cnt[s[i]-'a']-1] 是上一次出现位置之前的所有子序列数量
cnt[s[i]-'a'] = i: 更新该字符的最后出现位置
将每个字符的最后出现位置加入最小堆（用负数）
这样可以快速找到最早出现的字符位置
扩展处理n个虚拟字符
dp[i] = dp[i-1]*2%mod: 类似基本计算
tp = -q.top(): 获取最早出现的字符位置
if (tp) dp[i] = (dp[i] - dp[tp-1] + mod)%mod: 减去重复子序列
q.push(-i): 将当前位置加入队列
输出最终结果：前len+n个位置的不同子序列数量
时间复杂度：O((len+n)log k)，空间复杂度：O(len+n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e6+5, M = 26, mod = 1e9+7;
int n, k;
char s[N/2];
ll dp[N], cnt[M];
priority_queue<int> q;
int main() {
    fast;
    cin >> n >> k; scanf("%s", s + 1);
    int len = strlen(s + 1); dp[0] = 1;
    for (int i = 1; i < len+1; ++i) {
        dp[i] = dp[i-1]*2%mod;
        int idx = s[i] - 'a';
        if (cnt[idx])
            dp[i] = (dp[i] - dp[cnt[s[i]-'a']-1]+mod)%mod;
        cnt[s[i]-'a'] = i;
    }
    for (int i = 0; i < k; ++i) q.push(-cnt[i]);
    for (int i = len + 1; i < len + n + 1; ++i) {
        dp[i] = dp[i-1]*2%mod;
        int tp = -q.top(); q.pop();
        if (tp) dp[i] = (dp[i] - dp[tp-1] + mod)%mod;
        q.push(-i);
    }
    cout << dp[len+n] << '\n';
    return 0;
}