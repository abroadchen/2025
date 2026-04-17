//
// Created by Psy.C on 2026/4/16.
//
/**
char a[] = "AbdHIMOopqTUVvWwXxY"：定义源字符数组，包含19个字符
char b[] = "AdbHIMOoqpTUVvWwXxY"：定义目标字符数组，包含19个字符
char mp[300];：定义字符映射数组，用于存储字符转换关系
string s;：定义字符串变量s，用于存储输入字符串

mp[s[i]]：获取当前字符s[i]的映射字符
s[s.length() - i - 1]：获取字符串末尾对应的字符（回文位置）
if (mp[s[i]] != s[s.length() - i - 1])：如果映射字符不等于对应位置的字符

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char a[] = "AbdHIMOopqTUVvWwXxY", b[] = "AdbHIMOoqpTUVvWwXxY";
char mp[300];
string s;
int main() {
    fast;
    for (int i = 0; i < 19; ++i) mp[a[i]] = b[i];//a[i]映射到b[i]
    cin >> s;
    for (int i = 0; i < s.length(); ++i)
        if (mp[s[i]] != s[s.length() - i - 1]) {
            cout << "NIE\n";
            return 0;
        }
    cout << "TAK\n";
    return 0;
}