//
// Created by Psy.C on 2026/1/3.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    if (k >= n * (n - 1) / 2) cout << "no solution\n";
    else {
        for (int i = 0; i < n; ++i) cout << "0 " << i << '\n';
    }
    return 0;
}