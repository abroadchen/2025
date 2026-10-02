//
// Created by Psy.C on 2026/10/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[30], mx;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; mx = max(mx, a[i]);
    }
    if (mx <= 25) putchar('0'); else cout << mx-25;
    return 0;
}