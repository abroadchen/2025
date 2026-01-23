//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <cctype>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    ll m = 0, ans = 0;
    for (ll i = 0; i < s.size(); ++i) if (s[i] == '^') m = i;// 存储支点('^')的索引
    //对字符串中的每个数字（重量) 力矩 = 重量 × 距离
    for (ll i = 0; i < s.size(); ++i) if (isdigit(s[i])) {
        ans += (s[i] - '0') * (i - m);//距离支点的距离（左侧为负，右侧为正）
    }
    if (ans == 0) cout << "balance\n";
    else if (ans > 0) cout << "right\n";
    else cout << "left\n";
    return 0;
}