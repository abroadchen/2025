//
// Created by Psy.C on 2026/2/11.
//

#include <iostream>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100055
using namespace std;

struct node {
    int l, r;
    ll val, laz;
} q[N<<2];

int d[N], p[N], siz[N], son[N];
vector<int> g[N];
void dfs(const int u, const int fa, const int step) {
    d[u] = step; p[u] = fa; siz[u] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        const int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u, step + 1);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]])
            son[u] = v;
    }
}

int top[N], id[N], la[N], num, pos[N];
void dfs2(const int u, const int tp) {
    top[u] = tp; id[u] = la[u] = ++num; pos[id[u]] = u;
    if (son[u] == -1) return;
    dfs2(son[u], tp);
    for (int i = 0; i < g[u].size(); ++i) {
        if (const int v = g[u][i]; v != son[u] && v != p[u])
            dfs2(v, v);
    }
    la[u] = num;
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        u = p[top[u]];
    }
    return d[u] < d[v] ? u : v;
}

int root;
int LCA(const int u, const int v) {
    int a = lca(u, v), c = lca(root, v);
    if (int b = lca(root, u); d[a] < d[b]) swap(a, b);
    if (d[a] < d[c]) swap(a, c);
    return a;
}

int near_lca(int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    if (top[u] == top[v]) return pos[id[u] + 1];
    while (top[u] != top[v]) {
        if (d[top[u]] > d[top[v]]) swap(u, v);
        if (p[top[v]] == u) break;
        v = p[top[v]];
    }
    if (top[u] == top[v]) return pos[id[u] + 1];
    return top[v];
}

void push_up(const int rt) {
    q[rt].val = q[rt<<1].val + q[rt<<1|1].val;
}

ll val[N];
void build(const int l, const int r, const int rt) {
    q[rt].l = l; q[rt].r = r; q[rt].laz = 0;
    if (l == r) {
        q[rt].val = val[pos[l]];
        return;
    }
    const int m = (l + r) >> 1;
    build(l, m, rt<<1); build(m+1, r, rt<<1|1);
    push_up(rt);
}

void pushdown(const int rt) {
    const int l = q[rt].l, r = q[rt].r, m = (l + r) >> 1;
    if (q[rt].laz != 0) {
        const ll c = q[rt].laz;
        q[rt<<1].laz += c; q[rt<<1|1].laz += c;
        q[rt<<1].val += 1ll*(m-l+1)*c; q[rt<<1|1].val += 1ll*(r-m)*c;
        q[rt].laz = 0;
    }
}

void update(const int rt, const int L, const int R, const int c) {
    const int l = q[rt].l, r = q[rt].r;
    if (L <= l && r <= R) {
        q[rt].val += 1ll*(r-l+1)*c;
        q[rt].laz += c;
        return;
    }
    pushdown(rt);
    const int m = (l + r) >> 1;
    if (L <= m) update(rt<<1, L, R, c);
    if (m < R) update(rt<<1|1, L, R, c);
    push_up(rt);
}

ll query(const int rt, const int L, const int R) {
    const int l = q[rt].l, r = q[rt].r;
    if (L <= l && r <= R) return q[rt].val;
    pushdown(rt);
    const int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m) ret += query(rt<<1, L, R);
    if (m < R) ret += query(rt<<1|1, L, R);
    return ret;
}

void add(const int u, const int v) {
    g[u].push_back(v); g[v].push_back(u);
}

ll Query(const int x) { return query(1, id[x], la[x]); }
void Update(const int x, const int c) { update(1, id[x], la[x], c); }

bool ok(const int x, const int y) {
    if (id[x] >= id[y] && id[x] <= la[y]) return true;
    return false;
}

void init() {
    memset(son, -1, sizeof(son));
    memset(p, -1, sizeof(p));
    root = 1;
}

int n, Q, k;

int main() {
    fast;
    init();
    cin >> n >> Q;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; add(u, v);
    }
    dfs(1, -1, 0); dfs2(1, 1); build(1, num, 1);
    while (Q--) {
        cin >> k;
        if (k == 1) {
            int v; cin >> v;
            root = v;
        } else if (k == 2) {
            int u, v, x; cin >> u >> v >> x;
            int in = 0, rt;
            if (ok(u, root)) in++;
            if (ok(v, root)) in++;
            if (in == 1) rt = root;
            else if (in == 2) rt = lca(u, v);
            else rt = LCA(u, v);
            if (rt == root) Update(1, x);
            else if (ok(rt, root)) Update(rt, x);
            else if (ok(root, rt)) {
                Update(1, x);
                const int y = near_lca(root, rt);
                Update(y, -x);
            } else Update(rt, x);
        } else if (k == 3) {
            int v; cin >> v;
            ll ans;
            if (v == root) ans = Query(1);
            else if (ok(v, root)) ans = Query(v);
            else if (ok(root, v)) {
                ans = Query(1);
                const int x = near_lca(root, v);
                ans -= Query(x);
            } else ans = Query(v);
            cout << ans << '\n';
        }
    }
    return 0;
}