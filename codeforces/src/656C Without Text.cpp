//
// Created by Psy.C on 2026/4/8.
//
///O(|s|)，其中 |s| 是字符串长度，需要遍历每个字符一次
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int ans;
int main() {
    fast;
    cin >> s;
    for (const char p : s) {//遍历字符串中的每个字符
        if ('A' <= p && p <= 'Z')
            ans += p - 'A' + 1;//加上其在字母表中的位置
        if ('a' <= p && p <= 'z')
            ans -= p - 'a' + 1;
    }
    cout << ans << '\n';
    return 0;
}