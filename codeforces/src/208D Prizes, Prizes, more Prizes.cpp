//
// Created by Psy.C on 2025/12/6.
//
/*
*n：商品数量
p(n)：存储每个商品的价格
a1, b1, c1, d1, e1：五种硬币的面值（从小到大）
t：累计的找零金额，初始化为0
读取所有商品价格和硬币面值
 *
*累计当前商品价格到总金额t
对累计的金额进行找零计算（贪心算法）
从最大面值开始，尽可能多地使用大面值硬币
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, a1, b1, c1, d1, e1, t = 0; cin >> n;
    vector<ll> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    cin >> a1 >> b1 >> c1 >> d1 >> e1;
    ll a = 0, b = 0, c = 0, d = 0, e = 0;//五种硬币的使用数量
    for (int i = 0; i < n; ++i) {
        t += p[i];
        if (t >= e1) { e += t / e1; t %= e1; }
        if (t >= d1) { d += t / d1; t %= d1; }
        if (t >= c1) { c += t / c1; t %= c1; }
        if (t >= b1) { b += t / b1; t %= b1; }
        if (t >= a1) { a += t / a1; t %= a1; }
    }
    cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<'\n'<<t;
    return 0;
}