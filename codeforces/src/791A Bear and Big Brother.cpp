//
// Created by Psy.C on 2026/9/15.
//
/**
循环：只要熊还 不超过 哥哥（a <= b），就：
熊体重 ×3
哥哥体重 ×2
年数 ans++
循环退出时（a > b），输出年数 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    int ans = 0;
    while (a <= b) {
        a *= 3; b *= 2; ans++;
    }
    cout << ans << '\n';
    return 0;
}