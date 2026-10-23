//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
读入一个字符串 s。
遍历字符串，统计字符 'o' 的个数到 a，其余字符（即 非 'o' 的任意字符，包括 'x' 等）个数到 b。
判断条件（满足任一即输出 YES）：
a == 0：没有 'o'；
b == 0：没有非 'o' 字符（全是 'o'）；
b % a == 0：非 o 字符数能被 o 字符数整除。
只要以上三者之一成立输出 "YES"，否则 "NO"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

string s;
int a, b;
int main() {
    fast;
    cin >> s;
    for (char i : s) { if (i == 'o') a++; else b++; }
    if (a == 0 || b == 0 || b%a == 0) cout << "YES\n"; else cout << "NO\n";
    return 0;
}