//
// Created by Psy.C on 2026/1/30.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

bool get(const ll n) {//判断 n 是否为素数
    for (ll i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}

ll gcd(const ll a, const ll b) { return b == 0 ? a : gcd(b, a % b); }

struct node {
    ll p, q;//p：分子，q：分母
    explicit node(const ll _p=1, const ll _q=1) : p(_p), q(_q) {}
    friend node operator-(const node a, const node b) {
        node c;
        ll t = gcd(a.q, b.q);
        c.p = b.q / t * a.p - a.q / t * b.p;//计算分子
        c.q = a.q / t * b.q;//计算分母
        t = gcd(c.p, c.q);//约分：用分子分母的最大公约数化简
        c.p /= t; c.q /= t;
        return c;
    }
} a, b;

int main() {
    fast;
    ll q; cin >> q;
    while (q--) {
        ll n; cin >> n;
        ll v = n, u = n + 1;//v：小于等于 n 的最大素数  u：大于 n 的最小素数
        while (!get(v)) v--;
        while (!get(u)) u++;
        //a = (u-2)/(2*u) b = (u-1-n)/(v*u)
        a = node{u-2, 2*u}; b = node{u-1-n, v*u};
        a = a - b;
        cout << a.p << '/' << a.q << '\n';
    }
    return 0;
}