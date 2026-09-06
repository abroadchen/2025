//
// Created by Psy.C on 2026/9/6.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int k, a, b; cin >> k >> a >> b;
    if (a < k && b < k) { cout << "-1"; return 0; }
    if (a%k != 0 && b < k) { cout << "-1"; return 0; }
    if (b%k != 0 && a < k) { cout << "-1"; return 0; }
    cout << a/k+b/k;
    return 0;
}