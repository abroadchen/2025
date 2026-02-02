//
// Created by Psy.C on 2026/2/2.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    db tot = 0;
    for (int k = 0; k < n; ++k) {
        db x, y; cin >> x >> y;
        tot += y;
    }
    cout << fixed << setprecision(3) << 5. + tot / n << '\n';
    return 0;
}