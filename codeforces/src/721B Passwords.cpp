//
// Created by Psy.C on 2026/4/23.
//
/**
n：字符串总数
k：分组参数
s[107]：存储n个字符串的数组（最多107个）
ss：目标字符串
sa：长度小于ss的字符串数量
sm：长度等于ss的字符串数量
mn（最小时间）：sa + 1 + (sa/k)*5
sa：比目标短的字符串数量
1：找到目标字符串需要的时间
(sa/k)*5：每k个字符串检查一次，每次花费5秒
mx（最大时间）：sa + sm + (sa+sm-1)/k*5
sa + sm：比目标短或相等的字符串总数
(sa+sm-1)/k*5：考虑所有可能的检查时间

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k;
string s[107], ss;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    cin >> ss;
    sort(s + 1, s + n + 1, [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    int sa = 0, sm = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i].length() > ss.length()) break;
        if (s[i].length() < ss.length()) sa++;
        if (s[i].length() == ss.length()) sm++;
    }
    int mn = sa + 1 + sa/k*5, mx = sa + sm + (sa+sm-1)/k*5;
    cout << mn << ' ' << mx << '\n';
    return 0;
}