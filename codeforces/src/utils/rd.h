//
// Created by Psy.C on 2026/2/9.
//

#ifndef CODEFORCES_RD_H
#define CODEFORCES_RD_H
#include "../bits/stdc++.h"
// inline char gc() {
//     static char now[1<<16], *s, *t;
//     if (t == s) {
//         t = (s = now) + fread(now, 1, 1<<16, stdin);
//         if (t == s) return EOF;
//     }
//     return *s++;
// }

constexpr int SIZE = 1<<22;
char buf[SIZE], *S = buf, *T = buf;
#define gc \
(S == T ? T = ((S = buf) + fread(buf, 1, SIZE, stdin)), \
(S == T ? EOF : *S++) : *S++)

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

inline void readd(int& x) {
    char c = getchar();
    for (; !isdigit(c); c = getchar()) {}
    x = c^48;
}





constexpr int N = 1e5+1, mod = 1e9+7;

inline int ksm(int x, int p) {
    int res = 1;
    for (; p; p>>=1, x = 1ll*x*x%mod)
        if (p&1) res = 1ll*res*x%mod;
    return res;
}

ll dfs(ll a, ll n) {
    return n ? dfs(a*a%mod, n>>1)*(n&1 ? a : 1)%mod : 1;
}


int fac[N], inv[N];
inline void init() {
    fac[0] = 1;
    for (int i = 1; i <= N-1; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; ~i; --i) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
}

inline int c(const int n, const int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

#endif //CODEFORCES_RD_H