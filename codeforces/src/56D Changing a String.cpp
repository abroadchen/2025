//
// Created by Psy.C on 2025/10/20.
//
/*
*N = 1005: 数组大小上限
ll: long long的别名
n, m: 字符串a和b的长度
dp[N][N]: 动态规划表，dp[i][j]表示a的前i个字符转换为b的前j个字符的最小操作数
a, b: 输入的两个字符串
 *
*初始化边界条件：

dp[i][0] = i: 将a的前i个字符变为空字符串需要i次删除操作
dp[0][i] = i: 将空字符串变为b的前i个字符需要i次插入操作
 *
*动态规划填表：

如果当前字符相同：dp[i][j] = dp[i-1][j-1]（无需操作）
如果不同：取三种操作的最小值加1：
替换：dp[i-1][j-1] + 1
插入：dp[i][j-1] + 1
删除：dp[i-1][j] + 1
 *输出最小编辑距离
 *
 *DFS回溯函数
 *递归终止条件：当两个字符串都处理完时返回
 *
*如果是由插入操作转移而来：

先递归处理前面的部分
输出在位置m插入字符b[m]的操作

*如果是由删除操作转移而来：

先递归处理前面的部分
输出删除位置m+1的字符的操作
 *
*如果是由替换操作转移而来：

先递归处理前面的部分
输出将位置m的字符替换为b[m]的操作
 *
*如果字符相同无需操作：

直接递归处理前面的部分
 */
#include <algorithm>
#include <ios>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;
const int N = 1005;
typedef long long ll;
ll n, m, dp[N][N];
string a, b;

void dfs(ll n, ll m) {
    if (n <= 0 && m <= 0) return;
    if (m >= 1 && dp[n][m] == dp[n][m - 1] + 1) {
        dfs(n, m - 1);
        cout << "INSERT " << m << ' ' << b[m] << '\n';
    } else if (n >= 1 && dp[n][m] == dp[n - 1][m] + 1) {
        dfs(n - 1, m);
        cout << "DELETE " << m + 1 << '\n';
    } else if (n >= 1 && m >= 1 && dp[n][m] == dp[n - 1][m - 1] + 1) {
        dfs(n - 1, m - 1);
        cout << "REPLACE " << m << ' ' << b[m] << '\n';
    } else {
        dfs(n - 1, m - 1);
    }
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> a >> b; n = a.size(), m = b.size(); a = " " + a, b = " " + b;

    rep(i,n) dp[i][0] = i;
    rep(i,m) dp[0][i] = i;
    rep(i,n) rep(j,m) {
        if (a[i] == b[j]) dp[i][j] = dp[i-1][j-1];
        else dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1;
    }
    cout << dp[n][m] << '\n';
    dfs(n, m);
    return 0;
}