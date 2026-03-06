//
// Created by Psy.C on 2026/3/6.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6;

bool isp[N+5];
int pri[N+5], tot;
void get() {
    for (int i = 2; i <= N; ++i) {
        if (!isp[i]) pri[++tot] = i;
        for (int j = 1; j <= tot && i*1ll*pri[j] <= N; ++j) {
            isp[i*pri[j]] = true;
            if (i%pri[j] == 0) break;
        }
    }
}
namespace Miller_Rabin {
    const int P[] = {2, 3, 7, 97, 19260817};
    inline ll mul(ll a, ll b, const ll& mod) {
        ll tmp = a*b - 1ll*((long double)a*b/mod+.5)*mod;
        return tmp + (tmp>>63&mod);
    }
    inline ll ksm(ll a, ll b, const ll& mod) {
        ll ret = 1;
        for (; b; b>>=1, a=mul(a,a,mod))
            if (b&1) ret = mul(ret,a,mod);
        return ret;
    }
    bool ok(ll a, ll p) {
        ll x = p-1;
        int d = 0;
        while (!(x&1)) ++d, x>>=1;
        ll t = ksm(a, x, p);
        while (d--) {
            const ll lst = t;
            t = mul(t, t, p);
            if (t == 1 && lst != 1 && lst != p-1)
                return false;
        }
        return t == 1;
    }
    bool check(ll n) {
        if (n < 2) return false;
        if (n==2||n==3||n==7||n==97||n==P[4]) return true;
        for (const int i : P)
            if (n%i == 0) return false;
        return ranges::all_of(P, P+5, [&](const int p) {
            return ok(p%n, n);
        });
    }
}

ll n;
map<ll, int> pk, f[2];
vector<ll> v[(N<<1)+5];
set<int> s;
int main() {
    fast;
    get(); cin >> n;
    for (int i = 1; i <= tot; ++i) {
        ll p = 1;
        while (n/p >= pri[i]) pk[p*=pri[i]] = i;
    }
    for (int i = 1; 1ll*i*i <= n; ++i) if (n%i == 0) {
        if (pk.contains(i-1))
            v[pk[i-1]].push_back(i), s.insert(pk[i-1]);
        if (i*i != n) {
            const ll j = n/i;
            if (pk.contains(j-1))
                v[pk[j-1]].push_back(j), s.insert(pk[j-1]);
            else if (Miller_Rabin::check(j-1))
                v[++tot].push_back(j), s.insert(tot);
        }
    }
    f[0][1] = 1;
    int i = 1;
    for (const int x : s) {
        f[i&1] = f[i&1^1];
        for (auto [fst, snd] : f[i&1^1])
            for (const ll q : v[x])
                if (n/q >= fst && n%(fst*q) == 0)
                    f[i&1][fst*q] += snd;
        ++i;
    }
    cout << f[s.size()&1][n] << '\n';
    return 0;
}