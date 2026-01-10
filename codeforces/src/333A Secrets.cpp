//
// Created by Psy.C on 2026/1/10.
//
/**
* 找到最小的不能整除 n 的3的幂
返回 n / i + 1，其中 i 是最大的能整除 n 的3的幂
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin >> n;
    if (n <= 3) { cout << 1; return 0; }
    for (ll i = 3; true; i *= 3) if (n % i) {// n 除以 i 的余数是否不为0  n 不能被 i 整除
        cout << n / i + 1;
        break;
    }
    return 0;
}