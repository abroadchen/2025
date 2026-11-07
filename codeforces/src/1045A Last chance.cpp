//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
边数估算：E 预留了点数、查询边、线段树双向边、反向边等，e[E<<1] 存正向+反向。
add 存边，tot 从 1 开始（这样 e[i^1] 正好是反向边
树的 线段树节点：o（1 - N<<2）。
"物品/需求"节点：get(x)=x+4*m，即每个查询/物品有自己的点。
源 S=0，汇 T=n+4*m+1
整棵树表示区间 [1,m]（m 个时间片/timeslot）‍。
叶子 (o == 叶子)：连 叶子 → T 容量 1 → 每个时间片只被用 1 次。
内部节点：o → 左子 inf、o → 右子 inf → 通过 inf 边，父节点可"下放"流量到其任意后代叶子。
这就是"线段树优化建图"的精髓：把对区间 [l,r] 的连边，拆成 O(log m) 个线段树节点，而不是 O(m) 个叶子，从而减少边数
从"需求点 fr"向覆盖区间 [ql,qr] 的若干线段树节点连容量 1 的边，实现 fr → 区间内所有时间片的边。
找到代表单个时间片 q 的那个叶子节点编号
标准 BFS 分层，cur[] 为当前弧优化
递归增广，e[i^1] 处理反向边，i^1 依赖 tot 从 1 起、正反成对。
循环 BFS + DFS 直到流量为 0，返回最大流 = 最大匹配数。
op==0：该需求可选的单个时间片集合（k 个选择），源容量 1。
op==1：该需求可选的一段连续区间 [l,r]，源容量 1。
op==2：给定 3 个特定时间片，三选二，源容量 2（必须流出 2 单位），并额外记录。
目标：在 每个时间片只能用 1 次（叶子→T 容量1）的前提下，最大化完成的匹配数

从汇 T 出发，沿残留网络中仍有容量的正向边逆向回溯，找到达到的"需求节点"，从而还原每条选择路径。
之后输出 ans[i]（每个时间片分配给哪个需求）。
输出最大匹配值，然后还原并打印每条"需求-时间片"的分配。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 5005, M = (N<<2)+N, K = 1e5+5, E = N+K+N*14+4*N*2+N, inf = 0x3f3f3f3f;

struct edge { int y, nxt, w; } e[E<<1];

int tot(1), head[M];
inline void add(int x, int y, int w) {
    e[++tot] = {y, head[x], w}; head[x] = tot;
}

int m;
inline int get(int x) { return x+4*m; }

int T, id[N<<2];
struct sgt {
#define ls o<<1
#define rs (o<<1|1)
    int L[N<<2], R[N<<2];
    void build(int o, int l, int r) {
        L[o] = l; R[o] = r;
        if (l == r) {
            add(o,T,1); add(T, o, 0);
            id[o] = l;
            return;
        }
        build(ls, l, mid); build(rs, mid+1, r);
        add(o, ls, inf); add(ls, o, 0);
        add(o, rs, inf); add(rs, o, 0);
    }
    void ad(int o, int ql, int qr, int fr) {
        if (ql <= L[o] && R[o] <= qr) { add(fr,o,1); add(o,fr,0); return; }
        int md = (L[o] + R[o]) >> 1;
        if (ql <= md) ad(ls, ql, qr, fr);
        if (qr > md) ad(rs, ql, qr, fr);
    }
    int find(int o, int q) {
        if (L[o] == R[o]) return o;
        int md = (L[o] + R[o]) >> 1;
        if (q <= md) return find(ls, q);
        return find(rs, q);
    }
} tr;

int S, d[M], cur[M];
inline bool bfs() {
    queue<int> q; q.push(S); memset(d, -1, sizeof(d)); d[S] = 1; cur[S] = head[S];
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].y;
            if (d[y] == -1 && e[i].w) {
                d[y] = d[x] + 1; cur[y] = head[y];
                if (y == T) return 1;
                q.push(y);
            }
        }
    }
    return 0;
}

int find(int x, int lim) {
    if (x == T) return lim;
    int flow = 0;
    for (int i = cur[x]; i && flow < lim; i = e[i].nxt) {
        int y = e[i].y; cur[x] = i;
        if (d[y] == d[x] + 1 && e[i].w) {
            int t = find(y, min(e[i].w, lim-flow));
            if (!t) d[y] = -1;
            e[i].w -= t; e[i^1].w += t; flow += t;
        }
    }
    return flow;
}

inline int dinic() {
    int r = 0, flow;
    while (bfs()) while ((flow=find(S,inf)) > 0) r += flow;
    return r;
}

int n;
void scheme(int now, int &s) {
    if (s) return;
    if (4*m+1 <= now && now <= 4*m+n) {
        s = now - 4*m;
        return;
    }
    for (int i = head[now]; i; i = e[i].nxt) {
        int y = e[i].y;
        if ((i&1) && e[i].w) {
            scheme(y, s);
            --e[i].w;
            return;
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

bool isnd[N];
int sp[N][3], ans[N], cnt[N];
int main() {
    fast;
    n = rd(), m = rd(); S = 0; T = n+4*m+1; tr.build(1,1,m);
    rep(i,n) {
        int op = rd();
        if (op == 0) {
            int k = rd();
            while (k--) {
                int x = rd();
                add(get(i), tr.find(1,x), 1);
                add(tr.find(1,x), get(i), 0);
            }
            add(S,get(i),1); add(get(i), S, 0);
        } else if (op == 1) {
            int l = rd(), r = rd();
            tr.ad(1,l,r,get(i));
            add(S,get(i),1); add(get(i),S,0);
        } else if (op == 2) {
            int a = rd(), b = rd(), c = rd();
            add(get(i),tr.find(1,a),1); add(tr.find(1,a),get(i),0);
            add(get(i),tr.find(1,b),1); add(tr.find(1,b),get(i),0);
            add(get(i),tr.find(1,c),1); add(tr.find(1,c),get(i),0);
            add(S,get(i),2); add(get(i),S, 0);
            isnd[i] = 1; sp[i][0] = a; sp[i][1] = b; sp[i][2] = c;
        }
    }
    int tmp = dinic();
    cout << tmp << '\n';
    for (int i = head[T]; i; i = e[i].nxt) {
        int y = e[i].y;
        if (e[i].w) scheme(y, ans[id[y]]);
    }
    rep(i,m) ++cnt[ans[i]];
    rep(i,n) if (cnt[i] == 1 && isnd[i]) {
        if (ans[sp[i][0]] != i) ans[sp[i][0]] = i;
        else ans[sp[i][1]] = i;
    }
    rep(i,m) if (ans[i]) cout << ans[i] << ' ' << i << '\n';
    return 0;
}