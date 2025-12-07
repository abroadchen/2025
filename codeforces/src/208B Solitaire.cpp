//
// Created by Psy.C on 2025/12/6.
//
/*
*s[N][5]：存储每张纸牌的颜色和数值（最多4个字符+'\0'）
dp[N][N][N][N]：记忆化搜索数组，用于记录状态是否已访问
*l：当前剩余纸牌数量
s1, s2, s3：三根柱子顶部纸牌的编号
 *如果只剩一张牌，说明已经成功收集所有牌，返回1（成功）
 *记忆化剪枝：如果这个状态已经访问过且失败，直接返回0
 *
*如果柱子2顶牌和柱子3顶牌颜色相同(s[s2][0] == s[s3][0])或数值相同(s[s2][1] == s[s3][1])
则可以将柱子2的牌移到柱子3上
移动后状态变为：剩余l-1张牌，新的三根柱子顶牌分别是：第(l-3)张、原来的s1、原来的s3
 *
*如果剩余牌数>=4且柱子3顶牌和第(l-3)张牌颜色相同或数值相同
则可以将柱子3的牌移到第(l-3)张牌所在的柱子上
移动后状态变为：剩余l-1张牌，新的三根柱子顶牌分别是：原来的s3、原来的s1、原来的s2
 *
 *标记当前状态为已访问且失败，返回0
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 55
using namespace std;

char s[N][5];
int dp[N][N][N][N];

int dfs(const int l, const int s1, const int s2, const int s3) {
    if (l == 1) return 1;
    if (dp[l][s1][s2][s3] == 1) return 0;
    if (s[s2][0] == s[s3][0] || s[s2][1] == s[s3][1]) {
        if (dfs(l - 1, l - 3, s1, s3)) return 1;
    }
    if (l >= 4 && s[s3][0] == s[l-3][0] || s[s3][1] == s[l-3][1]) {
        if (dfs(l - 1, s3, s1, s2)) return 1;
    }
    dp[l][s1][s2][s3] = 1;
    return 0;
}

int main() {
    fast;
    int n; cin >> n;
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; ++i) cin >> s[i];
    if (dfs(n, n - 2, n - 1, n) == 1) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}