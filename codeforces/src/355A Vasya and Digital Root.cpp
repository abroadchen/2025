//
// Created by Psy.C on 2026/1/17.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int k, d; cin >> k >> d;
    if (k > 1 && d == 0) {
        cout << "No solution\n"; return 0;
    }
    for (int i = 0; i < k - 1; ++i) cout << '9';
    cout << d << '\n';
    return 0;
}