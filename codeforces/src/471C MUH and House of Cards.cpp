//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;

int main() {
    fast;
    cin >> n;
    ll num = 0;
    for (ll i = 0, y; ; ++i) {
        if (const ll x = (2*(i+1)*(i+2))/2+(i*(i+1))/2; n >= x) y = n - x;
        else break;
        if (y%3 == 0) num++;
    }
    cout << num << '\n';
    return 0;
}