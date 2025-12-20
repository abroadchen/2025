//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 105
using namespace std;


int main() {
    fast;
    ll n, t, f[N] = {}, cnt = 0; cin >> n >> t; ++n;
    if (t & (t - 1)) return cout << '0', 0;//如果t是2的幂次方，结果为0；否则非零
    for (int j = 60; ~j; --j) {//~j等价于j != -1
        for (int i = 60; i; --i) f[i] += f[i - 1];//相当于对多项式系数进行更新
        if (n>>j&1) ++f[cnt++];//n的第j位为1时，增加f[cnt]的值 然后cnt自增
    }
    ++f[cnt]; cnt = 0;//循环结束后剩余的计数需求
    while (t) t >>= 1, ++cnt;//t是2的多少次幂，结果存储在cnt中
    cout << f[cnt] - (cnt == 1);
    return 0;
}