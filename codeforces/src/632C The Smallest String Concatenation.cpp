//
// Created by Psy.C on 2026/3/30.
//
/**
如果 a + b < b + a，说明字符串a应该排在字符串b前面
如果 a + b > b + a，说明字符串b应该排在字符串a前面
排序：O(n log n × L)，其中L是平均字符串长度
输出：O(总字符数)
总体：O(n log n × L)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e4+5;
int n;
string s[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    sort(s + 1, s + n + 1, [](const string &a, const string &b) {
        return a + b < b + a;
    });
    for (int i = 1; i <= n; ++i) cout << s[i];
    cout << '\n';
    return 0;
}