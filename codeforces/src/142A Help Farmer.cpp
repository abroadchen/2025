//
// Created by Psy.C on 2025/11/20.
//
/*
*x = a
y = b
z = c = n/(x×y)
那么目标函数变为： f(x,y) = (x+1)(y+2)(n/(x×y)+2)
 *
*x的范围：1到∛n
y的范围：1到√(n/x)
z由n/(x×y)确定
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int main() {
    ll n; scanf("%lld", &n);
    ll mx = 3 * 3 * (n + 1) - n, mn = mx;
    for (ll x = 1; x * x * x <= n; ++x) {
        if (n % x != 0) continue;
        for (ll y = 1; x * y * y <= n; ++y) {
            if ((n / x) % y != 0) continue;
            ll z = (x + 1) * (y + 2) * (n / x / y + 2) - n;
            if (z < mn) mn = z;
        }
    }
    printf("%lld %lld\n", mn, mx);
    return 0;
}