//
// Created by Psy.C on 2026/3/2.
//
/**
a[N]：计数数组，用于统计某些位置的操作次数
m：操作数量
s：输入字符串

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1;

int a[N], m;
string s;
int main() {
    fast;
    cin >> s >> m;
    for (int i = 0, x; i < m; ++i) {
        cin >> x;
        a[x]++;//位置x被操作的次数
    }
    int len = s.size(), sum = 0;
    for (int i = 0; i <= len/2; ++i) {
        sum += a[i];
        if (sum % 2) swap(s[i-1], s[len-i]);//翻转该对称位置的字符
    }
    cout << s << '\n';
    return 0;
}