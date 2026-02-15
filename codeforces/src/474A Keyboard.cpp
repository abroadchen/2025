//
// Created by Psy.C on 2026/2/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string get(const string& s1, const char c) {
    string s = "qwertyuiopasdfghjkl;zxcvbnm,./", ans;
    const int len = s1.length();
    for (int i = 0; i < len; ++i) {
        const int idx = s.find(s1[i]);//s中查找当前字符s1[i]的位置索引
        if (c == 'R') ans += s[idx-1];//键盘上对应字符左边的字符添加到结果中
        else ans += s[idx+1];
    }
    return ans;//转换后的字符串
}

string s2;
char c;

int main() {
    fast;
    cin >> c >> s2; cout << get(s2,c);
    return 0;
}