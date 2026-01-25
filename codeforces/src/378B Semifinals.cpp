//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define rep(i,n) for (int i=0;i<n;++i)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int a[N], b[N];
    rep(i,n) cin >> a[i] >> b[i];
    int p = 0, q = 0;
    const int k = n / 2;
    rep(i, n) { if (a[p] < b[q]) p++; else q++; }
    rep(i,n) { if (i < p || i < k) cout << '1'; else cout << '0'; }
    cout << '\n';
    rep(i,n) { if (i < q || i < k) cout << '1'; else cout << '0'; }
    cout << '\n';
    return 0;
}