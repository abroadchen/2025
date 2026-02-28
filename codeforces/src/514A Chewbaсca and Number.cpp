//
// Created by Psy.C on 2026/2/28.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
string s;
int a[N], j = 1;//起始处理位置（默认从位置1开始）
int main() {
    fast;
    cin >> s;
    const int len = s.size();
    for (int i = 1; i <= len; ++i)
        a[i] = s[i-1] - '0';//处理后的数字数组
    if (a[1] == 9) j = 2;
    for (int i = j; i <= len; ++i)
        if (a[i] >= 5) a[i] = 9 - a[i];//对称变换
    for (int i = 1; i <= len; ++i) cout << a[i];
    return 0;
}