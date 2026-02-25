//
// Created by Psy.C on 2026/2/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c, d, v, m;
int main() {
    fast;
    cin >> a >> b >> c >> d;
    v = max(3*a/10, a-a/250*c);
    m = max(3*b/10, b-b/250*d);
    if (v > m) cout << "Misha";
    else if (m > v) cout << "Vasya";
    else cout << "Tie";
    return 0;
}