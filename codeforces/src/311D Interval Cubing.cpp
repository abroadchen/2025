//
// Created by Psy.C on 2026/1/3.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100007
#define M 48
#define mod 95542721
using namespace std;

ll pw(ll b, ll e, ll p) {
    ll res = 1;
    b %= mod;
    while (e > 0) {
        if (e & 1) res = res * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return res;
}


int a[N<<2][M];
void push_up(const int rt) {
    for (int i = 0; i < M; ++i) {
        a[rt][i] = a[rt<<1][i] + a[rt<<1|1][i];
        if (a[rt][i] >= mod) a[rt][i] -= mod;
    }
}

void build(const int l, const int r, const int rt) {
    if (l == r) {
        cin >> a[rt][0]; a[rt][0] %= mod;
        ll cur = a[rt][0];
        for (int i = 1; i < M; ++i) {
            a[rt][i] = static_cast<int>(cur);
            cur = pw(cur, 3, mod);
        }
        return;
    }
    const int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
    push_up(rt);
}

int laz[N<<2];
void pushdown(const int rt) {
    laz[rt] %= M;
    if (laz[rt]) {
        laz[rt<<1] += laz[rt];
        laz[rt<<1|1] += laz[rt];
        rotate(a[rt<<1], a[rt<<1]+laz[rt], a[rt<<1]+M);
        rotate(a[rt<<1|1], a[rt<<1|1]+laz[rt], a[rt<<1|1]+M);
        laz[rt] = 0;
    }
}


int query(const int L, const int R, const int l, const int r, const int rt) {
    if (l >= L && r <= R) { return a[rt][0]; }
    pushdown(rt);
    const int mid = (l + r) >> 1;
    if (R <= mid) return query(L, R, l, mid, rt<<1);
    if (L > mid) return query(L, R, mid+1, r, rt<<1|1);
    return query(L, R, l, mid, rt<<1) + query(L, R, mid+1, r, rt<<1|1);
}

void modify(const int L, const int R, const int l, const int r, const int rt) {
    if (l >= L && r <= R) {
        laz[rt]++;
        rotate(a[rt], a[rt] + 1, a[rt] + M);
        return;
    }
    pushdown(rt);
    const int mid = (l + r) >> 1;
    if (L <= mid) modify(L, R, l, mid, rt<<1);
    if (R > mid) modify(L, R, mid+1, r, rt<<1|1);
    push_up(rt);
}


int main() {
    fast;
    int n, q; cin >> n; build(1, n, 1);
    cin >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) cout << query(l, r, 1, n, 1) << '\n'; else {
            modify(l, r, 1, n, 1);
        }
    }
    return 0;
}