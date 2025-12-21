//
// Created by Psy.C on 2025/12/21.
//
/*
 * C(n+1, 3) = (n+1)!/(3!×(n-2)!) = (n-1)×n×(n+1)/6
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    cout << (n - 1) * n * (n + 1) / 6 + n << '\n';
    return 0;
}