//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
N=222、M=166666、B=444 是数组上限（点数≤222，边数上限）。
pt 提供向量运算；inf 用作超大流量。
把点集从最小的点（按 x 再按 y 排序的最小值）开始重排，让两个凸包的起点对齐，便于闵可夫斯基和。
Minkowski 和 A⊕B = {a+b | a∈A,b∈B} 的结果仍是凸多边形。这里对两个凸包的边按极角合并（叉积比较方向），依次拼接，得到和凸包的边。后面用于"圆与圆、圆与边界"的碰撞判定
"以点 a 为圆心、半径 r 的圆，是否与凸包 q 相交"的判定：

若圆一定不越过边界（点到每边距离都 ≥ r 且在内部方向），返回 ok（等于 1 表示圆在凸包内部且不相交? 需结合调用处理解）。
任何"圆心到边距离 < r"或"圆心落在边上/内部且圆与边相交"都返回 1（相交）。
调用处用它判断两圆相对原点的"和凸包"是否有重叠，从而决定两个圆之间是否需要连边（若圆 i 与圆 j 在路径上"相接/重叠"则加割边）。
邻接表存边 + 反向边（用于增广），add 加有向边及其残量反向边
Dinic 算法：BFS 建层级、DFS 推送流量，dis 为层级、e[i^1] 是反向边。
a = mincowski(a, b) 得到的是据点集与其自己的差集（对称差）的凸包，几何上为"以原点为中心、代表所有据点之间位移"的凸包。用它来判断"两点/两圆之间的位移方向是否会被/不会被圆阻挡"。

拆点连边（圆内部容量=1）
拆点是把"删除这个圆"建模成割掉那条容量为 1 的边，这就是"删掉最少的圆"的代价！
圆触及（靠近）边界时，从源/汇连 inf 边：任何从左到右的路径若要穿过去，必须经过这个圆，若不删它就会连通两侧。
圆之间按几何关系连边
check(c[i].o-c[j].o, c[i].r+c[j].r, a)：判断"圆心位移向量 + 两圆半径和"的圆是否与原点的据点差凸包 a 相交。
若相交，说明在只剩这两个"未被删的圆"的残余结构里，圆 i 与圆 j 在位移意义下会"相接"——于是它们之间建立 inf 容量边，构成通路。两条边分别表示 i→j 和 j→i（双向），容量 inf 表示"不能依靠割这个边来断流"，只能靠拆点（删除圆）断流。
这样形成一个流网络，源是"能到达左边界（穿通起点）的圆"，汇是"能到达右边界的圆"，中间按几何衔接。最小割 = 最少需要删除的圆，使左侧与右侧彻底不连通，即阻断从左到右的路径
跑 Dinic 求 S→T 最大流 = 最小割数值，即最少需要炸毁/移除的圆数，输出
*/
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; i++)
#define int long long
using namespace std;

constexpr int inf = 1ll<<30, N = 222, M = 166666, B = 444;

struct pt {
    int x, y;
    pt(int x=0, int y=0) : x(x), y(y) {}
    pt operator+(const pt &o) const { return {x+o.x, y+o.y}; }
    pt operator-(const pt &o) const { return {x-o.x, y-o.y}; }
    int dot(const pt &o) const { return 1ll*x*o.x+1ll*y*o.y; }
    int det(const pt &o) const { return 1ll*x*o.y-1ll*y*o.x; }
    int operator<(const pt &o) const { return x == o.x ? y < o.y : x < o.x; }
    int abs2() { return 1ll*x*x+y*y; }
};

struct node { pt o; int r; };

inline vector<pt> init(vector<pt> a) {
    vector<pt> t;
    int p = min_element(a.begin(), a.end()) - a.begin();
    rep(i,0,a.size()-1) t.emplace_back(a[(i+p)%a.size()]);
    return t;
}
inline vector<pt> mincowski(vector<pt> a, vector<pt> b) {
    a = init(a); b = init(b);
    vector<pt> t, A(a.size()), B(b.size());
    rep(i,0,a.size()-1) A[i] = a[(i+1)%a.size()] - a[i];//边的方向向量
    rep(i,0,b.size()-1) B[i] = b[(i+1)%b.size()] - b[i];
    int i = 0, j = 0; t.emplace_back(a[0]+b[0]);
    while (i < a.size() || j < b.size()) {//合并两个凸包的边
        if (i == a.size()) t.emplace_back(t.back()+B[j]), ++j;
        else if (j == b.size()) t.emplace_back(t.back()+A[i]), ++i;
        else if (A[i].det(B[j]) >= 0) t.emplace_back(t.back()+A[i]), ++i;
        else t.emplace_back(t.back()+B[j]), ++j;
    }
    return t;
}

