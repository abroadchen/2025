//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); i++)
using namespace std;

constexpr int N = 1e4+5;

int n, k, i, a[N], v[N], ans[N], cnt;
int main() {
    fast;
    cin>>n>>k;
    rep(i,n) {
        cin>>a[i];
        if (!v[a[i]]) { cnt++; ans[cnt] = i; }
        v[a[i]] = 1;
    }
    if (cnt < k) cout << "NO\n";
    else {
        cout << "YES\n";
        rep(i,k) cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}