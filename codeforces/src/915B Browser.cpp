//
// Created by Psy.C on 2026/10/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
int n, p, l, r;
int main() {
    fast;
    cin >> n >> p >> l >> r;
    if (l == 1 && r == n) cout << "0";
    else if (l == 1) cout << abs(p-r)+1;
    else if (r == n) cout << abs(p-l)+1;
    else cout << r-l+2+min(abs(p-r), abs(p-l));
    return 0;
}