//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
q 是询问次数；l, r 是区间左右端点；k 是目标数
x = r / k 得到区间右端点
r 里包含多少个完整的 k；
x++ 让 x 成为「比这一整段大 1」的倍数序数；
x * k 就是大于 r 的最小 k 的倍数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int q;
ll l, r, k;
int main() {
    fast;
    cin >> q;
    while (q--) {
        cin >> l >> r >> k;
        if (l > k) cout << k << '\n';
        else {
            ll x = r/k; x++;
            cout << x*k << '\n';
        }
    }
    return 0;
}