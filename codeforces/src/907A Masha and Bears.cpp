//
// Created by Psy.C on 2026/10/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

int v1, v2, v3, v;
int main() {
    fast;
    cin >> v1 >> v2 >> v3 >> v;
    if (v > 2*v3 || v3 > 2*v || v2 <= v) cout << -1 << '\n';
    else cout << 2*v1 << '\n' << 2*v2 << '\n' << max(v3, v) << '\n';
    return 0;
}