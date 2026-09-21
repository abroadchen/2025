//
// Created by Psy.C on 2026/9/21.
//
/**
rollback 可撤销并查集（dsu）‍
线段树分治（sgt）‍：把每条边的存活时间区间挂到线段树节点，DFS 时"进入节点就加入边，离开就回滚"
判断每个时刻图是否为二分图（拆点：u 与 v+n，v 与 u+n 相连，若 find(u)==find(v) 则冲突=非二分）

用 启发式合并（按高度/大小）‍，但 不路径压缩，这样能通过操作栈完美回滚。
每次 merge 把被修改的节点 x 和"是否增高"记录到栈 st。
re(lst) 回滚到栈顶数量为 lst 的状态，用于线段树分治离开节点时撤销
线段树分治核心：把"某条边在 [l,r] 时间区间内始终存在"这个信息，通过 insert 分解成 O(log m) 个线段树节点。DFS 时"进入节点加入边、离开节点回滚边"，就能在 O(m log m) 内处理全部动态时段。
二分图判定用拆点：把点 u 拆成 u 和 u+n 两个点，边 (u,v) 连 (u, v+n) 和 (v, u+n)。若某时刻 find(u)==find(v)（u 和 v 在同一集合=同色），说明冲突，不是二分图。
若某个节点内加入边时发生冲突，则该节点子树的所有叶子时刻都不可能是二分图，不再深入。
到达叶子（某具体时刻）仍 ok，则 ans[该时刻]=1
用 map 记录每条边当前的"开始存在时刻"。同一条边出现两次，表示它在 [第一次, 第二次-1] 之间始终存在（对应"添加/删除"）。
操作结束后仍在 map 中的边，存活到时刻 m。
由此把每条边转换成一个时间区间，用于线段树分治
逐时刻输出该时刻图是否仍为二分图（YES/NO）
 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+10;

struct dsu {
    int f[N], h[N], top;
    void init(int n) { for (int i = 1; i <= n; ++i) f[i] = i, h[i] = 1; }
    int find(int x) { return x == f[x] ? x : find(f[x]); }
    ii st[N];
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (h[x] > h[y]) swap(x, y);
        f[x] = y, st[++top] = {x, h[x]==h[y]};
        if (h[x] == h[y]) h[y]++;
    }
    void re(int lst) {
        for (; top > lst; --top) {
            int x = st[top].first, add = st[top].second;
            h[f[x]] -= add, f[x] = x;
        }
    }
} f;

struct edge { int x, y; } e[N];

int n;
bool ans[N];
struct sgt {
    struct node {
        int l, r;
        vector<int> id;
    } tr[N<<2];
#define lc (x<<1)
#define rc (x<<1|1)
    void build(int x, int l, int r) {
        tr[x].l = l, tr[x].r = r;
        if (l == r) return;
        int mid = (l+r)>>1;
        build(lc, l, mid); build(rc, mid+1, r);
    }
    void insert(int l, int r, int v, int x=1) {
        if (tr[x].l >= l && tr[x].r <= r) return tr[x].id.push_back(v), void();
        int mid = (tr[x].l + tr[x].r) >> 1;
        if (l <= mid) insert(l, r, v, lc);
        if (r > mid) insert(l, r, v, rc);
    }
    void dfs(int x=1) {
        bool ok = true;
        int lst = f.top, mid = (tr[x].l + tr[x].r) >> 1;
        for (int i : tr[x].id) {
            int u = e[i].x, v = e[i].y;
            if (f.find(u) == f.find(v)) { ok = false; break; }
            f.merge(u, v+n), f.merge(v, u+n);
        }
        if (ok) {
            if (tr[x].l == tr[x].r) ans[tr[x].l] = 1;
            else dfs(lc), dfs(rc);
        }
        f.re(lst);
    }
} T;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

map<ii, int> mp;
int cnt(0);
int main() {
    n = rd();
    int m = rd();
    f.init(2*n), T.build(1, 1, m);
    for (int i = 1; i <= m; ++i) {
        int x = rd(), y = rd();
        if (!mp.contains({x, y})) { mp[{x, y}] = i; continue; }
        e[++cnt] = {.x = x, .y = y}, T.insert(mp[{x, y}], i-1, cnt);
        mp.erase({x, y});
    }
    for (auto [fst, snd] : mp)
        e[++cnt] = {.x = fst.first, .y = fst.second}, T.insert(snd, m, cnt);
    T.dfs();
    for (int i = 1; i <= m; ++i) puts(ans[i] ? "YES" : "NO");
    return 0;
}