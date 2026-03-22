//
// Created by Psy.C on 2026/3/22.
//
/**
v1: 根节点初始值
v[N]: 节点权值数组
sum[]: 区间和
mul[]: 懒惰标记（乘法标记）
k[]: 额外标记
in[u], ot[u]: 节点u的进入和离开时间戳
用于将树上子树操作转换为区间操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, mod = 1e9+7;

int v1, v[N];
struct sgt {
    int sum[N<<2], mul[N<<2], k[N<<2];
    void push_up(int rt) {
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
        if (sum[rt] >= mod) sum[rt] -= mod;
    }
    void build(int l, int r, int rt) {
        mul[rt] = 1;
        if (l == r) {
            if (l == 1) sum[rt] = v1, k[rt] = 1;
            else sum[rt] = 0, k[rt] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
        push_up(rt);
    }
    void pushdown(int rt) {
        if (mul[rt] != 1) {
            sum[rt<<1] = 1ll*sum[rt<<1]*mul[rt]%mod;
            sum[rt<<1|1] = 1ll*sum[rt<<1|1]*mul[rt]%mod;
            k[rt<<1] = 1ll*k[rt<<1]*mul[rt]%mod;
            k[rt<<1|1] = 1ll*k[rt<<1|1]*mul[rt]%mod;
            mul[rt<<1] = 1ll*mul[rt<<1]*mul[rt]%mod;
            mul[rt<<1|1] = 1ll*mul[rt<<1|1]*mul[rt]%mod;
            mul[rt] = 1;
        }
    }
    void update(int L, int R, int val, int l, int r, int rt) {
        if (R < l || r < L || R < L) return;
        if (L <= l && r <= R) {
            sum[rt] = 1ll*sum[rt]*val%mod;
            k[rt] = 1ll*k[rt]*val%mod;
            mul[rt] = 1ll*mul[rt]*val%mod;
            return;
        }
        pushdown(rt);
        int mid = (l + r) >> 1;
        update(L, R, val, l, mid, rt<<1);
        update(L, R, val, mid+1, r, rt<<1|1);
        push_up(rt);
    }
    void update(int p, int val, int l, int r, int rt) {
        if (l == r) {
            sum[rt] = 1ll*val*v[p]%mod;
            k[rt] = val;
            mul[rt] = 1;
            return;
        }
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (p <= mid) update(p, val, l, mid, rt<<1);
        else update(p, val, mid+1, r, rt<<1|1);
        push_up(rt);
    }
    int query(int L, int R, int l, int r, int rt) {
        if (R < l || r < L || R < L) return 0;
        if (L <= l && r <= R) return sum[rt];
        pushdown(rt);
        int mid = (l + r) >> 1;
        return (query(L, R, l, mid, rt<<1) + query(L, R, mid+1, r, rt<<1|1))%mod;
    }
    int query(int p, int l, int r, int rt) {
        if (l == r) return k[rt];
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (p <= mid) return query(p, l, mid, rt<<1);
        return query(p, mid+1, r, rt<<1|1);
    }
} tr;

int in[N], idx, ot[N];
vector<int> g[N];
void dfs(int u) {
    in[u] = ++idx;
    for (auto &i : g[u]) dfs(i);
    ot[u] = idx;
}

int ksm(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) ans = 1ll*ans*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return ans;
}

int n, q, qu[N][4], deg[N];
int main() {
    fast;
    n = 1; cin >> v1 >> q; v[1] = v1;
    for (int i = 1; i <= q; ++i) {
        cin >> qu[i][0];
        if (qu[i][0] == 1) {
            cin >> qu[i][1] >> qu[i][3]; qu[i][2] = ++n;
            g[qu[i][1]].push_back(qu[i][2]);
        } else cin >> qu[i][1];
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) deg[i] = 1;
    tr.build(1, n, 1);
    for (int i = 1; i <= q; ++i) {
        if (qu[i][0] == 1) {
            int fa = qu[i][1], u = qu[i][2];
            v[in[u]] = qu[i][3];
            tr.update(in[fa], ot[fa], 1ll*(deg[fa]+1)*ksm(deg[fa], mod-2)%mod, 1, n, 1);
            deg[fa]++;
            tr.update(in[u], tr.query(in[fa], 1, n, 1), 1, n, 1);
        } else {
            int u = qu[i][1], ans = tr.query(in[u], ot[u], 1, n, 1);
            ans = 1ll*ans*deg[u]%mod;
            ans = 1ll*ans*ksm(tr.query(in[u], 1, n, 1), mod-2)%mod;
            cout << ans << '\n';
        }
    }
    return 0;
}