//
// Created by Psy.C on 2026/3/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int b, r;
int main() {
    fast;
    cin >> b >> r;
    if (b > r) {
        b -= r;
        cout << r << ' ' << b/2;
    } else if (r > b) {
        r -= b;
        cout << b << ' ' << r/2;
    } else cout << b << ' ' << 0;
    return 0;
}