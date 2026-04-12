//
// Created by Psy.C on 2026/4/11.
//
/**
如果相邻字符相同（s[i] == s[i-1]）
尝试用一个与前后字符都不同的字符替换s[i]
遍历所有26个小写字母（'a'到'z'）
对于每个字母t，检查它是否与前一个字符s[i-1]和后一个字符s[i+1]都不同
如果找到合适的替换，将s[i]替换为t并中断内层循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s; int n = s.length();
    for (int i = 1; i < n; ++i)
        if (s[i] == s[i-1])
            for (int j = 0; j < 26; ++j) {
                char t = j + 'a';
                if (t != s[i-1] && t != s[i+1]) {
                    s[i] = t;
                    break;
                }
            }
    cout << s << '\n';
    return 0;
}