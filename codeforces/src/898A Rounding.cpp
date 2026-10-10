//
// Created by Psy.C on 2026/10/10.
//
/**
n%10 取 n 的个位数
若个位数 < 5：向下舍入到最近的 10 倍数，即 n - n%10（把个位抹掉）
若个位数 >= 5：向上进位，即 n - n%10 + 10（个位抹掉再 +10）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int n; cin >> n;
    if (n%10 < 5) cout << n-n%10 << '\n';
    else cout << n-n%10+10 << '\n';
    return 0;
}