//
// Created by Psy.C on 2025/10/13.
//
/*
*n：字符串长度
ans1, ans2：两种情况下的不同字符计数
s：输入的原始字符串
s1, s2：两种目标模式字符串
 *
*创建交替模式字符串s1：

偶数位置(0,2,4...)放'0'
奇数位置(1,3,5...)放'1'
例如：当n=5时，s1="01010"
 *
*创建两种可能的目标模式：

s1：在原来模式前加'1'，变成"101010"
s2：在原来模式后加'0'，变成"010100"
 *
 *
 */
#include <ios>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n, ans1, ans2;
string s, s1, s2;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (!(i % 2)) s1 += '0';
        else s1 += '1';
    }
    s2 = s1 + '0';
    s1 = '1' + s1;
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s[i]) ans1++;
        else ans2++;
    }
    cout << min(ans1, ans2);
    return 0;
}