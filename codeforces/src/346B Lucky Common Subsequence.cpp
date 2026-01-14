//
// Created by Psy.C on 2026/1/13.
//
/**
 * DP数组，存储字符串状态
 *j是匹配指针，nxt是KMP的失败函数数组
 *从第二个字符开始遍历模式串g
 *
*外层嵌套循环：遍历s和t的所有位置
i：s的当前位置（1到s.size()）
j：t的当前位置（1到t.size()）
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 110
using namespace std;


int main() {
    fast;
    string s, t, g, dp[N][N][N], ans; cin >> s >> t >> g;
    ll j = 0, nxt[N];
    for (int i = 1; i < g.size(); ++i) {
        while (j > 0 && g[i] != g[j]) j = nxt[j-1];//回退j直到匹配或j=0
        if (g[i] == g[j]) nxt[i] = ++j;//如果匹配成功，j增加并更新nxt[i]
    }
    for (int i = 1; i <= s.size(); ++i) for (j = 1; j <= t.size(); ++j) {
        for (int k = 0; k < g.size(); ++k) {//遍历模式串g的匹配状态
            if (s[i-1] == t[j-1]) {//s和t的当前字符相同
                const char p = s[i-1];//获取匹配的字符
                ll len = k;//当前在模式串g中的匹配位置
                while (len > 0 && p != g[len]) len = nxt[len-1];
                if (p == g[len]) len++;//如果字符匹配，增加匹配长度
                if (dp[i][j][len].size() < dp[i-1][j-1][k].size() + 1)//新方案更长
                    dp[i][j][len] = dp[i-1][j-1][k] + p;//更新DP状态
            }
            if (dp[i][j][k].size() < dp[i-1][j][k].size())//从上方转移
                dp[i][j][k] = dp[i-1][j][k];//继承s前一个位置的状态
            if (dp[i][j][k].size() < dp[i][j-1][k].size())//从左方转移
                dp[i][j][k] = dp[i][j-1][k];
        }
    }
    //遍历所有可能的匹配状态 如果找到更长的公共子序列
    for (int i = 0; i < g.size(); ++i) if (ans.size() < dp[s.size()][t.size()][i].size()) {
        ans = dp[s.size()][t.size()][i];
    }
    if (ans.empty()) cout << 0; else cout << ans;
    return 0;
}