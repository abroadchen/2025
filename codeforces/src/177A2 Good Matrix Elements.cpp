//
// Created by Psy.C on 2025/11/30.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 107
using namespace std;

int n, f[N][N], a[N][N], ans;

int main() {
    fast;
    cin >> n;
    rep(i,n) f[i][i] = f[i][n-i+1] =
        f[n/2+1][i] = f[i][n/2+1] = 1;
    rep(i,n) rep(j,n) { cin >> a[i][j];  ans += f[i][j] * a[i][j]; }
    cout << ans;
    return 0;
}