inline int check_onseg(pt p, pt x, pt y) {//p 在 x-y 线段上
    return (p-x).det(p-y) == 0 && (p-x).dot(p-y) <= 0;
}
inline int check(pt a, int r, vector<pt> q) {
    for (auto b : q) if ((a-b).abs2() < r*r) return 1;//圆心在凸包 q 内部或边上 → 相交
    int ok = 1;
    rep(i,0,q.size()-1) {
        pt x = q[i], y = q[(i+1)%q.size()];
        if (check_onseg(a,x,y)) return 1;
        if ((a-x).dot(y-x) > 0 && (a-y).dot(x-y) > 0) {//圆心在线段的"外侧"（正投影在段上）且距离小于 r → 段与圆相交
            int t = (a-x).det(y-x);
            if (t*t < r*r*(y-x).abs2()) return 1;//点到线段距离 < r
        }
        ok &= (a-x).det(y-x) <= 0;//检查圆心是否在凸包同侧
    }
    return ok;//圆心在凸包内部(不含边)且圆完全包含在凸包? 或安全
}

struct edge { int to, nxt, f; } e[M];

int head[B], cnt(1);
inline void add(int u, int v, int d) {
    e[++cnt] = {v, head[u], d}; head[u] = cnt;
    e[++cnt] = {u, head[v], 0}; head[v] = cnt;
}

int dis[B], q[B], S, T;
int bfs() {
    memset(dis, -1, sizeof dis);
    int h = 0, t = 1; q[1] = S; dis[S] = 0;
    while (h != t) {
        int u = q[++h];
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[v] == -1 && e[i].f) {
                dis[v] = dis[u] + 1;
                if (v == T) return 1;
                q[++t] = v;
            }
        }
    }
    return 0;
}

int dfs(int u, int flow) {
    if (u == T) return flow;
    int del = flow;
    for (int i = head[u]; i && del; i = e[i].nxt) {
        int v = e[i].to;
        if (dis[v] == dis[u] + 1 && e[i].f) {
            int k = dfs(v, min(e[i].f, del));
            e[i].f -= k; e[i^1].f += k; del -= k;
        }
    }
    if (del) dis[u] = -1;
    return flow - del;
}

int n, w, lb, rb, m, id[N][2], tim;
vector<pt> a, b;
vector<node> c;
signed main() {
    cin >> n >> w; lb = M, rb = -M; a.resize(n); b.resize(n);
    rep(i,0,n-1) {
        int x, y; cin >> x >> y; a[i] = {x,y}; b[i] = {-x,-y};
        lb = min(lb,x), rb = max(rb,x);
    }
    cin >> m;
    rep(i,1,m) id[i][0] = ++tim, id[i][1] = ++tim; S = ++tim; T = ++tim; c.resize(m+1);
    rep(i,1,m) cin >> c[i].o.x >> c[i].o.y >> c[i].r; a = mincowski(a,b);
    rep(i,1,m) {
        add(id[i][0], id[i][1], 1);//拆点：入→出，容量 1（删掉这个圆代价 1）
        if (rb-lb > c[i].o.x-c[i].r) add(S, id[i][0], inf);//圆触及左边界 → 连源
        if (rb-lb > w-c[i].o.x-c[i].r) add(id[i][1], T, inf);//圆触及右边界 → 连汇
    }
    rep(i,1,m) rep(j,i+1,m) if (check(c[i].o-c[j].o, c[i].r+c[j].r, a)) {
        add(id[j][1], id[i][0], inf);
        add(id[i][1], id[j][0], inf);
    }
    int ans = 0;
    while (bfs()) ans += dfs(S, inf);
    cout << ans << '\n';
    return 0;
}