//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
N = 200005：点数上限
一条带权边：
v：边的另一端顶点。
a, b：边的两个权值（整型系数）。
id：边的编号。
有默认构造函数和参数构造函数。
全局数组 E[...]（下标 by id，用于点分治时记录父边）
n：树当前节点数。
adj[N<<1]：邻接表数组（N<<1 = 4e5，因为树会被扩展成更多节点）。
operator[]：方便用 F[u] 访问邻接表。
add(u,v,a,b,i)：在 u、v 间加一条带权 (a,b) 编号 i 的无向边（两边各压一次）。
定义两个实例：F（原始树）、G（变换后的新树，用于分治）
表示一条线性函数 f(X) = a*X + b，也代表一条路径的累计权值和。
重载 <：先比 a，再比 b —— 用于排序，是凸包构造的基础
把度很大的树转换为二叉树（每个节点至多 2 个「子分支」），且保留路径权值和不变。
遍历原树 F，对每个节点 u：
对它的每个非父孩子的边 e：
在 G 中新建一个内部节点 ++G.n（权值 0,0，不带原权值）；
把 lst（上一个内部节点/原节点）与新节点相连（权 0,0）；
把新节点与真正的孩子 e.v 相连，带上原边权 (e.a, e.b)；
更新 lst = 新节点，继续递归孩子。
效果：u 的多个孩子被"串联"成一条内部节点链，每个孩子各挂一个分支 — 等价于把多叉树二叉化，所有原路径上的 (a,b) 累加和仍一致
sz[u]：以 u 为根的子树大小。
no[e.id]：标记一条边是否已被删除（分治时禁用）。
get(u)：对 u 做 DFS，计算子树大小 sz，并记录每条通向孩子的边 E[e.v]（存父节点、权值、id），供 find 找重心时用
目标是找到一个子树大小 ≤ lim 的"中心"（这里是找一个点 u，其子树大小不超过 lim = sz/2）。
若当前 u 的子树已经 ≤ lim，直接返回 u。
否则在其子树中某条 find 上递归找最大的子树往下钻，直到找到一个满足条件的。
这是点分治中"找重心/切分点"的变体，用于找到一条能"对半切开"树的关键边。
从 u 出发 DFS，now 累计当前路径的 (a,b)。
当到达叶子（G[u].size()==1 即 u 只有父边那条邻接，是叶子）时，把累计的 now 压入 P。
即：把"根到所有叶子"的每条路径的 (a,b) 和收集进 P
"斜率优化 / 构造下凸包边界"函数：给定一组线性函数，筛掉永远不会成为最大值候选的（即常规的 convex hull trick 前期处理）。
排序后按 a（斜率）升序。
用双端"栈"tmp 维护凸壳：
消除同斜率中 b 较大（被支配）的项；
消除非凸点（中间点斜率被新点"包住"）。
最后只保留 top+1 个"凸包边界点"。
这保证后续合并时复杂度由参与的真实凸壳点决定
分治（点分治）的"合并"步骤，把树按一条边切开成两半，然后再分别递归。
逐步解释：

(a) get(u); if sz[u]<=1 return;

计算子树大小，若只有一个点则不必继续分。
(b) 找到要切开的"中心边"
c1 是子树大小 ≤ sz/2 的中心点（由 find 找到），E[c1] 记录了它的父边，c2 = E[c1].v 是边的另一端（父节点方向）
(c) 禁用该边，清空并分别收集两半的叶子路径
标记这条边为"已切"（分治中禁用）。
从 c1 一侧收集所有到叶子路径到 P1（含空路径 0,0），从 c2 一侧收集到 P2。
分别做凸包优化 run。
(d) 双指针合并两半路径（Minkowski / 斜率单调合并）‍
因为 P1、P2 都是斜率增大的凸包边界，用双指针单调合并（类似 Minkowski sum / 两个凸多边形的边界合并）枚举"每一种穿过切边 c1-c2 的组合路径"，每条组合路径的 (a,b) = P1某点 + P2某点 + 切边权 (E[c1].a, E[c1].b)，压入全局 P。
选择前进方向的准则：比较两边的下一段斜率 k1、k2，斜率大者推进。
这里的 P 会收集所有跨越"切边"的路径组合的 (a,b)。最终 P 就是所有可能的"好路径"的线性函数集合。
(e) 递归分治两侧
对切开的两半（c1 侧、c2 侧）递归继续分治，收集内部跨越更小切边的组合。
递归结束，所有路径组合都被加入全局 P。

读入 n 个节点、m 次查询。
读入 n-1 条带权 (a,b) 的边，建成原树 F
把原树 F 二叉化到 G（to2t(1)）。
在全局 P 中放一个空路径 (0,0)（默认基线）。
调用 solve(1) 点分治，把所有可能的路径组合 (a,b) 收进 P。
再对 P 做一次凸包优化 run(P)，去掉被支配的线性函数
Convex Hull Trick（凸包斜率优化）‍：
P 是凸包边界（a 增序、b 相应），最优解在边界上。
对每次查询 t（看作自变量 X），由于边界斜率递增，当 t*P[id+1].a + P[id+1].b > t*P[id].a+P[id].b 时，往 id+1 移动（本函数值更大）。
由于 t 从 0 递增（单调），id 单调不减 → 每个查询 O(1) 均摊，总 O(m + 凸包点数)。
结果 ans = t*P[id].a + P[id].b 即为最优答案
每个查询答案空格分隔，最后换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

