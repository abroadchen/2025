//
// Created by Psy.C on 2025/11/28.
//
/*
 *f[N]：用于存储计算结果的数组
 *
*初始条件：f(1) = 0
递推关系：f(n) = (3^(n-1) - f(n-1)) mod (10^9 + 7)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr ll N = 1e7+10, mod = 1e9+7;
int n;
ll f[N];

int main() {
    fast;
    cin >> n; f[1] = 0;
    ll x = 1;
    for (int i = 2; i <= n; ++i) {
        x = x * 3 % mod;
        f[i] = (x - f[i - 1]) % mod;
    }
    if (f[n] < 0) f[n] += mod;
    cout << f[n] << '\n';
    return 0;
}