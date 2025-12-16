//
// Created by Psy.C on 2025/12/16.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, t, x, y, xa = 0, ya = 0, xb = 0, yb = 0; cin >> n;
    while (n--) {
        cin >> t >> x >> y;
        if (t == 1) { xa += x; ya += y; }
        else { xb += x; yb += y; }
    }
    cout << (xa >= ya ? "LIVE" : "DEAD") << '\n';
    cout << (xb >= yb ? "LIVE" : "DEAD") << '\n';
    return 0;
}