struct edge {
    int v, a, b, id;
    edge() = default;
    edge(int _v, int _a, int _b, int _id) : v(_v), a(_a), b(_b), id(_id) {}
} E[N];

class Tree {
public:
    int n;
    vector<edge> adj[N<<1];
    vector<edge> &operator[](unsigned int i) { return adj[i]; }
    void add(int u, int v, int a, int b, int i) {
        adj[u].emplace_back(v, a, b, i);
        adj[v].emplace_back(u, a, b, i);
    }
} F, G;

struct Path {
    ll a, b;
    Path() = default;
    Path(ll _a, ll _b) : a(_a), b(_b) {}
    bool operator<(const Path& o) const {
        return a < o.a || (a == o.a && b < o.b);
    }
};

int eid;
void to2t(int u, int fa=0) {
    int lst = u;
    for (const auto &e : F[u]) {
        if (e.v != fa) {
            G.add(lst,++G.n,0,0,++eid);
            G.add(G.n,e.v,e.a,e.b,++eid);
            lst = G.n;
            to2t(e.v,u);
        }
    }
}

int sz[N];
bool no[N*3];
void get(int u, int fa=0) {
    sz[u] = 1;
    for (const auto &e : G[u]) {
        if (e.v != fa && !no[e.id]) {
            E[e.v] = {u,e.a,e.b,e.id};
            get(e.v,u);
            sz[u] += sz[e.v];
        }
    }
}

int find(int u, int lim, int fa=0) {
    if (sz[u] <= lim) return u;
    int mx = 0, id;
    for (const auto &e : G[u]) {
        if (e.v != fa && !no[e.id]) {
            int t = find(e.v, lim, u);
            if (sz[t] > mx) mx = sz[t], id = t;
        }
    }
    return id;
}

void getp(int u, vector<Path> &P, Path now=Path(0,0), int fa = 0) {
    if (G[u].size() == 1) P.push_back(now);
    for (const auto &e : G[u]) {
        if (e.v != fa && !no[e.id])
            getp(e.v,P,Path(now.a+e.a,now.b+e.b), u);
    }
}

void run(vector<Path> &P) {
    static vector<Path> tmp;
    sort(P.begin(),P.end());
    tmp.resize(P.size()); tmp.emplace_back(0,0);
    int top = 0;
    for (const auto &p : P) {
        while (top > 0 && (p.a == tmp[top].a && p.b >= tmp[top].b)) top--;
        if (p.a == tmp[top].a && p.b <= tmp[top].b) continue;
        while (top > 0 && 1.*(tmp[top].b-tmp[top-1].b)/(tmp[top].a-tmp[top-1].a) <
            1.*(p.b-tmp[top].b)/(p.a-tmp[top].a)) top--;
        tmp[++top] = p;
    }
    for (int i = 0; i <= top; i++) P[i] = tmp[i];
    P.resize(top+1);
}

vector<Path> P1, P2, P;
void solve(int u) {
    get(u);
    if (sz[u] <= 1) return;
    int c1 = find(u, sz[u]/2), c2 = E[c1].v;
    no[E[c1].id] = true; P1.clear(); P2.clear();
    P1.emplace_back(0,0); P2.emplace_back(0,0);
    getp(c1, P1); getp(c2, P2); run(P1); run(P2);
    int x = 0, y = 0;
    while (x < (int)P1.size() && y < (int)P2.size()) {
        P.emplace_back(P1[x].a+P2[y].a+E[c1].a, P1[x].b+P2[y].b+E[c1].b);
        double k1 = -1e100, k2 = -1e100;
        if (x < (int)P1.size()-1) k1 = 1.*(P1[x+1].b-P1[x].b)/(P1[x+1].a-P1[x].a);
        if (y < (int)P2.size()-1) k2 = 1.*(P2[y+1].b-P2[y].b)/(P2[y+1].a-P2[y].a);
        if (k1 > k2) x++; else y++;
    }
    solve(c1); solve(c2);
}

int n, m;
int main() {
    fast;
    cin >> n >> m; F.n = n;
    for (int i = 1, u, v, a, b; i < n; i++) {
        cin >> u >> v >> a >> b;
        F.add(u, v, a, b, i);
    }
    G.n = n; to2t(1); P.emplace_back(0,0); solve(1); run(P);
    int id = 0;
    for (int t = 0; t < m; t++) {
        while (id < (int)P.size()-1 && (1ll*t*P[id+1].a+P[id+1].b) >
            (1ll*t*P[id].a+P[id].b)) id++;
        ll ans = 1ll*t*P[id].a+P[id].b;
        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}