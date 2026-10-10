//
// Created by Psy.C on 2026/10/10.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a1, a2;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x == 1) a1++; else a2++;
    }
    cout << min(a2, a1) + max(a1-a2, 0)/3 << '\n';
    return 0;
}