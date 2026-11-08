//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
邻接表存边：to 目标点、nxt 下一条边的下标（链式前向星）、w 边权。
e[N<<1]：无向边存两份（2×N 空间），head[N] 头指针，cnt 边数。
add(u,v,w)：在 u 的链头插入一条边。
Add(u,v,w)：加一条无向边（调用两次 add）。
因为这个宏在 Tree 和 Graph 两个结构体里各展开一次，各自有独立的 e、head、cnt、add、Add（图 A 是树，图 B 是原图）
f[u][j]：倍增表，u 的 2^j 级祖先。
dep[u]：深度。
dis[u]：从根到 u 的带权和（路径上边权总和）
从根（1 号）DFS：
记录父亲 f[u][0]=fa、深度 dep[u]=dep[fa]+1。
递归时累计带权距离 dis[v]=dis[u]+w。
跳过父亲防止回退
先 DFS 建树、得到所有 f[u][0] 和 dis。
再用递推 f[i][j]=f[f[i][j-1]][j-1] 填满 2 的幂级祖先（j 从 1 到 19，因为 2^19 > N）
先把较深的 u 提到与 v 同深度（按二进制位跳）。
若此时相等，则 u 就是 LCA。
否则从高到低，若 f[u][i] != f[v][i] 就一起上跳（保证跳到 LCA 的下一层）。
最后返回 f[u][0] 即 LCA。
标准公式：dis[u]+dis[v]-2*dis[lca]，即两点到根之和减去两倍 LCA 到根之和。
s：存放所有非树边的端点（不一定去重，后面用 vis 等处理）。这些点被称为"特殊点/必经候选点"。
存原图的邻接表（每个点存一份 Dijkstra 结果 dis[N]——这里 dis[S] 是一整行，即从源 S 出发到所有点的最短路数组）。注意：dis 是一个二维（N 个一维数组）‍，vl dis[N] 表示数组的数组。
vis：Dijkstra 访问标记。
q：优先队列（大根堆，靠存储负值模拟小根堆）
vl &d = dis[S]：取从源 S 出发的距离数组的引用。
初始化为 inf，d[S]=0，把 (0,S) 入队（存 0 因为是大根堆，取最小用正数最小即 0；后面入队统一存 -d[v] 来模拟小根堆——因为存负数，大根堆的堆顶就是最小的 d）。
典型 Dijkstra：取堆顶（最小距离点），若已访问跳过，否则松弛邻边。
松弛时若 d[u]+w < d[v]，更新并把 (-新距离, v) 入队
遍历所有非树边端点 s，每个都跑一次 Dijkstra，预处理出 dis[i][x] = "从特殊点 i 到任意点 x 的最短路"
带路径压缩的并查集，用于判断某条边加入是否会成环（是否已在同一连通分量）
读全部 m 条边：
先把边加进原图 G（无论是否成环）。
用并查集判断：
若 u、v 不在同一集合（不成环）→ 并查集合并，并把这一条边加入生成树 T。
若已在同一集合（会成环）→ 这条边是"非树边"，记录它的端点 u 和 v 到 s（去重用 b[]）。
读完后：
T.init()：建好树的倍增 LCA 表。
G.prep()：从所有特殊点 s 预处理最短路。
关键正确性：原图 = 生成树 T + 若干非树边。树上任意两点的最短路 ≤ 树上距离；而可能更短的路径必然要经过某条非树边，一旦经过非树边就必然经过它的某个端点。所以对每个非树边端点跑 Dijkstra，即可覆盖所有"更优"的路径
先 in() 完成读入、建树、预处理。
读 q 次查询：
初始答案 = 树上最短路 T.dist(u,v)。
对每个特殊点 i，尝试 dis[i][u] + dis[i][v]（从 i 分别到 u、v 的最短路之和，即"经过 i 中转"），取 min。
输出答案。
之所以取 min：真正的最短路要么走纯树边，要么会在某个非树边端点处路过（从而通过该点的最短路中转）。因为树已经连通所有点，Dijkstra 的 dis 也是一般图的最短路，dis[i][u]+dis[i][v] 覆盖了"经过 i 点"的所有可能
*/
#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;i++)
#define per(i,n) for(int i=n;~i;i--)
#define ll long long
#define vl vector<ll>
#define li pair<ll,int>
#define vi vector<int>
using namespace std;

constexpr int N = 1e5+5;
constexpr ll inf = 1e18;

struct edge { int to, nxt, w; } ;

#define EE; edge e[N<<1]; \
int head[N], cnt;\
void add(int u, int v, int w) {\
    e[++cnt].w = w, e[cnt].to = v, e[cnt].nxt = head[u], head[u] = cnt;\
}\
void Add(int u, int v, int w) { add(u, v, w); add(v, u, w); }\


int n;
struct Tree {
    EE;
    int f[N][20], dep[N];
    ll dis[N];
    void dfs(int u, int fa) {
        f[u][0] = fa, dep[u] = dep[fa] + 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == fa) continue;
            dis[v] = dis[u] + e[i].w;
            dfs(v, u);
        }
    }

    void init() {
        dfs(1,0);
        rep(j,19) rep(i,n) f[i][j] = f[f[i][j-1]][j-1];
    }
    int LCA(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int h = dep[u] - dep[v];
        per(i,19) if (h&(1<<i)) u = f[u][i];
        if (u == v) return u;
        per(i,19) if (f[u][i]^f[v][i]) u = f[u][i], v = f[v][i];
        return f[u][0];
    }
    ll dist(int u, int v) { return dis[u] + dis[v] - 2*dis[LCA(u,v)]; }
}T;


vi s;
struct Graph {
    EE;
    vl dis[N];
    bool vis[N];
    priority_queue<li> q;
    void dijkstra(int S) {
        vl &d = dis[S]; memset(vis,0,sizeof(vis)); d.resize(n+1);
        rep(i,n) d[i] = inf;
        d[S] = 0, q.emplace(0,S);
        while (!q.empty()) {
            auto x = q.top(); q.pop();
            int u = x.second;
            if (vis[u]) continue;
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt) {
                int v = e[i].to;
                if (d[u] + e[i].w < d[v])
                    d[v] = d[u] + e[i].w, q.emplace(-d[v],v);
            }
        }
    }
    void prep() { for (auto i : s) dijkstra(i); }
}G;

int fa[N];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
void merge(int u, int v) { fa[find(u)] = fa[find(v)]; }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

bool b[N];
void in() {
    n = rd();
    int m = rd();
    rep(i,n) fa[i] = i;
    rep(i,m) {
        int u = rd(), v = rd(), w = rd(); G.Add(u,v,w);
        if (find(u) != find(v)) merge(u,v), T.Add(u,v,w);
        else {
            if (!b[u]) s.push_back(u);
            if (!b[v]) s.push_back(v);
            b[u] = b[v] = 1;
        }
    }
    T.init(); G.prep();
}


int main() {
    in();
    int q = rd();
    while (q--) {
        int u = rd(), v = rd();
        ll ans = T.dist(u, v);
        for (int i : s) ans = min(ans, G.dis[i][u]+G.dis[i][v]);
        write(ans), putchar('\n');
    }
    return 0;
}