//
// Created by Psy.C on 2025/12/1.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int n, m, num[310];
double p[3010][310], f[310][3010], g[3010], gl[310], t[3010], ans;

void run(const int x) {
    num[x]++;
    if (num[x] >= n) { gl[x] = 0; return; }
    rep(i,n) t[i] = f[x][i];
    f[x][0] = 0.;
    rep(i,n) f[x][i] = f[x][i-1]*(1.-p[i][x]) + t[i-1]*p[i][x];
    gl[x] -= f[x][n];
}

void print() {
    rep(i,n) {
        double mx = 0; int id = 0;
        rep(j,m) if (mx < gl[j]) { mx = gl[j]; id = j; }
        ans += mx;
        if (!id) return;
        run(id);
    }
    cout << fixed << setprecision(8) << ans << '\n';
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) {
        cin >> p[i][j];
        p[i][j] = p[i][j] * 1. / 1000;
    }
    rep(i,m) f[i][0] = 1.;
    rep(i,m) {
        rep(j,n) f[i][j] = f[i][j-1]*(1-p[j][i]);
        gl[i] = 1. - f[i][n];
    }
    print();
    return 0;
}