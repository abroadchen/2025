//
// Created by Psy.C on 2026/3/3.
//
/**
h[N]: 节点权重
mn[N]: 以当前节点为根的子树中的最小值
nxt[N]: 严格大于当前节点的最小值
st: multiset维护有序序列
c[N]: 集合，存储具有相同最小值的节点
e[N]: 邻接表表示的树
dfs: 深度优先搜索，维护multiset并计算mn和nxt值

计算每个节点的r值
对线段树进行区间更新
如果根节点最小值非负，输出0
找到最后一个小于0的位置

遍历每个节点，尝试作为候选答案
检查各种约束条件
临时更新线段树
如果满足条件，更新答案
恢复线段树状态

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e6+1, inf = 0x3f3f3f3f;
struct node { int mn, lz; } tr[N<<2];

inline void push_up(const int u) {
    tr[u].mn = min(tr[u<<1].mn, tr[u<<1|1].mn);
}
int m;
void build(const int u, const int l, const int r) {
    if (l >= r) { tr[u].mn = -(m-l+1); return; }//负数序列
    const int mid = (l+r)>>1;
    build(u<<1, l, mid), build(u<<1|1, mid+1, r);
    push_up(u);
}

inline void modify(const int u, const int w) {//单点修改
    tr[u].mn += w; tr[u].lz += w;
}
void pushdown(const int u) {
    if (tr[u].lz) {
        modify(u<<1, tr[u].lz), modify(u<<1|1, tr[u].lz);
        tr[u].lz = 0;
    }
}
void update(const int u, const int l, const int r, const int L, const int R, const int w) {
    if (L > R) return;
    if (l == L && r == R) { modify(u, w); return; }
    const int mid = (l+r)>>1; pushdown(u);
    if (R <= mid) update(u<<1, l, mid, L, R, w);
    else if (L > mid) update(u<<1|1, mid+1, r, L, R, w);
    else {
        update(u<<1, l, mid, L, mid, w);
        update(u<<1|1, mid+1, r, mid+1, R, w);
    }
    push_up(u);
}

int query(const int u, const int l, const int r, const int x) {
    if (l >= r) return tr[u].mn;
    const int mid = (l+r)>>1; pushdown(u);
    return x <= mid ? query(u<<1, l, mid, x) : query(u<<1|1, mid+1, r, x);
}

int h[N], mn[N], nxt[N];
multiset<ii> st;
vector<int> c[N], e[N];
void dfs(int u, const int fa) {
    st.insert({h[u], u});
    auto it = st.begin();
    mn[u] = it->first, c[it->second].push_back(u);
    ++it;
    if (it != st.end()) nxt[u] = it->first;
    else nxt[u] = inf;
    for (const auto v : e[u])
        if (v != fa) dfs(v, u);
    st.erase(st.find({h[u], u}));
}



int n, a[N], r[N], pos, ans = inf;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        e[x].push_back(y); e[y].push_back(x);
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    sort(a + 1, a + m + 1);
    dfs(1, 0), build(1, 1, m);
    for (int i = 1; i <= n; ++i) {
        r[i] = upper_bound(a + 1, a + m + 1, mn[i]) - a - 1;
        update(1, 1, m, 1, r[i], 1);
    }
    if (tr[1].mn >= 0) { cout << "0\n"; return 0; }
    for (pos = m; pos >= 1; pos--)
        if (query(1, 1, m, pos) < 0) break;
    for (int i = 1; i <= n; ++i) {
        if (r[i] >= pos || nxt[i] < a[pos] || c[i].size() < -tr[1].mn)
            continue;
        for (const auto v : c[i]) {
            int x = min(a[pos], nxt[v]);
            x = upper_bound(a + 1, a + m + 1, x) - a - 1;
            update(1, 1, m, r[v]+1, x, 1);
        }
        if (tr[1].mn >= 0) ans = min(ans, a[pos] - h[i]);
        for (auto v : c[i]) {
            int x = min(a[pos], nxt[v]);
            x = upper_bound(a + 1, a + m + 1, x) - a - 1;
            update(1, 1, m, r[v]+1, x, -1);
        }
    }
    if (ans == inf) cout << "-1\n"; else cout << ans << '\n';
    return 0;
}