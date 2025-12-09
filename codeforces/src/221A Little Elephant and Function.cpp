//
// Created by Psy.C on 2025/12/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n; cout << n;
    for (int i = 1; i < n; ++i) cout << ' ' << i;
    cout << '\n';
    return 0;
}