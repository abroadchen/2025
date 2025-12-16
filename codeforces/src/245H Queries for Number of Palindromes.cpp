//
// Created by Psy.C on 2025/12/16.
//
/*
 *f用于判断回文（初始化为false）
 *dp用于计数回文子串（初始化为0）
 *
*f[i][i] = 1：单个字符都是回文
f[i+1][i] = 1：空字符串视为回文（边界情况）
dp[i][i] = 1：单个字符构成1个回文子串
 *
*外层循环k从2到m，表示子串长度
内层循环i从1开始，确保子串s[i...j]长度为k
j = i + k - 1计算子串结束位置
*首尾字符相同s[i] == s[j]
并且内部子串s[i+1...j-1]也是回文
 *
*dp[i+1][j]：子串s[i+1...j]中的回文数
dp[i][j-1]：子串s[i...j-1]中的回文数
dp[i+1][j-1]：重复计算的部分（被减去）
f[i][j]：当前整个子串是否为回文（如果是则加1）
 *
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5001
using namespace std;


int main() {
    fast;
    string str; cin >> str;
    const int len = static_cast<int>(str.length()); char s[N];
    for (int i = 0; i < len; i++) s[i + 1] = str[i];
    const int m = static_cast<int>(strlen(s + 1));
    bool f[N][N] = {}; int dp[N][N] = {};
    for (int i = 1; i <= m; ++i) f[i][i] = f[i+1][i] = dp[i][i] = 1;
    for (int k = 2; k <= m; ++k) for (int j, i = 1; i + k - 1 <= m; ++i) {
        j = i + k - 1;
        f[i][j] = s[i] == s[j] && f[i+1][j-1];
        dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1] + f[i][j];
    }
    int n, l, r; cin >> n;
    while (n--) {
        cin >> l >> r;
        cout << dp[l][r] << '\n';
    }
    return 0;
}