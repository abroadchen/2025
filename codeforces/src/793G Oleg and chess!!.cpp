//
// Created by Psy.C on 2026/9/15.
//
/**
Dinic 最大流（bfs / dfs / 邻接表 st/e/adde，反向边 e[i^1]）。
两棵线段树 r1、r2（线段树优化建图）：一棵叶子→根（build，容量为区间大小），一棵根→叶子（build2），用于把"区间连到点 / 点连到区间"压缩成 O(log n) 条边。
ODT（珂朵莉树 / 区间赋值分块）‍：set<l2> + split + solve，用颜色段维护区间覆盖，碰到不同颜色的交界就建边。
矩形事件差分（扫描线）‍：每个矩形拆成 (p=x1, +1) 和 (p=x2+1, -1) 两个事件，sort 后扫过去。
l[K] 存的是三元组 {l, r, p, t}，l2 是 {l, r, c} 颜色段。l1 的排序键是 (p, t)——按横坐标 p 扫描

建一棵"自下而上"的树：孩子 → 父亲，容量 = 区间大小。
beg（源点）连到每个叶子，容量 1。这样 beg 能往树里注入流，且沿树向上汇聚容量是子区间长度
另一棵"自上而下"的树：父亲 → 孩子，容量 = 区间大小，叶子 → ed（汇）容量 1
把线段树中覆盖区间 [L,R] 的 O(log n) 个节点，与外部点 v 连边。
t==1：树节点 → v（套在 r1 上，叶子→根树）；t==2：v → 树节点（套在 r2 上，根→叶子树）。
容量为子树区间长度。
作用：一个"区间"作为流路中介，可以表示"这段区间整体分配给某外部点"
标准珂朵莉 split(x)：保证存在起点为 x 的段。把横跨 x 的段 [o,p] 拆成 [o,x-1] 和 [x,p]

先把 [l,r] 的边界切好（split）。
当 val == -1（即事件类型 t=1，插入一个矩形/新颜色区域）时，遍历 [L,R) 之间所有颜色段：
若段颜色 i->c 既不是新颜色 nw 也不是 -1（即这段之前属于别的"矩形色块"），就新建中间点 o，
add(r1, ..., i->c, nw-1, o, 1)：把"颜色区间 [旧色, 新色-1] 的叶子段"连向 o；
add(r2, ..., i->l, i->r, o, 2)：从 o 连向"这段占据的坐标区间"。
然后做珂朵莉区间赋值：把 [l,r] 及相邻同色段合并染色成 val。
语义还原：ODT 在维护"坐标列上的颜色划分"，每个颜色代表一个矩形的可见区域。当扫描线推进到某 y（矩形纵坐标），把一个 y 区间 x∈[l,r] 划分为某种矩形颜色。相交/覆盖时，被覆盖的旧颜色区域要"释放/换色"，于是建边表示这种"不同矩形互相冲突"的关系，最后用最大流求出最大可选数量（最大独立集 / 最小割）
每个矩形 (x1,y1,x2,y2) 拆成两个扫描线事件：p=x1 进入（t=1）、p=x2+1 离开（t=-1），区间取纵坐标 [y1,y2]。再补一个 p=n+1 的哨兵。
sv 按 p（横坐标）排序扫描，贯穿 ODT 染色与建边。
最后从源 beg 到汇 ed 跑 Dinic 最大流，输出 ans。
总体逻辑：这是"二维区间选点/矩形最大数"类问题，用扫描线把矩形在纵轴上分割成颜色段（ODT），借助两棵线段树把"区间 ↔ 颜色"的冲突建边（线段树优化建图，把容量当区间长度），把问题规约为最大流（=最小割=最大独立集）‍求解
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 8e4+9, M = 9e5+9, K = 2e4+9, inf = 0x3f3f3f3f;

struct edge { int to, nxt, fl; } e[M];
int E = -1, st[N];
void adde(int x, int y, int fl) {
    E++;
    e[E] = {.to = y, .nxt = st[x], .fl = fl};
    st[x] = E;
    E++;
    e[E] = {.to = x, .nxt = st[y], .fl = 0};
    st[y] = E;
}

int V, lev[N];
queue<int> fq;
bool bfs(int s, int t) {
    for (int i = 1; i <= V; ++i) lev[i] = V+1;
    lev[s] = 0; fq.push(s);
    while (!fq.empty()) {
        int d = fq.front(); fq.pop();
        for (int i = st[d]; i != -1; i = e[i].nxt) {
            if (e[i].fl == 0 || lev[e[i].to] <= lev[d]+1) continue;
            lev[e[i].to] = lev[d] + 1;
            fq.push(e[i].to);
        }
    }
    return lev[t] != V + 1;
}

int cur[N];
int dfs(int s, int t, int fl) {
    if (s == t) return fl;
    int nfl = 0;
    for (int& i = cur[s]; i != -1; i = e[i].nxt) {
        int o = min(fl-nfl, e[i].fl);
        if (o == 0 || lev[e[i].to] != lev[s] + 1) continue;
        int p = dfs(e[i].to, t, o);
        if (p < o) lev[e[i].to] = V + 1;
        e[i].fl -= p; e[i^1].fl += p; nfl += p;
        if (nfl == fl) break;
    }
    return nfl;
}

struct l1 {
    int l, r, p, t;
    bool operator<(const l1 &o) const {
        return p < o.p || (p == o.p && t < o.t);
    }
} l[K];

struct l2 {
    int l, r, c;
    bool operator<(const l2 &o) const {
        return l < o.l;
    }
};

int beg, lc[N], rc[N];
void build(int k, int l, int r) {
    if (l == r) { adde(beg, k, 1); return; }
    int m = (l+r)>>1;
    lc[k] = ++V; rc[k] = ++V;
    build(lc[k], l, m); build(rc[k], m+1, r);
    adde(lc[k], k, m-l+1); adde(rc[k], k, r-m);
}
int ed;
void build2(int k, int l, int r) {
    if (l == r) { adde(k, ed, 1); return; }
    int m = (l+r)>>1;
    lc[k] = ++V; rc[k] = ++V;
    build2(lc[k], l, m); build2(rc[k], m+1, r);
    adde(k, lc[k], m-l+1); adde(k, rc[k], r-m);
}

void add(int k, int l, int r, int L, int R, int v, int t) {
    if (l > R || r < L) return;
    if (l >= L && r <= R) {
        t == 1 ? adde(k, v, r-l+1) : adde(v, k, r-l+1);
        return;
    }
    int m = (l+r)>>1;
    add(lc[k], l, m, L, R, v, t);
    add(rc[k], m+1, r, L, R, v, t);
}

set<l2> s;
auto split(int x) {
    auto t = s.lower_bound({.l = x, .r = x, .c = 0});
    if (t == s.end() || t->l > x) --t;
    if (t->l == x) return t;
    int o = t->l, p = t->r, c = t->c;
    s.erase(t); s.insert({.l = o, .r = x-1, .c = c});
    return s.insert({.l = x, .r = p, .c = c}).first;
}

int r1, r2, n;
void solve(int l, int r, int val, int nw) {
    auto R = split(r+1), L = split(l);
    if (val == -1) {
        for (auto i = L; i != R; ++i) {
            if (i->c == nw || i->c == -1) continue;
            int o = ++V;
            add(r1, 1, n, i->c, nw-1, o, 1);//旧颜色 i->c 的区间 → 新点 o（r1）
            add(r2, 1, n, i->l, i->r, o, 2);//o → 位置区间 [i->l,i->r]（r2）
        }
    }
    auto x = L, y = L;
    if (L != s.begin()) {
        --x;
        if (x->c == val) { l = x->l; s.erase(x); }
    }
    if (y != s.end() && y->c == val) { ++R; r = y->r; s.erase(y); }
    s.erase(L, R); s.insert({.l = l, .r = r, .c = val});//整体染色成 val
}

int q, cnt;
int main() {
    memset(st,0xff,sizeof(st));
    scanf("%d %d",&n,&q);
    beg = ++V,ed = ++V;
    r1 = ++V,r2 = ++V;
    build(r1,1,n);
    build2(r2,1,n);
    for(int i = 1; i <= q; i ++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        l[++cnt] = {.l = y1,.r = y2,.p = x1,.t = 1};//进入
        l[++cnt] = {.l = y1,.r = y2,.p = x2 + 1,.t = -1};//离开
    }
    l[++cnt] = {.l = 1,.r = n,.p = n + 1,.t = 1};//尾部哨兵
    sort(l + 1,l + cnt + 1);//按 p 扫描
    s.insert({.l = 1,.r = n,.c = 1});//初始整段颜色 1
    for(int i = 1; i <= cnt; i ++){
        if(l[i].t == -1)
            solve(l[i].l,l[i].r,l[i].p,l[i].p);//结束一个矩形
        else
            solve(l[i].l,l[i].r,-1,l[i].p);//开始一个矩形
    }
    int ans = 0;
    while(bfs(beg,ed))//跑最大流
        memcpy(cur,st,sizeof(int) * (V + 1)),ans += dfs(beg,ed,inf);
    printf("%d\n",ans);
    return 0;
}