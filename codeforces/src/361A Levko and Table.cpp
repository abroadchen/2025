//
// Created by Psy.C on 2026/1/19.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i, cout << '\n') {
        for (int j = 1; j <= n; ++j)
            cout << (i==j?k:0) << ' ';
    }
    return 0;
}