//
// Created by Psy.C on 2026/9/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int k, b, ans;
signed main() {
    fast;
    cin >> k >> b;
    for (int y = 0; y <= k*b; ++y) {
        int x = floor(b-y*1.0/k);
        ans = max(ans, (x+1)*(y+1)*(x+y)/2);
    }
    cout << ans << '\n';
    return 0;
}