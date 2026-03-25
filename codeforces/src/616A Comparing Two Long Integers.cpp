//
// Created by Psy.C on 2026/3/25.
//
/**
h1, h2 分别为字符串s1和s2的首个非零字符位置（去除前导零）
跳过字符串s1开头的所有'0'字符，找到第一个非零字符的位置
跳过字符串s2开头的所有'0'字符，找到第一个非零字符的位置

比较两个数字的有效位数（去掉前导零后的长度）
如果有效位数相同
逐位比较两个数字字符串
如果发现不同字符
s1当前字符小于s2当前字符，输出<
s1当前字符大于s2当前字符，输出>
所有字符都相等，输出=
如果有效位数不同，则位数多的数字更大
s1位数少输出<，否则输出>
O(max(|s1|, |s2|))，即线性时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s1, s2;
int main() {
    fast;
    cin >> s1 >> s2;
    int l1 = s1.length(), l2 = s2.length(), h1 = 0, h2 = 0;
    while (s1[h1] == '0') h1++;
    while (s2[h2] == '0') h2++;
    if (l1 - h1 == l2 - h2) {
        for (int i = 0; i < l1 - h1; ++i)
            if (s1[h1 + i] != s2[h2 + i]) {
                if (s1[h1 + i] < s2[h2 + i]) cout << '<';
                else cout << '>';
                return 0;
            }
        cout << '=';
        return 0;
    }
    l1 - h1 < l2 - h2 ? cout << '<' : cout << '>';
    return 0;
}