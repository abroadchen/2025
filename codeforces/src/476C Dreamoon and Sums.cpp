//
// Created by Psy.C on 2026/2/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;

ll a, b;

int main() {
    fast;
    cin >> a >> b;
    const ll t = b * (b-1)/2 %mod, t1 = (1+a)*a/2%mod, t2 = (t1*b+a)%mod;
    cout << t2%mod*t%mod << '\n';
    return 0;
}