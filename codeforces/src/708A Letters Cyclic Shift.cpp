//
// Created by Psy.C on 2026/4/19.
//
/**
从左往右找到第一个不是'a'的字符位置
这是为了处理借位操作
'a' 映射到 'a'（不变）
'b' 映射到 'a'，'c' 映射到 'b'，以此类推
即每个字符映射到它的前一个字符
从第一个非'a'字符开始处理
遇到'a'就停止（避免借位）
将每个字符替换为其前一个字符
如果字符串全是'a'（k等于字符串长度）
将最后一个字符改为'z'
这相当于借位操作（类似999-1=998，但这里是aaa-1=...z）
O(n): 遍历字符串一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
map<char,char> mp;
int main() {
    fast;
    cin>>s;
    int k = 0;
    for (k = 0; k < s.size(); ++k)
        if (s[k] != 'a') break;
    mp['a'] = 'a';
    for (char i = 'b'; i <= 'z'; ++i) mp[i] = i-1;
    for (int i = k; i < s.size(); ++i) {
        if (s[i] == 'a') break;
        s[i] = mp[s[i]];
    }
    if (k == s.size()) s[s.size()-1] = 'z';
    cout << s << '\n';
    return 0;
}