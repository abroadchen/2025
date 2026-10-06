//
// Created by Psy.C on 2026/10/6.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, x; cin >> n >> k >> x;
    int s = 0, a;
    for (int i = 0; i < n; ++i) {
        if (i < n - k) { cin >> a;  s += a; }
        else s += x;
    }
    cout << s;
    return 0;
}