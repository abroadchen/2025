//
// Created by Psy.C on 2026/2/1.
//
/**
 * 当前字符为'0'时：dp[i][0]表示以0结尾的状态
*字符'1'时的转移规则：
状态1：只能从状态3转移
状态2：可以从状态0或1转移
 *字符'2'时：状态4只能从状态3转移
 *通配符'*'时：状态3可从状态2、4、3转移
 *通配符'?'时：可以代表任意字符，同时更新所有可能的状态
 *
*将索引减1（指向最后一个有效位置）
输出最终结果：状态0、1、3的总和
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
#define mod 1000000007
using namespace std;


int main() {
    fast;
    char str[N]; cin >> str;
    int len = static_cast<int>(strlen(str));
    ll dp[N][5]={};
    if (str[0] == '0') dp[0][0] = 1;
    else if (str[0] == '1') dp[0][2] = 1;
    else if (str[0] == '*') dp[0][3] = 1;
    else if (str[0] == '?') {
        dp[0][0] = 1; dp[0][2] = 1; dp[0][3] = 1;
    }
    for (int i = 1; i < len; ++i) {
        if (str[i] == '0') dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % mod;
        else if (str[i] == '1') {
            dp[i][1] = dp[i-1][3];
            dp[i][2] = (dp[i-1][0] + dp[i-1][1]) % mod;
        }
        else if (str[i] == '2') dp[i][4] = dp[i-1][3];
        else if (str[i] == '*') dp[i][3] = (dp[i-1][2] + dp[i-1][4] + dp[i-1][3]) % mod;
        else if (str[i] == '?') {
            dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % mod;
            dp[i][1] = dp[i-1][3];
            dp[i][2] = (dp[i-1][0] + dp[i-1][1]) % mod;
            dp[i][4] = dp[i-1][3];
            dp[i][3] = (dp[i-1][2] + dp[i-1][4] + dp[i-1][3]) % mod;
        }
    }
    len--;
    cout << (dp[len][0] + dp[len][1] + dp[len][3]) % mod << '\n';
    return 0;
}