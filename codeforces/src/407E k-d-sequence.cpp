//
// Created by Psy.C on 2026/2/1.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
#define mid ((l+r)>>1)
using namespace std;



int mn[N], tg[N];
void build(const int i, const int l, const int r) {
    mn[i] = tg[i] = 0;
    if (l == r) return;
    build(i<<1, l, mid); build(i<<1|1, mid+1, r);
}


inline void P(const int i, const int x) { mn[i] += x, tg[i] += x; }
inline void pd(const int i) { if (tg[i]) P(i<<1, tg[i]), P(i<<1|1, tg[i]), tg[i] = 0; }
void modify(const int i, const int l, const int r, const int a, const int b, const int x) {
    if (r < a || b < l) return;
    if (a <= l && r <= b) return P(i, x);
    pd(i), modify(i<<1, l, mid, a, b, x), modify(i<<1|1, mid+1, r, a, b, x);
    mn[i] = min(mn[i<<1], mn[i<<1|1]);
}

int mxl;
inline void solve(int *a, int n, int k, int offset) {
    if (n <= mxl) return;
    static int b[N], c[N], lst[N], s1[N], s2[N];
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + n + 1);
    const int m = static_cast<int>(unique(b + 1, b + n + 1) - b - 1);
    for (int i = 1; i <= n; ++i) c[i] = static_cast<int>(lower_bound(b + 1, b + m + 1, a[i]) - b);
    for (int i = 1; i <= m; ++i) lst[i] = 0;
    int ml = 1, t1 = 0, t2 = 0; build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        ml = max(ml, lst[c[i]] + 1); lst[c[i]] = i;
        for (; t1 && a[s1[t1]] <= a[i]; --t1)
    }
}





int main() {
    fast;
    int n, k, d; cin >> n >> k >> d;
    int a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (d == 0) {
        int mx = 1, lst = a[1], len = 1, ans = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i] == lst) ++len;
            else len = 1, lst = a[i];
            if (len > mx) mx = len, ans = i - mx + 1;
        }
        cout << ans << ' ' << ans + mx - 1;
        return 0;
    }
    int r[N], b[N], t = 0;
    for (int i = 1; i <= n; ++i) r[i] = (a[i] % d + d) % d;
    for (int i = 1; i <= n; ++i) {
        b[++t] = (a[i] - r[i]) / d;
        if (i == n || r[i] != r[i+1])
    }
    return 0;
}