//
// Created by Psy.C on 2026/2/1.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int c[100];
    for (int i = 0; i < n; ++i) cin >> c[i];
    sort(c, c+n);
    for (int i = 0; i < n; ++i) cout << c[i] << ' ';
    cout << '\n';
    return 0;
}