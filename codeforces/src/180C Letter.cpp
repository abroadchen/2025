//
// Created by Psy.C on 2025/12/1.
//
/*
*dp[i][1]：当前字符保持大写，需要从前一个字符的小写或大写状态转移而来，都需要1次操作（因为字符本来是大写，保持它需要"操作"）
dp[i][0]：当前字符转为小写，只能从前一个字符的小写状态转移而来，不需要额外操作
 *
*dp[i][1]：当前字符转为大写，可以从任意前一个状态转移而来，不需要额外操作
dp[i][0]：当前字符保持小写，只能从前一个字符的小写状态转移而来，需要1次操作
 */
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
using namespace std;

int n, dp[N][2];
char s[N];

int main() {
    fast;
    cin >> s; n = static_cast<int>(strlen(s));
    dp[0][0] = dp[0][1] = 0;
    if (isupper(s[0])) dp[0][1] = 1;
    else dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        if (isupper(s[i])) {
            dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + 1;
            dp[i][0] = dp[i-1][0];
        } else {
            dp[i][1] = min(dp[i-1][0], dp[i-1][1]);
            dp[i][0] = dp[i-1][0] + 1;
        }
    }
    cout << min(dp[n-1][0], dp[n-1][1]) << '\n';//最少操作数
    return 0;
}