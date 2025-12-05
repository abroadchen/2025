//
// Created by Psy.C on 2025/12/5.
//
/*
*提取x的最高位数字：
不断除以10，直到x变成个位数
循环结束后，x就是原数的最高位数字
 *
 *时间复杂度O(log x)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll conv(ll x) {
    ll res = 0;
    if (x < 10) return x;//是个位数
    const ll d = x % 10;//x的个位数字
    res = x / 10 + 9;//x/10：十位及以上数字的完整组数
    while (x >= 10) x /= 10;
    if (x > d) res--;//如果最高位数字 > 个位数字，则结果减1
    return res;
}

int main() {
    fast;
    ll a, b; cin>>a>>b;
    const ll s1 = conv(a - 1), s2 = conv(b);
    cout << s2 - s1;//[a, b]范围内满足条件的数字个数
    return 0;
}