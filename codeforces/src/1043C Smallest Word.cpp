//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
A：i 不是最后一字符，且 s[i] != s[i+1]（当前字符与下一个不同）
B：i 是最后字符，且 s[i] == 'a'
否则输出 0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s.length()-1 != i && s[i] != s[i+1] ||
            i == s.length()-1 && s[i] == 'a') cout << 1 << ' ';
        else cout << 0 << ' ';
    }
    return 0;
}