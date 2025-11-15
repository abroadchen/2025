//
// Created by Psy.C on 2025/11/15.
//
/*
*s：存储输入字符串
m：维护某种状态的变量
dp[N]：动态规划数组
 *
*对DP数组进行更新：
从j = m + s.size()到j = m + 1进行反向遍历
每次将dp[j]和dp[j-1]相加并取模
结果存储在dp[j-1]中
这实际上是前缀和的逆向操作或组合数的递推
 *
 *
 */
#include <iostream>
using namespace std;

const int N = 6005, mod = 1e6+3;
string s;
int m, dp[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s; m = 2 * s.size();
    dp[m] = 1;
    for (int i = 0; i < s.size(); ++i) {//遍历字符串的每个字符
        if (s[i] < '0') {//如果当前字符不是数字
            if (s[i] == '+' || s[i] == '-' ||
                (i && s[i - 1] >= '0')) m--;//不是第一个字符且前一个字符是数字
            else { cout << 0; return 0; }
        } else if (s[i + 1] < '0') {//当前字符是数字，且下一个字符不是数字 当前数字是某个数字序列的结尾
            for (int j = m + s.size(); j > m; --j)
                dp[j - 1] = (dp[j] + dp[j - 1]) % mod;
        }
    }
    cout << dp[m];
    return 0;
}