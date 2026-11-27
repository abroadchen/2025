//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
从字符串开头开始。
只要当前字符是 <，就 a1++ 并前进；遇到第一个非 < 或到达末尾则停止。
得到前缀连续 < 的个数 a1
从末尾开始。
只要末尾字符是 >，就 a2++ 并向左移；遇到第一个非 > 或只剩一个字符则停止。
得到后缀连续 > 的个数 a2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int t, n;
string s;
int main() {
    fast;
    cin >> t;
    for (int g = 1; g <= t; g++) {
        cin >> n >> s; s = ' ' + s;
        int i = 1, a1 = 0, a2 = 0;
        while (s[i] == '<') {
            if (i == n) break;
            a1++; i++;
        }
        while (s[n] == '>') {
            if (n == 1) break;
            a2++; n--;
        }
        cout << min(a1,a2) << '\n';
    }
    return 0;
}