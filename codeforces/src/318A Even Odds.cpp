//
// Created by Psy.C on 2026/1/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, k, ans; cin >> n >> k;
    if (const ll div = (n + 1) >> 1; k <= div) ans = (k<<1)-1;//如果k在前半部分
    else ans = (k - div)<<1;//如果k在后半部分
    cout << ans << '\n';
    return 0;
}