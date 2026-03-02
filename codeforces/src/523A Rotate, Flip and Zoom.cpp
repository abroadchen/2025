//
// Created by Psy.C on 2026/3/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;
constexpr int N = 101;
int n, m;
char a[N][N];
int main() {
    fast;
    cin >> m >> n;
    rep(i,n) rep(j,m) cin >> a[i][j];
    rep(i,m) rep(j,2) {
        rep(k,n) cout << a[k][i] << a[k][i];
        cout << '\n';
    }
    return 0;
}