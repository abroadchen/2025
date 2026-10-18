//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 110, mod = 1e9+7;

ll ksm(ll x, ll p) {
    ll ret = 1;
    for (; p; p>>=1, x=x*x%mod)
        if (p&1) ret=ret*x%mod;
    return ret;
}

int n, m;
char s[N];
ll fib[N], pw[N], f[N][N][N];
int main() {
    scanf("%d%d", &n, &m); scanf("%s", s+1);
    fib[0] = fib[1] = 1; pw[0] = pw[1] = 2;
    rep(i,2,m) fib[i] = (fib[i-1]+fib[i-2])%(mod-1), pw[i] = ksm(2, fib[i]);
    rep(i,1,n) f[0][i][i] = s[i]=='0', f[1][i][i] = s[i]=='1';
    rep(i,2,m) rep(j,1,n) rep(k,j,n) {
        f[i][j][k] = (f[i][j][k]+f[i-1][j][k]*(k==n?pw[i-2]:1)%mod)%mod;
        f[i][j][k] = (f[i][j][k]+f[i-2][j][k]*(j==1?pw[i-1]:1)%mod)%mod;
        rep(l,j,k-1) f[i][j][k] = (f[i][j][k]+f[i-1][j][l]*f[i-2][l+1][k]%mod)%mod;
    }
    printf("%lld\n", f[m][1][n]);
    return 0;
}