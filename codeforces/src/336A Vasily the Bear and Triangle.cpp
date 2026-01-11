//
// Created by Psy.C on 2026/1/11.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x, y; cin >> x >> y;
    if (x > 0) {
        if (y > 0) cout << 0 << ' ' << x + y << ' ' << x + y << ' ' << 0 << '\n';
        else cout << 0 << ' ' << y - x << ' ' << x - y << ' ' << 0 << '\n';
    } else {
        if (y > 0) cout << x - y << ' ' << 0 << ' ' << 0 << ' ' << y - x << '\n';
        else cout << x + y << ' ' << 0 << ' ' << 0 << ' ' << x + y << '\n';
    }
    return 0;
}