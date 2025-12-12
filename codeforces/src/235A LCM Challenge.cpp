//
// Created by Psy.C on 2025/12/12.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    if (n < 3) return cout << n, 0;
    if (n & 1) cout << n * (n - 1) * (n - 2);
    else {
        if (n % 3 != 0) cout << n * (n - 1) * (n - 3);
        else cout << (n - 1) * (n - 2) * (n - 3);
    }
    return 0;
}