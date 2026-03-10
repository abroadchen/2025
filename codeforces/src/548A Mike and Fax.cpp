//
// Created by Psy.C on 2026/3/9.
//
/**
s：输入的字符串
k：分组数量
外层循环：
i = 0：起始位置
i += s.size()/k：每次跳转到下一个分组的起始位置
s.size()/k：每个分组的长度
内层循环：
j = i：分组的起始位置
l = i+s.size()/k-1：分组的结束位置
j <= l：检查直到中心位置
j++, l--：从两端向中心移动
核心逻辑：
if (s[j] != s[l])：如果分组的第j个字符和第l个字符不相等
输出"NO"并结束程序
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int k;
int main() {
    fast;
    cin >> s >> k;
    if (s.size()%k!=0) return cout << "NO", 0;
    for (int i = 0; i<s.size(); i+=s.size()/k)
        for (int j=i, l=i+s.size()/k-1; j<=l; j++, l--)
            if (s[j] != s[l])
                return cout << "NO", 0;
    cout << "YES";
    return 0;
}