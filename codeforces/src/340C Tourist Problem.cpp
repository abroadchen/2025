//
// Created by Psy.C on 2026/1/12.
//
/**
* 对于中间位置 i ≈ n/2：4*(n/2) - 2*n - 1 = -1
当 i < (2*n+1)/4 时，系数为负
当 i > (2*n+1)/4 时，系数为正
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 101000
using namespace std;


int main() {
    fast;
    ll n, a[N], ans = 0; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) ans += (4*i - 2*n - 1) * a[i];
    const ll g = __gcd(ans, n);
    cout << ans / g << ' ' << n / g << '\n';//使用最大公约数化简分数
    return 0;
}