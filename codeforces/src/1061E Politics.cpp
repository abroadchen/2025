//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
Flow 类：最小费用最大流（SPFA + 增广路，最小费用）。
Tree 类：两棵树的 DFS 处理，把树上节点值向祖先"传递/归并"
网络流节点数约 N<<1（1000 左右），边数 M<<1。
S、T 为源点汇点。
add(x,y,v,f)：加一条从 x 到 y、单位费用 v、容量 f 的边；Add 是加带反向边（反向边费用取负、容量 0）
队列 SPFA 求从 S 到各点最短路（以费用为边权）‍，dis[to] < dis[x]+val 松弛。
fr[to]=i 记录前驱边，用于回溯增广路。
返回是否还能找到增广路（fr[T]!=-1）
从 fr[T] 回溯增广路径，x = min(flow) 求路径上的最小残余容量。
mx += x 累加总流量；mn += val*x 累加总费用；沿路扣减正向流量、增加反向流量
输出 -mn，说明最后答案取负——即建图时用的是"负费用"技巧：把想最大化的东西改建成最小费用流（取负号）
q[x] 表示节点 x 的权值/流量值。
从根开始：如果当前节点有值（q[x] 非零）且不是根，就把它的值累加/上交给祖先 lst（q[lst] -= q[x]），并记录 f[x]=x（自己作为一段的"代表"）。
否则 f[x]=lst（继承祖先代表）。
f[x] 的含义：把树按"有值的节点"划分成段，f[x] 是节点 x 所在段最终归属的代表节点。
check()：检查所有 q[i] >= 0（若某祖先被"扣成负值"则无解）
两棵树结构相同（各 n 节点），根分别为 r1、r2。
a[i]：每个点在网络里对应一个费用（这里取负，即收益）
两棵树根节点值必须相等
两棵树分别把叶子/子节点的值归并到代表节点。
源 S → 第一棵树各代表（容量 = 树1 该段流量）。
第二棵树各代表 → 汇 T（容量 = 树2 该段流量）。
树1代表 → 树2代表 +n，容量 1，费用 = -a[i]（最大化 a 的收益，用负号转为最小费用）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= (n); ++i)
#define ll long long
using namespace std;

constexpr int N = 510, B = 1010,  M = B*B, inf = 0x3f;

struct Flow {
    struct node { int fr, to, nxt, val, flow; } e[M<<1];
    int S, T, head[N<<1], cnt, vis[N<<1], fr[N<<1];
    ll dis[N<<1], mx, mn;
    queue<int> q;
    void init(int s, int t) {
        S = s, T = t;
        memset(head, -1, sizeof(head));
        mx = mn = 0;
    }
    void add(int x, int y, int v, int f) {
        e[cnt] = {x,y,head[x], v, f}; head[x] = cnt++;
    }
    void Add(int x, int y, int v, int f) {
        add(x,y,v,f); add(y,x,-v,0);
    }
    int spfa() {
        memset(vis, 0, sizeof(vis));
        memset(dis, inf, sizeof(dis));
        dis[S] = 0; q.push(S); vis[S] = 1; fr[S] = fr[T] = -1;
        while(!q.empty()) {
            int x = q.front(); q.pop(); vis[x] = 0;
            for (int i = head[x]; ~i; i = e[i].nxt) {
                int to = e[i].to;
                if (e[i].flow > 0 && dis[to] > dis[x] + e[i].val) {
                    dis[to] = dis[x] + e[i].val; fr[to] = i;
                    if (!vis[to]) q.push(to), vis[to] = 1;
                }
            }
        }
        return fr[T] != -1;
    }
    void mcmf() {
        int i = fr[T], x;
        memset(&x, inf, sizeof(x));
        while (i != -1) x = min(x, e[i].flow), i = fr[e[i].fr];
        i = fr[T]; mx += x;
        while (i != -1) {
            mn += e[i].val*x;
            e[i].flow -= x; e[i^1].flow += x;
            i = fr[e[i].fr];
        }
    }
    void run() { while (spfa()) mcmf(); }
    void out() const { cout << -mn << '\n'; }
} G;

struct Tree {
    struct node { int to, nxt; } e[N<<1];
    int head[N], cnt, q[N], f[N];
    void init() { memset(head, -1, sizeof(head)); }
    void add(int x, int y) { e[cnt] = {y, head[x]}; head[x] = cnt++; }
    void dfs(int x, int fr, int lst) {
        if (fr && q[x]) q[lst] -= q[x], f[x] = lst = x; else f[x] = lst;
        for (int i = head[x]; ~i; i = e[i].nxt) {
            int to = e[i].to;
            if (to != fr) dfs(to, x, lst);
        }
    }
    bool check(int n) {
        for (int i = 1; i <= n; ++i)
            if (q[i] < 0) return 0;
        return 1;
    }
} t[2];

int a[B], n, i, x, y, k, r1, r2, q, sum;
int main() {
    fast;
    G.init(0, 1001); t[0].init(), t[1].init();
    cin >> n >> r1 >> r2;//n 节点数，r1/r2 两棵树的根
    rep(i,n) cin >> a[i];//a 节点价格/收益
    rep(i,n-1) cin >> x >> y, t[0].add(x, y), t[0].add(y, x);
    rep(i,n-1) cin >> x >> y, t[1].add(x, y), t[1].add(y, x);
    cin >> q;
    rep(i,q) cin >> x >> k, t[0].q[x] = k;
    cin >> q;
    rep(i,q) cin >> x >> k, t[1].q[x] = k;
    if (t[0].q[r1] != t[1].q[r2]) return cout << "-1\n", 0;//两棵树根节点值必须相等
    sum = t[0].q[r1];
    t[0].dfs(r1, 0, r1); t[1].dfs(r2, 0, r2);
    if (!t[0].check(n) || !t[1].check(n)) return cout << "-1\n", 0;
    rep(i,n) {
        G.Add(t[0].f[i], t[1].f[i]+n, -a[i], 1);//主边：树1代表→树2代表+n，费用 -a[i]，容量1
        G.Add(G.S, i, 0, t[0].q[i]);//源→树1节点，费用0，容量=树1该节点流量
        G.Add(i+n, G.T, 0, t[1].q[i]);//树2节点→汇，费用0，容量=树2该节点流量
    }
    G.run();
    if (G.mx != sum) return cout << "-1\n", 0;
    G.out();
    return 0;
}