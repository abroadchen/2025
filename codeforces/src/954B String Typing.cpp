//
// Created by Psy.C on 2026/10/19.
//
/**
从 i = n/2 递减到 1，检查长度为 i 的前缀 s[0..i-1] 是否等于位置 i 起的长 i 块 s[i..2i-1]。第一个满足的就是最大长度可合并对（因为从大到小），输出 n - i + 1；找不到则输出 n
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = n/2; i > 0; --i) {
        if (s.substr(0, i) == s.substr(i, i)) {
            cout << n-i+1 << '\n';
            return 0;
        }
    }
    cout << n << '\n';
    return 0;
}