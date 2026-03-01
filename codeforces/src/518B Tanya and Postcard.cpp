//
// Created by Psy.C on 2026/2/28.
//
/**
s, t：输入的两个字符串
mp：字符计数映射，存储字符串t中每个字符的出现次数

c1：精确匹配的字符数（大小写完全相同）
c2：大小写不同的匹配字符数
遍历字符串s，如果字符s[i]在t中存在（mp[s[i]] > 0）：
增加c1计数
减少对应字符的计数（表示已使用）
将s[i]标记为'-'（表示已匹配）

只处理未被第一次匹配标记为'-'的字符
如果s[i]是小写字母且t中有对应的大写字母：
使用该大写字母，减少计数，增加c2
如果s[i]是大写字母且t中有对应的小写字母：
使用该小写字母，减少计数，增加c2

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s, t;
map<char, int> mp;
int main() {
    fast;
    cin >> s >> t;
    for (int i = 0; i < t.length(); ++i) mp[t[i]]++;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < s.length(); ++i)
        if (mp[s[i]] > 0) {
            c1++;
            mp[s[i]]--;
            s[i] = '-';
        }
    for (int i = 0; i < s.length(); ++i) if (s[i] != '-') {
        if (islower(s[i]) && mp[toupper(s[i])] > 0)
            mp[toupper(s[i])]--, c2++;
        else if (isupper(s[i]) && mp[tolower(s[i])] > 0)
            mp[tolower(s[i])]--, c2++;
    }
    cout << c1 << ' ' << c2;
    return 0;
}