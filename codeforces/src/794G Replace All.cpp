//
// Created by Psy.C on 2026/9/16.
//

#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 4e6+10, mod = 1e9+7;

int mu[N], vis[N], p[N], tp;
void sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) p[++tp] = i, mu[i] = mod-1;
        for (int j = 1, t; j <= tp && p[j]*i <= n; ++j) {
            t = i*p[j];
            vis[t] = 1;
            if (i%p[j] == 0) { mu[t] = 0; break; }
            mu[t] = mod - mu[i];
        }
    }
}
inline void mo(int& x) { x >= mod ? x -= mod : x; }
inline int ksm(int a, int b) {
    int ret = 1;
    while (b) {
        if (b&1) ret = 1ll*ret*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return ret;
}

int fac[N], ifac[N];
inline int C(int n, int m) {
    if (n < m || m < 0) return 0;
    return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int calc(int a, int b, int cnta, int cntb, int d) {
    if (a < 0 || b < 0) return 0;
    return C(a+b-cnta-cntb, a+d-cntb);
}

int pw[N], cnts[2], cntt[2], sum[N];
char s[N], t[N];
int main() {
    pw[0] = fac[0] = ifac[0] = 1; sieve(N-1);
    for (int i = 1; i < N; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    ifac[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; i; --i) ifac[i] = 1ll*ifac[i+1]*(i+1)%mod;
    for (int i = 1; i < N; ++i) pw[i] = 2ll*pw[i-1]%mod;
    int a, b, n, ans = 0;
    scanf("%s%s%d", s+1, t+1, &n); a = strlen(s+1), b = strlen(t+1);
    for (int i = 1; i <= a; ++i)
        if (s[i] != '?') ++cnts[s[i]=='A'];
    for (int i = 1; i <= b; ++i)
        if (t[i] != '?') ++cntt[t[i]=='A'];
    if (a == b) {
        int flg = 1, cnt = 0;
        for (int i = 1; i <= a && flg; ++i) {
            if (s[i] != '?' && t[i] != '?' && s[i] != t[i]) flg = 0;
            else if (s[i] == '?' && t[i] == '?') ++cnt;
        }
        if (flg) ans = 1ll*(pw[n+1]-2)*(pw[n+1]-2)%mod*pw[cnt]%mod;
        int tot = (calc(a-cnts[0], b-cntt[0], cnts[1], cntt[1], 0)+mod-
            (flg?pw[cnt]:0))%mod;
        for (int p = 1; p <= n; ++p)
            for (int t = p; t <= n; t += p)
                mo(sum[t] += 1ll*mu[p]*pw[t/p]%mod);
        for (int i = 1; i <= n; ++i)
            mo(ans += 1ll*(n/i)*(n/i)%mod*sum[i]%mod*tot%mod);
    }
    for (int i = -a; i <= b; ++i) {
        if (!i) continue;
        int tot = calc(a-cnts[0], b-cntt[0], cnts[1], cntt[1], i), d = i+a-b;
        if (!tot) continue;
        if (1ll*i*d <= 0) continue;
        int x = abs(i), y = abs(d), p = __gcd(x, y); x = x/p; y = y/p;
        int up = min(n/x, n/y);
        mo(ans += 1ll*tot*(pw[up+1]-2)%mod);
    }
    printf("%d\n", ans);
    return 0;
}