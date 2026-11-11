//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
外层 i 从 2 到 n；
内层 j 取 i 的倍数（从 2i 开始），每次累加 4*(j/i)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, ans;
int main() {
    fast;
    cin >> n;
    for (int i = 2; i <= n; i++)
        for (int j = 2*i; j <= n; j += i)
            ans += 4*(j/i);
    cout << ans;
    return 0;
}