//
// Created by Psy.C on 2026/10/10.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, x, y, l, r;
int main() {
    fast;
    cin >> n;
    while (n--) {
        cin >> x >> y;
        if (x > 0) r++;
        else if (x < 0) l++;
    }
    if (r > 1 && l > 1) cout << "No\n";
    else cout << "Yes\n";
    return 0;
}