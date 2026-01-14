//
// Created by Psy.C on 2026/1/14.
//

#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) cin >> a[i];
    ranges::sort(a);
    swap(a[0], a[n-1]);
    for (ll i = 0; i < n; ++i) cout << a[i] << ' ';
    return 0;
}