//
// Created by Psy.C on 2026/10/10.
//
/**
这段字符串表示连续 5 年（60 个月）‍的每个月天数，其中只包含一个闰年（2 月有 29 天的那一年），其余 4 年是平年（2 月 28 天）。年份只差一天，不影响月份天数分布。

正常平年：每月 31,28,31,30,31,30,31,31,30,31,30,31
闰年：31,29,31,30,31,30,31,31,30,31,30,31
5 年拼接：平 平 闰 平 平
第一行读入 n（计数，但代码里实际上没使用），然后整行读入 s
用 string::find 检查子串 s 是否作为 m 的连续子串出现
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string m = "31 28 31 30 31 30 31 31 30 31 30 31 "
           "31 28 31 30 31 30 31 31 30 31 30 31 "
           "31 29 31 30 31 30 31 31 30 31 30 31 "
           "31 28 31 30 31 30 31 31 30 31 30 31 "
           "31 28 31 30 31 30 31 31 30 31 30 31 ";
string s;
int main() {
    fast;
    int n; cin >> n; cin.ignore();
    getline(cin, s);
    if (m.find(s) != string::npos) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}