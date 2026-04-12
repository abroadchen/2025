//
// Created by Psy.C on 2026/4/12.
//
/**
dp[i][0]表示2字符子串的状态，dp[i][1]表示3字符子串的状态
st: 集合存储找到的唯一子串

如果长度>6，用最后2个字符初始化基本情况
如果长度>7，用最后3个字符初始化基本情况
将dp[ls-2]的值重置为0

从ls-3到4反向工作
对于2字符子串：检查是否可以从位置i+2或i+3扩展
对于3字符子串：检查类似的条件
确保子串不与相邻子串匹配（在某些情况下避免重复）
将有效子串添加到集合中

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int dp[10005][2];
set<string> st;
int main() {
    fast;
    cin >> s;
    if (s.length() < 6) {
        cout << "0\n";
        return 0;
    }
    int ls = s.length();
    if (ls > 6) {
        dp[ls-1][0] = 1;
        st.insert(s.substr(ls-2, 2));
    }
    if (ls > 7) {
        dp[ls-1][1] = 1;
        st.insert(s.substr(ls-3, 3));
    }
    dp[ls-2][0] = dp[ls-2][1] = 0;
    for (int i = ls-3; i >= 4; --i) {
        if (i - 2 >= 4)
            if ((i+3 < ls && dp[i+3][1]) ||
                (dp[i+2][0] && s.substr(i-1, 2) != s.substr(i+1, 2))) {
                dp[i][0] = 1;
                st.insert(s.substr(i-1, 2));
            }
        if (i - 3 >= 4)
            if (dp[i+2][0] > 0 ||
                (i + 3 < ls && dp[i+3][1] && s.substr(i-2, 3) != s.substr(i+1, 3))) {
                dp[i][1] = 1;
                st.insert(s.substr(i-2, 3));
            }
    }
    cout << st.size() << '\n';
    for (auto i : st) cout << i << '\n';
    return 0;
}