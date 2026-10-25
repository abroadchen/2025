//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
先按长度：短的排前面（s1.size() < s2.size()）。
长度相同则按字典序：s1 < s2
遍历排序后的相邻元素 s[i-1] 和 s[i]：

s[i].find(s[i-1])：在 s[i] 中查找子串 s[i-1]。
若找到，返回第一次出现的位置（≥0）。
若找不到，返回特殊值 -1。
若某个 s[i] 不包含前一个 s[i-1]（返回 -1），则排序无法构成包含链，输出 NO 并退出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (i=j; i<=k; i++)
using namespace std;

constexpr int N = 105;

bool cmp(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) return s1.size() < s2.size();
    return s1 < s2;
}

int n, i;
string s[N];
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> s[i];
    sort(s+1, s+n+1, cmp);
    rep(i,2,n) if (s[i].find(s[i-1]) == -1) {
        cout << "NO\n"; return 0;
    }
    cout << "YES\n";
    rep(i,1,n) cout << s[i] << '\n';
    return 0;
}