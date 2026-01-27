//
// Created by Psy.C on 2026/1/26.
//
/*
* 有初始资源a和额外资源b
每轮操作消耗x单位资源，但能获得w单位产出
需要达到目标c
计算需要多少轮操作才能达到目标
当(w > x)时，每轮净收益为(w-x)，所以需要计算达到目标所需的操作轮数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll a, b, w, x, c; cin >> a >> b >> w >> x >> c;
    if (c <= a) cout << "0\n"; else {
        ll p;
        if (ll p1 = (c - a - b/x) * x - b % x, p2 = w - x; p1 % p2 == 0) p = p1 / p2;
        else p = p1 / p2 + 1;
        cout << p + c - a << '\n';
    }
    return 0;
}