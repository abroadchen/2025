//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
对每一个 i（1 到 n）：

2*i / 3：整数除法（结果向下取整，即商）。
2*i % 3：取模（即余数，只能是 0、1、2 中的一种）。
因为 2*i 是被除数，3 是除数，所以输出的是 2*i 除以 3 的商和余数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cout << 2*i/3 << ' ' << 2*i%3 << '\n';
    return 0;
}