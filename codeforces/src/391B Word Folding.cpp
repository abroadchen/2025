//
// Created by Psy.C on 2026/1/29.
//
/**
 *
*s[M]：存储输入字符串
dp[N]：DP数组，初始化为0，dp[i] 表示以位置 i 结尾的最长回文子序列长度
ans：记录最大值，初始为0
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
#define M 1005
using namespace std;


int main() {
    fast;
    char s[M]; cin >> s;
    int dp[N]={}, ans = 0;
    const int len = static_cast<int>(strlen(s));
    for (int i = 0; i < len - 1; ++i) for (int j = i + 1; j < len; j += 2) {//只考虑奇数间隔
        if (s[i] == s[j]) dp[j] = dp[i] + 1;//如果首尾字符相同
        ans = max(ans, dp[j]);
    }
    cout << ans + 1 << '\n';//记录的是中间的连接数，实际长度需要加1
    return 0;
}