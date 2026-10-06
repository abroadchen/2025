//
// Created by Psy.C on 2026/10/6.
//
/**
邻接表（前向星）存无向图，每条边加两次（add(v,i) 和 add(i,v)）
从根 (1,1) 开始 DFS。
dfn[x] = ++tim：给节点赋 DFS 时间戳，子树内节点的时间戳连续。
w[dfn[x]] = a[x]：按时间戳把权值放入线段树构建数组。
sz[x] 记录子树大小，因此 x 的子树区间是 [dfn[x], dfn[x]+sz[x]-1]
叶子存的是 w[L]（即某节点的权值）。
cover(o)：节点整段取反 —— tag *= -1 表示取反标；sum = 区间长度 - sum（因为 0↔1 取反后 1 的个数 = 总数 − 原来的 1 的个数）。
tag 用 1 表示无异、-1 表示待取反的懒标记。
push_down：把取反懒标记下传给左右孩子。
update：区间取反，完全覆盖走 cover，否则下传后递归。
query：区间求和，完全覆盖直接返回 sum。
这是一个常见的 "01 区间翻转求和"线段树实现，正确且高效（O(log n) 每次）
读 n、边、权值。
dfs(1,1) 建立 DFS 序，tt.build 建线段树。
循环处理 t 个操作：
g x：查询子树 [dfn[x], dfn[x]+sz[x]-1] 的和 → 即子树内"黑点/值为1"的个数。
p x：将该子树区间取反
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+10;

struct node { int to, nxt; } e[N<<1];

int tot, head[N];
void add(int x, int y) {
    e[++tot].to = y; e[tot].nxt = head[x]; head[x] = tot;
}

int sz[N], dfn[N], tim, w[N], a[N];
void dfs(int x, int fa) {
    sz[x] = 1; dfn[x] = ++tim; w[dfn[x]] = a[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        int to = e[i].to;
        if (to == fa) continue;
        dfs(to, x);
        sz[x] += sz[to];
    }
}

struct Tr {
    struct node { int lc, rc, tag, sum; } tr[N<<2];
#define l(o) tr[o].lc
#define r(o) tr[o].rc
#define tag(o) tr[o].tag
#define sum(o) tr[o].sum
    void push_up(int o) { sum(o) = sum(o<<1) + sum(o<<1|1); }
    void cover(int o) {
        tag(o) *= -1;
        sum(o) = (r(o) - l(o) + 1) - sum(o);
    }
    void push_down(int o) {
        if (tag(o) == -1) {
            cover(o<<1); cover(o<<1|1);
            tag(o) = 1;
        }
    }
    void build(int o, int L, int R) {
        l(o) = L, r(o) = R; tag(o) = 1;
        if (L == R) { sum(o) = w[L]; return; }
        int mid = (L + R) >> 1;
        build(o<<1, L, mid); build(o<<1|1, mid+1, R);
        push_up(o);
    }
    void update(int o, int L, int R) {
        if (L <= l(o) && R >= r(o)) { cover(o); return; }
        push_down(o);
        int mid = (l(o) + r(o)) >> 1;
        if (L <= mid) update(o<<1, L, R);
        if (R > mid) update(o<<1|1, L, R);
        push_up(o);
    }
    int query(int o, int L, int R) {
        int ans = 0;
        if (L <= l(o) && R >= r(o)) { return sum(o); }
        push_down(o);
        int mid = (l(o) + r(o)) >> 1;
        if (L <= mid) ans += query(o<<1, L, R);
        if (R > mid) ans += query(o<<1|1, L, R);
        return ans;
    }
} tt;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

char op[10];
int main() {
    fast;
    int n = rd();
    for (int i = 2, v; i <= n; ++i) {
        v = rd(); add(v, i), add(i, v);
    }
    for (int i = 1; i <= n; ++i) a[i] = rd();
    dfs(1, 1); tt.build(1, 1, n);
    int t = rd(), x;
    while (t--) {
        scanf("%s", op+1); x = rd();
        if (op[1] == 'g') cout << tt.query(1, dfn[x], dfn[x]+sz[x]-1) << '\n';
        if (op[1] == 'p') tt.update(1, dfn[x], dfn[x]+sz[x]-1);
    }
    return 0;
}