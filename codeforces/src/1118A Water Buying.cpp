//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
情况一：单买两瓶更便宜
如果a*2<b 说明套餐比两瓶单买还贵（套餐不划算），那就直接全部单买共 n瓶 a*n
情况二：套餐划算
尽量多买套餐：b × (n/2)（n 整除 2 个套餐）。
剩下 n%2（0 或 1）瓶单买：a × (n%2)。
两段相加即最少花费
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, a, b;
int main() {
    fast;
    int q; cin >> q;
    while(q--) {
        cin >> n >> a >> b;
        if (a*2 < b) cout << a*n << '\n';
        else cout << b*(n/2)+a*(n%2) << '\n';
    }
    return 0;
}