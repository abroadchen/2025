//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
先读入位数 n。
循环里每次读入一个字符（char a），即数字的一位。
由于是 char 型，直接与字符 '0' 等比较
若该位是偶数数字，就把当前位置下标 i（从 1 开始）加到 ans。
i 是 1-based 位置号，注意它累加的不是数字本身，而是下标
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char a; cin >> a;
        if (a == '0' || a == '2' || a == '4' || a == '6' || a == '8')
            ans += i;
    }
    cout << ans;
    return 0;
}