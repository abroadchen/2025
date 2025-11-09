//
// Created by Psy.C on 2025/11/8.
//
/*
*将m个资源平均分配给⌈n/2⌉个有效位置
每个位置得到 m / ⌈n/2⌉ 个资源
乘以系数k得到基础价值 k * (m / ⌈n/2⌉)
 *
*只考虑索引为偶数（位置为奇数）的元素
在这些元素和初始值中选择最小值
 *
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    ll n, m, k; scanf("%lld %lld %lld", &n, &m, &k);
    if (n % 2 == 0) puts("0");
    else {
        ll mn(k * (m / ((n + 1) / 2)));
        for (ll i = 0; i < n; ++i) {
            ll x; scanf("%lld", &x);
            if (i % 2 == 0) mn = mn < x ? mn : x;
        }
        printf("%lld\n", mn);
    }
    return 0;
}