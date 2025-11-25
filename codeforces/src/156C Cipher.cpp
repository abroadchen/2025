//
// Created by Psy.C on 2025/11/24.
//
/*
*状态定义: dfs(s, k) 表示ASCII值和为s、长度为k的字符串数量
边界条件:
如果已经计算过该状态，直接返回结果
如果s > 25*k，说明平均每个字符的ASCII值超过'z'，不可能实现
如果k=0，只有一种方案（空字符串）
状态转移:
枚举第一个字符的ASCII值（相对于'a'的偏移量0-25）
递归计算剩余部分的方案数
累加所有可能的方案

s - i: 剩余字符需要达到的ASCII值总和
k - 1: 剩余需要构造的字符串长度
 *
*计算其各字符相对于'a'的ASCII值之和
调用dfs(sum, length)计算所有字典序小于等于该字符串的字符串数量
减1得到严格小于的字符串数量
 *
*时间复杂度: O(sum × length × 26) with memoization
空间复杂度: O(sum × length)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) ((int) x.size())
using namespace std;

typedef long long ll;
constexpr int N = 3e3, mod = 1e9+7;
ll dp[N][N];

ll add(const ll a, const ll b) { return (a + b) % mod; }

ll dfs(const int s, const int k) {
    if (dp[s][k]) return dp[s][k];
    if (s > 25 * k) return 0;
    if (k == 0) return 1;
    ll& memo = dp[s][k], res = 0;
    for (int i = 0; i <= min(s, 25); ++i) res = add(res,
        dfs(s - i, k - 1));
    return memo = res;
}

int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        string s; cin >> s; int sum = 0;
        for (const char c : s) sum += c - 'a';
        cout << dfs(sum, sz(s)) - 1 << '\n';
    }
    return 0;
}