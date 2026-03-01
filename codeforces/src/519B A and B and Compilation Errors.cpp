//
// Created by Psy.C on 2026/3/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, b, c, sa, sb, sc;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) { cin >> a; sa += a; }
    for (int i = 0; i < n-1; ++i) { cin >> b; sb += b; }
    for (int i = 0; i < n-2; ++i) { cin >> c; sc += c; }
    cout << sa - sb << '\n';
    cout << sb - sc << '\n';
    return 0;
}