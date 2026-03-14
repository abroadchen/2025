//
// Created by Psy.C on 2026/3/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int t, s, q;
int main() {
    fast;
    cin >> t >> s >> q;
    int sum = 0;
    while (s < t) { s *= q; sum++; }
    cout << sum << '\n';
    return 0;
}