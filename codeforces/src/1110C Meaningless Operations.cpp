//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
y 从 1 开始不断翻倍，找到第一个大于 x 的 2 的幂；
循环结束后 y 是"第一个大于 x 的 2 的整数次幂"，y-- 使其变为 (2^k)-1，这个值满足 ≤ x
如果 y != x：说明最大那个 2^k-1 严格小于 x（即 x 不是 2^k-1 形式的数），此时直接输出 y。
如果 y == x：说明 x 本身就是某个 2^k - 1（梅森数形），比如 x = 1、3、7、15、31、63… 这时走下面"分支 A"。
分支 A：处理 y==x（梅森数）的情况
z = ceil(sqrt(x))：x 的平方根上取整，作为试除的上界。
f 标记"是否找到了 x 的最小真因子"。
从 i=2 到 z 循环试除：
当找到第一个能整除 x 的 i 时，x 是合数，输出 x/i（最大的那个真因子），并设 f=0、break 跳出。
若循环结束仍没找到因子（f 仍为 1），说明 x 是质数（或 x=1），输出 "1"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll q;
int main() {
    fast;
    cin >> q;
    while (q--) {
        ll x; cin >> x;
        ll y = 1;
        while (y <= x) y *= 2;
        y--;
        if (y == x) {
            ll z = ceil(sqrt(x));
            bool f = 1;
            for (ll i = 2; i <= z; i++) if (x%i == 0) {
                cout << x/i << '\n'; f = 0;
                break;
            }
            if (f) cout << "1\n";
        } else cout << y << '\n';
    }
    return 0;
}