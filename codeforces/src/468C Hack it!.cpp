//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, inf = 1e18;

int main() {
    fast;
    cin >> n;
    const ll l = n - inf%n*9%n*9%n, r = inf + l - 1;
    cout << l << ' ' << r << '\n';
    return 0;
}