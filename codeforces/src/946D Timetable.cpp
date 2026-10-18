//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 505;

int n, nn, m, c[N][N], a[N], s[N], f[N][N];
char ch;
int main() {
    fast;
    cin >> n >> nn >> m;
    memset(c, 0x3f, sizeof(c));
    rep(i,1,n) {
        rep(j,1,nn) {
            cin >> ch;
            if (ch == '1') a[++s[i]] = j;
        }
        c[i][s[i]] = 0;
        rep(len,1,s[i]) rep(l,1,s[i]-len+1) {
            int r = l + len - 1;
            c[i][s[i]-len] = min(c[i][s[i]-len], a[r]-a[l]+1);
        }
    }
    memset(f, 0x3f, sizeof(f));
    rep(j,0,m) f[0][j] = 0;
    rep(i,1,n) rep(j,0,m) rep(k,0,min(j,s[i]))
        f[i][j] = min(f[i][j], f[i-1][j-k]+c[i][k]);
    cout << f[n][m];
    return 0;
}