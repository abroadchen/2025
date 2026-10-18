//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int d, p0, p1, lm, n, s, b, a[N];
ll dis;
bool check(int f) {
    dis = 1ll*d*f; p0 = 1; p1 = n;
    for (int i = f+1; i <= lm; ++i) {
        dis += d; s = b;
        while (a[p0] < s) s -= a[p0++];
        a[p0] -= s;
        if (p0 - i > dis) return 0;
        if (i == lm && (n&1)) break;
        s = b;
        while (a[p1] < s) s -= a[p1--];
        a[p1] -= s;
        if ((n-i+1) - p1 > dis) return 0;
    }
    return 1;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int c[N], l, r, ans;
int main() {
    fast;
    n = rd(), d = rd(), b = rd(); lm = (n+1) >> 1;
    for (int i = 1; i <= n; ++i) c[i] = a[i] = rd();
    l = 0, r = n + 1;
    while (l <= r) {
        int mid = (l+r)>>1;
        memcpy(a, c, sizeof(c));
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << '\n';
    return 0;
}