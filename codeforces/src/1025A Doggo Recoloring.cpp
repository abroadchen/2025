//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
如果字符串只有一个字符，代码直接输出 Yes（有重复）
枚举所有 i < j 的字符对。
一旦发现任意一对字符相等（s[i] == s[j]），立即输出 Yes 并结束。
若所有字符两两不同，循环结束输出 No

strlen() 遇到 \0（空字符）就会截断，只返回到 \0 之前的长度；
而 length() / size() 能返回字符串的真实长度，即使字符串中间含有 \0 也不受影响
想强调"这是字符串"时用 length()；
在 STL 算法/容器泛型代码里用 size() 保持风格统一
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    int len = s.length();
    if (len == 1) { cout << "Yes\n"; return 0; }
    for (int i = 0; i < len; i++)
        for (int j = i+1; j < len; j++) if (s[i] == s[j]) {
            cout << "Yes\n"; return 0;
        }
    cout << "No\n";
    return 0;
}