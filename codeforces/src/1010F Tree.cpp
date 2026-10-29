//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define vl vector<ll>
#define vi vector<int>
using namespace std;

constexpr int N = 2e5+10, mod = 998244353;

namespace Ju {
    ll fac[N<<2], ifac[N<<2], inv[N<<2];
    int lg[N<<2], rev[N<<2];
    ll C(int x, int y) {
        if (x < 0 || y < 0 || x < y) return 0ll;
        return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
    }
    ll ksm(ll x, ll y) {
        ll z = 1;
        while (y) {
            if (y&1) z=z*x%mod;
            x=x*x%mod;
            y>>=1;
        }
        return z;
    }
    void init(int nn) {
        int n = 1;
        while (n < nn<<1) n <<= 1;
        lg[1] = lg[0] = 1;
        for (int i = 2; i <= n; i++) lg[i] = lg[(i+1)>>1]<<1;
        inv[1] = 1;
        for (int i = 2; i <= n; i++) inv[i] = (mod-mod/i)*inv[mod%i]%mod;
        fac[0] = ifac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i-1]*i%mod, ifac[i] = ifac[i-1]*inv[i]%mod;
    }
    vl operator+(const vl &x, const vl &y) {
        vl z(y);
        int t = x.size();
        if (x.size() > y.size()) {
            t = y.size(); z.resize(x.size());
            for (int i = y.size(); i < x.size(); i++) z[i] = x[i];
        }
        for (int i = 0; i < t; i++) z[i] = (z[i] + x[i]) % mod;
        return z;
    }
    void ntt(vl &x, int flg) {
        int n = x.size();
        if (n < lg[n]) x.resize(lg[n], 0), n = lg[n];
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i>>1]>>1;
            if (i&1) rev[i] |= n>>1;
            if (i < rev[i]) swap(x[i], x[rev[i]]);
        }
        for (int i = 1; i < n; i <<= 1) {
            ll u = ksm(3, (mod-1)/i>>1);
            if (flg == -1) u = ksm(u, mod-2);
            for (int j = 0; j < n; j += i<<1) {
                ll v = 1;
                for (int k = 0; k < i; k++) {
                    ll y = x[j|k], z = x[j|i|k]*v%mod;
                    x[j|k] = y + z;
                    if (x[j|k] >= mod) x[j|k] -= mod;
                    x[j|i|k] = y - z;
                    if (x[j|i|k] < 0) x[j|i|k] += mod;
                    v = v*u%mod;
                }
            }
        }
        if (flg == -1) {
            ll t = ksm(n, mod-2);
            for (int i = 0; i < n; i++) x[i] = x[i]*t%mod;
        }
    }
    vl operator*(const vl &x, const vl &y) {
        static vl t1, t2; vl z; t1 = x, t2 = y;
        int n = x.size() + y.size() - 1, len = lg[n];
        t1.resize(len, 0), t2.resize(len, 0); z.resize(len);
        ntt(t1, 1); ntt(t2, 1);
        for (int i = 0; i < len; i++) z[i] = t1[i]*t2[i]%mod;
        ntt(z, -1); z.resize(n);
        return z;
    }
    ll BM(vl f, vl g, ll k) {
        static vl t;
        while (k) {
            t = g;
            for (int i = 1; i < g.size(); i += 2) t[i] = (mod-t[i])%mod;
            f = f*t; g = g*t;
            int i = k&1;
            for (; i < f.size(); i += 2) f[i>>1] = f[i];
            f.resize(i>>1);
            for (i = 0; i < g.size(); i += 2) g[i>>1] = g[i];
            g.resize(i>>1);
            k >>= 1;
        }
        if (f.empty()) return 0;
        return f[0]*ksm(g[0], mod-2)%mod;
    }
}
using namespace Ju;
vl get(int x) {
    vl ret; ret.resize(x+1);
    for (int i = 0; i <= x; i++) {
        ll t = C(x,i);
        ret[i] = (i&1) ? (mod-t)%mod : t;
    }
    return ret;
}

struct frac {
    vl f; int g;
    frac operator*(const frac &x) const { return {f*x.f, g+x.g}; }
    frac operator+(const frac &x) const {
        if (g >= x.g) return {f+x.f*get(g-x.g), g};
        return {x.f+f*get(x.g-g), x.g};
    }
} f[N];

int sz[N], son[N];
vector<int> g[N];
void dfs(int u, int fa) {
    sz[u] = 1; son[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}


pair<frac, frac> cdq(vi b) {
    if (b.size() == 1) return {f[b[0]], f[b[0]]};
    int sum = 0;
    for (int x : b) sum += f[x].g;
    int mid = 0, mn = sum, sm = 0;
    for (int i = 0; i < b.size()-1; i++) {
        sm += f[b[i]].g;
        if (max(sum-sm, sm) < mn) {
            mn = max(sum-sm, sm);
            mid = i;
        }
    }
    auto [fl, gl] = cdq(vi(b.begin(), b.begin()+mid+1));
    auto [fr, gr] = cdq(vi(b.begin()+mid+1, b.end()));
    return {fr*gl+fl, gl*gr};
}

void dfs2(int u, int fa, bool tp) {
    if (son[u]) dfs2(son[u], u, 0);
    f[u] = {{1}, 0};
    for (int v : g[u]) {
        if (v == son[u] || v == fa) continue;
        dfs2(v, u, 1);
        f[u] = f[v];
    }
    if (tp) {
        vi td;
        for (int x = u; x; x = son[x]) {
            td.push_back(x);
            f[x].g++;
        }
        f[u] = cdq(td).first;
        if (u != 1) f[u].f = f[u].f + get(f[u].g);
    }
}

ll X;
int n;
int main() {
    fast;
    cin >> n >> X; init((n+1)<<1);
    int sum = 0;
    for (int i = 1, x, y; i < n; i++)
        cin >> x >> y, g[x].push_back(y), g[y].push_back(x);
    dfs(1, 0); dfs2(1, 0, 1);
    cout << BM(f[1].f, get(f[1].g), X) << '\n';
    return 0;
}