//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
dp[i][j]：考虑前 i 个字符，消除掉长度为 j 的 'hard' 前缀子序列所需的最小删除代价。
str[] = " hard"：str[1]=h, str[2]=a, str[3]=r, str[4]=d，作为目标子序列的字符表
处理目标前缀长度 j=1，即破坏 "h" 这个单字符子序列。
遇到 'h'：要么删除它（代价 +a[i]），由于要把这个 h 破坏掉且前面已有的 h 也必须消除（无其他选择，只能全删），所以 dp[i][1] = dp[i-1][1] + a[i]。
非 'h'：不新增代价，dp[i][1] = dp[i-1][1]。
注：因为要完全消除 "h" 子序列，所有 'h' 都必须删，所以这里是无条件累加
对目标前缀的每个长度 j（a、r、d），遍历 i：
若当前字符 s[i] == str[j]（即这个字符可以是当前目标字母）：
两种选择：
删掉这个字符：代价 dp[i-1][j] + a[i]（保持已破坏长度 j，额外花 a[i] 删掉当前字符避免它被用进子序列）。
不删它：那它可能被用进 "hard" 子序列，为了不让它形成更长的合法前缀，只能让前面的部分是残缺的，代价为 dp[i-1][j-1]（即破坏到 j-1 长度，这样当前字符无法作为第 j 个字符补全，从而无法形成完整目标前缀）。
两者取 min。
否则（当前字符不是目标字母 j）‍：它不会造成第 j 个字符的威胁，直接继承 dp[i-1][j]。
dp[n][4] = 处理完整个串、破坏掉完整 "hard"（4 个字符）的最小代价，即为答案。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int n;
string s;
ll a[N], dp[N][5];
char str[] = " hard";
int main() {
    fast;
    cin >> n >> s; s = ' ' + s;
    rep(i,n) cin >> a[i];
    rep(i,n) {
        if (s[i] == 'h') dp[i][1] = dp[i-1][1] + a[i];
        else dp[i][1] = dp[i-1][1];
    }
    for (int j = 2; j <= 4; j++) rep(i,n) {
        if (s[i] == str[j]) dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]+a[i]);
        else dp[i][j] = dp[i-1][j];
    }
    cout << dp[n][4] << '\n';
    return 0;
}