//
// Created by Psy.C on 2025/11/22.
//

#include <cstdio>
using namespace std;

typedef long long ll;
constexpr ll mod = 1e9+7;

int main() {
    ll n, m, k; scanf("%lld %lld %lld", &n, &m, &k);
    ll ans = 1;
    if (k == 1 || k > n) {
        for (ll i = 0; i < n; ++i) ans = (ans * m) % mod;//m的n次方并对mod取模
    } else if (k == n) {
        for (ll i = 0; i < (n + 1) / 2; ++i) ans = (ans * m) % mod;//m^(⌈n/2⌉)
    } else if (k % 2 == 1) ans = (m * m) % mod;
    else if (k % 2 == 0) ans = m;
    printf("%lld\n", ans);
    return 0;
}