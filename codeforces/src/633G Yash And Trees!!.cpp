//
// Created by Psy.C on 2026/3/30.
//
/**
操作1：子树增加
在u的子树范围内增加x（模m）
通过循环移位实现
操作2：子树查询质数个数
查询子树中所有不同的值
与质数表按位与，统计质数个数

预处理：O(M log log M)（筛质数）+ O(n)（树遍历）
单次操作：O(log n × M/32)
总体：O(q log n × M/32)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 1e3+5;

struct node { int v, nxt; } e[N<<1];

int head[N], cnt;
void add(int u, int v) {
    e[++cnt] = {v, head[u]}, head[u] = cnt;
}

bitset<M> tr[N<<2];
void push_up(int u) { tr[u] = tr[u<<1]|tr[u<<1|1]; }

///线段树，每个节点是bitset
int tag[N<<2], m;
bitset<M> f;///全1的bitset，用于位运算
///&f 用于截断超出范围的位
void push_down(int u) {
    if (tag[u]) {
        tag[u<<1] = (tag[u<<1]+tag[u])%m, tag[u<<1|1] = (tag[u<<1|1]+tag[u])%m;
        tr[u<<1] = tr[u<<1]<<tag[u]|tr[u<<1]>>(m-tag[u]);//将bitset向左循环移动tag[u]位
        tr[u<<1|1] = tr[u<<1|1]<<tag[u]&f|tr[u<<1|1]>>(m-tag[u]);
        tag[u] = 0;
    }
}
void build(int u, int l, int r, int *a) {
    if (l == r) {
        tr[u].reset();
        tr[u].set(a[l]);
        return;
    }
    int mid = (l+r)>>1;
    build(u<<1, l, mid, a); build(u<<1|1, mid+1, r, a);
    push_up(u);
}
void update(int u, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        tag[u] = (tag[u]+val)%m;
        tr[u] = tr[u]<<val&f|tr[u]>>(m-val);
        return;
    }
    push_down(u);
    int mid = (l+r)>>1;
    if (L <= mid) update(u<<1, l, mid, L, R, val);
    if (mid < R) update(u<<1|1, mid+1, r, L, R, val);
    push_up(u);
}

bitset<M> ans;
void query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) { ans |= tr[u]; return; }
    push_down(u);
    int mid = (l+r)>>1;
    if (L <= mid) query(u<<1, l, mid, L, R);
    if (mid < R) query(u<<1|1, mid+1, r, L, R);
}

int d[N], siz[N], dfn[N], rfn[N], tot;
void dfs(int u, int fa) {
    d[u] = d[fa]+1, siz[u] = 1, dfn[u] = ++tot, rfn[tot] = u;
    for (int i = head[u], v; i != 0; i = e[i].nxt) {
        if ((v=e[i].v) != fa) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}

int n, a[N], b[N], q;
bitset<M> pr;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) f.set(i);
    for (int i = 2; i < m; ++i) pr.set(i);
    for (int i = 2; i < m; ++i)
        if (pr[i])
            for (int j = 2*i; j < m; j += i)
                pr.reset(j);//pr保存质数标记
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; a[i] %= m;
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) b[i] = a[rfn[i]];//将树上的节点映射到连续的线性区间
    build(1, 1, n, b);
    cin >> q;
    while (q--) {
        int op, u, x; cin >> op >> u;
        if (op == 1) {
            cin >> x;
            update(1, 1, n, dfn[u], dfn[u]+siz[u]-1, x%m);
        } else {
            ans.reset();
            query(1, 1, n, dfn[u], dfn[u]+siz[u]-1);
            int res = (ans&pr).count();
            cout << res << '\n';
        }
    }
    return 0;
}