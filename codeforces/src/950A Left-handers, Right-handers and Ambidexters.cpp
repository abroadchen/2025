//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b, c, k;
int main() {
    fast;
    cin >> a >> b >> c; k = c;
    if (a < b) {
        k -= b - a;
        if (k >= 0) cout << 2*(b+k/2);
        else cout << 2*(a+c);
    }
    if (b < a) {
        k -= a - b;
        if (k >= 0) cout << 2*(a+k/2);
        else cout << 2*(b+c);
    }
    if (a == b) cout << 2*(a+c/2);
    return 0;
}