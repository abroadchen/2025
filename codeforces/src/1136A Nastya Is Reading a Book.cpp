//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 1e6;
int n, a[N], b[N], k, sum;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i] >> b[i];
    cin >> k;
    rep(i,n) {
        if (k >= a[i] && k <= b[i]) break;
        sum++;
    }
    cout << n - sum << '\n';
    return 0;
}