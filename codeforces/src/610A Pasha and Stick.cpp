//
// Created by Psy.C on 2026/3/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, ans;
int main() {
    fast;
    cin >> n;
    if (n&1) { cout << "0\n"; return 0; }
    n >>= 1;
    ans = n>>1;
    if (n&1) cout << ans << "\n";
    else cout << ans-1 << "\n";
    return 0;
}