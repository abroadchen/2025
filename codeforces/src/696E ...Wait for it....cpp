//
// Created by Psy.C on 2026/4/17.
//
/**
head[i] 存储节点i的第一条边的索引
e[i].to 表示边指向的节点，e[i].nxt 指向下一条边
top[x]：x所在重链的顶部节点
dfn[x]：x的时间戳（DFS序）
id[i]：时间戳为i的节点编号
ed[x]：以x为根的子树在DFS序中的结束位置

时间复杂度：单次操作 O(log²n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = 2e18;

ll head[N], cnt;
struct edge {
    ll to, nxt;
    void add(ll x, ll y) {
        to = y, nxt = head[x], head[x] = cnt;
    }
} e[N<<1];

struct node {
    ll pos, val, id;
    bool operator<(const node &o) const {//优先按值排序，值相同时按位置排序
        return val < o.val || (val == o.val && pos < o.pos);
    }
} mn[N<<2];
vector<node> a[N];/// 存储在节点i处的待处理元素

ll dep[N], fa[N], siz[N], son[N];
void dfs(ll x) {//计算每个节点的深度、父节点、子树大小
    dep[x] = dep[fa[x]] + 1; siz[x] = 1;
    for (ll i = head[x]; i; i = e[i].nxt) {
        if (e[i].to != fa[x]) {
            fa[e[i].to] = x;
            dfs(e[i].to);
            siz[x] += siz[e[i].to];
            if (siz[e[i].to] > siz[son[x]])
                son[x] = e[i].to;
        }
    }
}

ll top[N], id[N], dfn[N], tot, ed[N];
void dfs(ll x, ll y) {//构建链
    top[x] = y;
    id[dfn[x]=++tot] = x;
    if (son[x]) dfs(son[x], y);
    for (ll i = head[x]; i; i = e[i].nxt)
        if (e[i].to != fa[x] && e[i].to != son[x])
            dfs(e[i].to, e[i].to);
    ed[x] = tot;
}

void push_up(ll cur, ll l, ll r) {//合并左右子树信息，取最小值
    mn[cur] = min(mn[cur<<1], mn[cur<<1|1]);
}
ll laz[N<<2];//用于区间更新
#define mid ((l+r)>>1)
void build(ll cur, ll l, ll r) {
    laz[cur] = 0;
    if (l == r) {
        mn[cur] = !a[id[l]].empty() ? a[id[l]][0] : node{0, inf, inf};
        return;
    }
    build(cur<<1, l, mid); build(cur<<1|1, mid+1, r);
    push_up(cur, l, r);
}

void pushdown(ll cur, ll l, ll r) {
    if (laz[cur] > 0) {
        laz[cur<<1] += laz[cur];
        laz[cur<<1|1] += laz[cur];
        mn[cur<<1].val += laz[cur];
        mn[cur<<1|1].val += laz[cur];
        laz[cur] = 0;
    }
}
void update(ll cur, ll l, ll r, ll L, ll R, ll x) {
    if (L <= l && r <= R) {
        laz[cur] += x;
        mn[cur].val += x;
        return;
    }
    pushdown(cur, l, r);
    if (L <= mid) update(cur<<1, l, mid, L, R, x);
    if (R > mid) update(cur<<1|1, mid+1, r, L, R, x);
    push_up(cur, l, r);
}
ll get(ll cur, ll l, ll r, ll x) {
    if (l == r) return laz[cur];
    if (x <= mid) return laz[cur] + get(cur<<1, l, mid, x);
    return laz[cur] + get(cur<<1|1, mid+1, r, x);
}

ll pos[N], n;
void del(ll cur, ll l, ll r, ll x) {//将指定位置的元素标记为已删除
    if (l == r) {
        pos[id[l]]++;
        mn[cur] = a[id[l]].size() > pos[id[l]] ? a[id[l]][pos[id[l]]] : node{0, inf, inf};
        if (a[id[l]].size() > pos[id[l]])
            mn[cur].val += get(1, 1, n, l);//更新线段树中该位置的最小值
        return;
    }
    pushdown(cur, l, r);
    if (x <= mid) del(cur<<1, l, mid, x);
    else del(cur<<1|1, mid+1, r, x);
    push_up(cur, l, r);
}

node query(ll cur, ll l, ll r, ll L, ll R) {
    if (L <= l && r <= R) return mn[cur];
    pushdown(cur, l, r);
    node ret = {0, inf, inf};
    if (L <= mid) ret = min(ret, query(cur<<1, l, mid, L, R));
    if (R > mid) ret = min(ret, query(cur<<1|1, mid+1, r, L, R));
    return ret;
}
node query(ll x, ll y) {//查询树上路径x-y上的最小值
    node ret = {0, inf, inf};
    for (; top[x] != top[y]; x = fa[top[x]]) {//将路径分解为重链段
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ret = min(ret, query(1, 1, n, dfn[top[x]], dfn[x]));
    }
    if (dfn[x] > dfn[y]) swap(x, y);
    return min(ret, query(1, 1, n, dfn[x], dfn[y]));
}

inline ll rd() {
    int f = 0, ch = 0; ll x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll m, q, pt[N];
int main() {
    fast;
    n = rd(), m = rd(), q = rd();
    for (ll i = 1; i < n; ++i) {
        ll x = rd(), y = rd();
        e[++cnt].add(x, y), e[++cnt].add(y, x);
    }
    for (ll i = 1; i <= m; ++i) {
        ll x = rd();
        a[x].push_back({x, i, i});
    }
    for (ll i = 1; i <= n; ++i)
        pos[i] = 0, sort(a[i].begin(), a[i].end());
    dfs(1); dfs(1, 1); build(1, 1, n);
    while (q--) {
        ll op = rd();
        if (op == 1) {
            ll x = rd(), y = rd(), k = rd(), num = 0;
            for (num = 0; num < k; ++num) {
                auto now = query(x, y);//找到路径上最小值
                if (now.pos == 0) break;//没有可取元素
                pt[num+1] = now.id;//记录结果
                del(1, 1, n, dfn[now.pos]);//删除该元素
            }
            cout << num;
            for (ll i = 1; i <= num; ++i)
                cout << ' ' << pt[i];
            cout << '\n';
        } else {
            ll x = rd(), k = rd();
            update(1, 1, n, dfn[x], ed[x], k);//对子树进行区间更新
        }
    }
    return 0;
}