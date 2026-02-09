//
// Created by Psy.C on 2026/2/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 330000
#define mod 1000000009
using namespace std;

inline char gc() {
    static char now[1<<16], *s, *t;
    if (t == s) {
        t = (s = now) + fread(now, 1, 1<<16, stdin);
        if (t == s) return EOF;
    }
    return *s++;
}

inline int read() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = gc();
    }
    while (ch <= '9' && ch >= '0') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x * f;
}


struct node { int sum, fa, fb, l, r; } tr[N<<1];

int f[N];
inline int get(const int a, const int b, const int k) {
    if (k == 1) return a;
    if (k == 2) return b;
    return static_cast<int>((1ll*a*f[k-2]+1ll*b*f[k-1])%mod);
}

inline int get_sum(const int a, const int b, const int k) {
    if (k == 1) return a;
    if (k == 2) return (a + b)%mod;
    return (get(a, b, k+2) - b + mod) % mod;
}

inline void change(const int x, const int len, const int a, const int b) {
    (tr[x].fa += a) %= mod;
    (tr[x].fb += b) %= mod;
    (tr[x].sum += get_sum(a, b, len)) %= mod;
}

inline void pushdown(const int x, const int l, const int r) {
    if (!tr[x].fa) return;
    const int mid = (l + r) >> 1, lc = tr[x].l, rc = tr[x].r;
    (tr[lc].fa += tr[x].fa) %= mod;
    (tr[lc].fb += tr[x].fb) %= mod;
    (tr[lc].sum += get_sum(tr[x].fa, tr[x].fb, mid - l + 1)) %= mod;
    const int a = get(tr[x].fa, tr[x].fb, mid - l + 2),
    b = get(tr[x].fa, tr[x].fb, mid - l + 3);
    (tr[rc].fa += a) %= mod;
    (tr[rc].fb += b) %= mod;
    (tr[rc].sum += get_sum(a, b, r - mid)) %= mod;
    tr[x].fa = tr[x].fb = 0;
}


inline void push_up(const int x) {
    const int l = tr[x].l, r = tr[x].r;
    tr[x].sum = (tr[l].sum + tr[r].sum) % mod;
}

int num, a[N];
inline void build(int &x, const int l, const int r) {
    x = ++num;
    const int mid = (l + r) >> 1;
    if (l == r) { tr[x].sum = a[l]; return; }
    build(tr[x].l, l, mid);
    build(tr[x].r, mid + 1, r);
    push_up(x);
}

inline void insert(const int x, const int l, const int r, const int L, const int R) {
    if (L <= l && R >= r) {
        change(x, r-l+1, f[l-L+1], f[l-L+2]);
        return;
    }
    const int mid = (l + r) >> 1;
    pushdown(x, l, r);
    if (L <= mid) insert(tr[x].l, l, mid, L, R);
    if (R > mid) insert(tr[x].r, mid+1, r, L, R);
    push_up(x);
}

inline ll query(const int x, const int l, const int r, const int L, const int R) {
    if (L <= l && R >= r) return tr[x].sum;
    const int mid = (l + r) >> 1;
    ll t = 0;
    pushdown(x, l, r);
    if (L <= mid) t += query(tr[x].l, l, mid, L, R);
    if (R > mid) t += query(tr[x].r, mid + 1, r, L, R);
    return t % mod;
}

int n, m, rt;

int main() {
    fast;
    n = read(); m = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    f[1] = f[2] = 1;
    for (int i = 3; i <= n + 2; ++i) f[i] = (f[i-1] + f[i-2]) % mod;
    build(rt, 1, n);
    while (m--) {
        const int op = read(), l = read(), r = read();
        if (op == 1) insert(rt, 1, n, l, r);
        if (op == 2) printf("%lld\n", query(rt, 1, n, l, r));
    }
    return 0;
}