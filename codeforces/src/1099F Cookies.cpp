//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define ii pair<int, int>
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e6+5;

struct sgt {
    ll num[N<<2], sum[N<<2];
    void up(int u) {
        num[u] = num[u<<1]+num[u<<1|1];
        sum[u] = sum[u<<1]+sum[u<<1|1];
    }
    void build(int u, int l, int r) {
        sum[u] = num[u] = 0;
        if (l == r) return;
        build(u<<1,l,mid); build(u<<1|1,mid+1,r);
        return up(u);
    }
    ll qry(int u, int l, int r, ll s) {
        if (sum[u] == 0) return 0;
        if (l == r) return min(s/l, num[u]);
        if (sum[u<<1] >= s) return qry(u<<1,l,mid,s);
        return num[u<<1]+qry(u<<1|1,mid+1,r,s-sum[u<<1]);
    }
    void modify(int u, int l, int r, int pos, ll cnt) {
        if (l == r) { num[u] += cnt; sum[u] += cnt*pos; return; }
        if (pos <= mid) modify(u<<1,l,mid,pos,cnt);
        else modify(u<<1|1,mid+1,r,pos,cnt);
        return up(u);
    }
} tr;

int t[N], x[N];
vector<ii> to[N];
ll dfs(int u, ll rem) {
    tr.modify(1,1,N-5,t[u],x[u]);
    ll res = tr.qry(1,1,N-5, rem), m1 = 0, m2 = 0;
    for (auto [fst, snd] : to[u]) {
        if (rem - snd <= 0) continue;
        ll t = dfs(fst, rem-snd);
        if (t >= m1) m2 = m1, m1 = t;
        else if (t > m2) m2 = t;
    }
    tr.modify(1,1,N-5,t[u],-x[u]);
    if (u == 1) res = max(res, m1);
    return max(res, m2);
}

int n;
ll T;
int main() {
    fast;
    cin >> n >> T; tr.build(1,1,N-5);
    rep(i,n) cin >> x[i];
    rep(i,n) cin >> t[i];
    for (int i = 2, p, l; i <= n; ++i) {
        cin >> p >> l;
        to[p].emplace_back(i,l*2);
    }
    cout << dfs(1,T) << '\n';
    return 0;
}