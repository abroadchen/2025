//
// Created by Psy.C on 2026/10/4.
//
/**
如果是小写字母且当前字母未出现过，增加数量
如果是大写字母，统计最大数量并清空计数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

string s;
int a[128];
ll n, len, mx;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (islower(s[i]) && a[s[i]] == 0) len++, a[s[i]] = 1;
        if (isupper(s[i])) mx = max(mx, len), len = 0, memset(a, 0, sizeof(a));
    }
    cout << max(mx, len);
    return 0;
}