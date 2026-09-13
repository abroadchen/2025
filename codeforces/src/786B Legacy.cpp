//
// Created by Psy.C on 2026/9/13.
//
/**
to[] / ti[]：分别存储两棵线段树节点的编号（节点号先分配 place，构造图节点）。
e[]：邻接表，最多 N×10 条边。
cnt：动态分配图节点编号，初始 cnt=n（前面的 1..n 是真实点）
叶子：to[k]=ti[k]=l，叶子就是真实点本身。
内部节点：为 to[k] 和 ti[k] 各分配一个新图节点（++cnt）。
建两棵树：
to 树（出树/区间→点方向）用它聚合到区间再下到点：子节点 to[child] 连向父节点 to[k]，权 0，方向子→父（表示从某局部能到聚合的大区间节点）。
ti 树（入树/点→区间方向）父节点下指子节点：ti[k] 连向子节点，权 0，方向父→子（表示从大区间节点能分发到每个叶子/点）。
这样，两端线段树 + 叶子即真实点 = 完整图

从点 fr 到区间 [L,R] 内的所有点加边权 w。
思路：把 [L,R] 用线段树分解成 O(log n) 个节点，fr 直接连到每个区间节点的 ti[k]（入树节点），再由入树向下分发到叶子（权 0）。边数从 O(len) 降为 O(log n)
从区间 [L,R] 内所有点 到 单点 fr 加边 w。
把 [L,R] 分解成若干 to[k]（出树节点），由出树自下而上聚合（子→父 权 0），再由 to[k] 一次性连到 fr，权 w

op==1：直接加边。
op==2：update 单点→区间。
op==3：modify 区间→单点。
最后 Dijkstra 输出 s 到每个点的最短路，不可达输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, inf = 0x3f3f3f3f3f3f3f3f;

int to[N<<2], ti[N<<2], cnt;
vector<ii> e[N*10];
inline void build(int k, int l, int r) {
    if (l == r) { to[k] = l; ti[k] = l; return; }
    int mid = (l + r) >> 1;
    build(k<<1, l, mid); build(k<<1|1, mid+1, r);
    to[k] = ++cnt; ti[k] = ++cnt;
    e[to[k<<1]].emplace_back(to[k], 0);
    e[to[k<<1|1]].emplace_back(to[k], 0);
    e[ti[k]].emplace_back(ti[k<<1], 0);
    e[ti[k]].emplace_back(ti[k<<1|1], 0);
}

inline void update(int k, int l, int r, int L, int R, int fr, int w) {
    if (L <= l && r <= R) {
        e[fr].emplace_back(ti[k], w);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) update(k<<1, l, mid, L, R, fr, w);
    if (mid < R) update(k<<1|1, mid+1, r, L, R, fr, w);
}

inline void modify(int k, int l, int r, int L, int R, int fr, int w) {
    if (L <= l && r <= R) {
        e[to[k]].emplace_back(fr, w);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid) modify(k<<1, l, mid, L, R, fr, w);
    if (mid < R) modify(k<<1|1, mid+1, r, L, R, fr, w);
}

struct node {
    int pos, dis;
    bool operator<(node o) const {
        return dis > o.dis;//小顶堆
    }
};

int dis[N*10], s;
priority_queue<node> q;
inline void dijkstra() {
    memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    node t{}; t.dis = 0; t.pos = s; q.push(t);
    while (!q.empty()) {
        auto now = q.top(); q.pop();
        if (dis[now.pos] != now.dis) continue;//过时节点跳过
        for (auto&[fst, snd] : e[now.pos]) {
            if (fst == 0) continue;
            if (snd + now.dis < dis[fst]) {
                dis[fst] = snd + now.dis;
                t.pos = fst; t.dis = dis[fst];
                q.push(t);
            }
        }
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, T;
signed main() {
    fast;
    n = rd(), T = rd(), s = rd(); cnt = n; build(1, 1, n);
    for (int i = 1; i <= T; ++i) {
        int op = rd();
        if (op == 1) {
            int fr = rd(), y = rd(), v = rd();
            e[fr].emplace_back(y, v);
        } else {
            if (op == 2) {
                int fr = rd(), l = rd(), r = rd(), v = rd();
                update(1, 1, n, l, r, fr, v);
            } else {
                int fr = rd(), l = rd(), r = rd(), v = rd();
                modify(1, 1, n, l, r, fr, v);
            }
        }
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        cout << (dis[i] == inf ? -1 : dis[i]) << ' ';
    return 0;
}