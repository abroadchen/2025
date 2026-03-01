//
// Created by Psy.C on 2026/3/1.
//
///s[i]-'a'  // 将字符转换为0-25的索引
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[26];
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        s[i] = tolower(s[i]);
        a[s[i]-'a'] = 1;//标记该字母已出现
    }
    for (int i = 0; i < 26; ++i)
        if (a[i] == 0) {//有任何字母未出现
            cout << "NO\n";
            return 0;
        }
    cout << "YES\n";
    return 0;
}