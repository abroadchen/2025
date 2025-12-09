//
// Created by Psy.C on 2025/12/9.
//
/*
 *2^p-1为素数的指数p
 *
*ret初始化为1（结果）
当指数x不为0时循环：
如果x的最低位为1（x是奇数），则ret *= num并取模
num自乘并取模（相当于num^2）
x右移一位（相当于x除以2）
返回最终结果
 *
*n-1 来获取正确的数组元素
然后对数组元素再减1作为指数
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;

int a[45] = {
    2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,4423,
    9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,216091,
    756839,859433,1257787,1398269,2976221,3021377,6972593,13466917,20996011
};

ll f(ll num, ll x) {
    ll ret = 1;
    while (x) {
        if (x & 1) { ret *= num; ret %= mod; }
        num *= num; num %= mod;
        x >>= 1;
    }
    return ret;
}

int main() {
    fast;
    int n; cin>>n;
    cout << f(2, a[n-1]-1) - 1 << '\n';
    return 0;
}