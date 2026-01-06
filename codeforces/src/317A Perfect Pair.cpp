//
// Created by Psy.C on 2026/1/6.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll x, y, m; cin >> x >> y >> m;
    if (x >= m || y >= m) cout << 0 << '\n'; else {
        if (x <= 0 && y <= 0) cout << -1 << '\n'; else {
            if (x < y) swap(x, y);//确保x是较大的值
            ll res = 0;//操作次数
            if (y < 0) {
                const ll n = (-y) / x + 1;//多少次操作使y变为非负
                res += n;
                y += x * n;//更新y
            }
            while (x < m) {//不断将较小数替换为两数之和，直到某个数达到m
                y += x;
                swap(x, y);
                res++;
            }
            cout << res << '\n';
        }
    }
    return 0;
}