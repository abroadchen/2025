//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
dt 是哨兵（val=inf，id=0），用于空查询返回
这是一棵 维护区间 [l,r] 内"最小 (val, id)"的线段树。每个叶节点对应下标 p，存一对 {val, id}；内部节点存左右孩子中 val 更小的那对（push_up 用 min 合并，比较规则是 val 优先）。dt(inf,0) 作空区间返回值。

括号注意：这类递归指针线段树，build/modify/query 里用默认参数 i=rt、l=1,r=n，通过引用 pd &i 递归建树/更新。node a,b 之间用 min 需要重载了 operator<（val 升序）
用链式前向星 head[r] 挂上所有右端点是 r 的查询。
因为接下来按 r 从 1 到 n 扫描，扫到 r 时就能回答所有右端点为 r 的查询【离线处理】。
e[j].to 存左端点 l，e[j].w 存查询编号 i
pos[x] 记录值 x 上一次出现的下标。
扫描到位置 i（值 x）：
若 x 之前出现过（pos[x] 非 0）：把上一次位置 pos[x] 处的权标记为"不再是最新"（modify(pos[x], dt) 清零），并把当前位置 i 记为"x 最近一次出现的位置，val=pos[x]"。这样线段树中每个值 x 只会在它最后出现的那个下标处保留一条有效记录 {上一次出现的下标 pos[x], x}。
若 x 第一次出现（pos[x]=0）：modify(i, {0, x})——在 i 处放一个 {0, x}（val=0 表示"它在区间内是首次出现"）。
更新 pos[x]=i。
关键洞察：线段树下标 m 处存的 {val=pos[a[m]], id=a[m]} 意思是——值 a[m] 上一次出现的位置是 val。那么查询区间 [l, r] 时，query(l,r) 返回这些记录里 val 最小的那一条 (minval, id)：

若 minval < l：说明值 id 上一次出现早于 l，也就是 在 [l,r] 内 id 是第一次/唯一一次出现，则 ans = id。
若 minval >= l：说明该值在 [l,r] 内已经重复出现（或不存在），ans = 0。
这就是经典的 "求区间内只出现一次的数" 或 "区间内某值是否唯一" 的离线段树解法
按查询编号输出各自结果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 5e5+5, inf = 0x7fffffff;

struct node {
    int val, id;
    node(int v, int i) : val(v), id(i) {}
    bool operator<(const node& o) const { return val < o.val; }
} dt(inf, 0);

struct sgt {
    node mn;
    sgt *lc, *rc;
    sgt(int x, int i): mn(x,i) { lc = rc = nullptr; }
} *rt;
typedef sgt *pd;

inline void push_up(pd i) { i->mn = min(i->lc->mn, i->rc->mn); }

void build(int l, int r, pd &i = rt) {
    i = new sgt(inf, 0);
    if (l != r) {
        int mid = (l+r)>>1;
        build(l, mid, i->lc), build(mid+1, r, i->rc);
    }
}

int n;
void modify(int p, node x, pd i=rt, int l=1, int r=n) {
    if (l == r) i->mn = x;
    else {
        int mid = (l+r)>>1;
        if (mid >= p) modify(p, x, i->lc, l, mid);
        else modify(p, x, i->rc, mid+1, r);
        push_up(i);
    }
}
node query(int L, int R, pd i=rt, int l=1, int r=n) {
    if (r < L || l > R) return dt;
    if (l >= L && r <= R) return i->mn;
    int mid = (l+r)>>1;
    return min(query(L, R, i->lc, l, mid), query(L, R, i->rc, mid+1, r));
}

struct edge { int to, w, nxt; } e[N];
int cnt, head[N];
inline void add(int u, int v, int w) {
    e[++cnt] = {v, w, head[u]}, head[u] = cnt;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], m, pos[N], ans[N];
int main() {
    fast;
    n = rd();
    rep(i,n) a[i] = rd();
    m = rd();
    rep(i,m) { int l = rd(), r = rd(); add(r, l, i); }
    build(1, n);
    rep(i,n) {
        int x = a[i];
        if (pos[x]) modify(pos[x], dt), modify(i, {pos[x], x});
        else modify(i, {0, x});
        pos[x] = i;
        for (int j = head[i]; j; j = e[j].nxt) {
            node y = query(e[j].to, i);
            ans[e[j].w] = y.val < e[j].to ? y.id : 0;
        }
    }
    rep(i,m) cout << ans[i] << '\n';
    return 0;
}