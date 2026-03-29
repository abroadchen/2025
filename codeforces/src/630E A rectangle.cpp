//
// Created by Psy.C on 2026/3/29.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int main() {
    fast;
    ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    ll nx = (x2 - x1 + 1)/2, ny = (y2 - y1 + 2)/2;
    cout << ny*(x2 - x1 + 1) - nx << '\n';
    return 0;
}