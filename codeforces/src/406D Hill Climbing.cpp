//
// Created by Psy.C on 2026/2/1.
//
/**
* Edge：边结构体（邻接点和下一节点指针）
E[M]：边池
H[N]：头节点数组
edge：边池指针
*siz[N]：子树大小
pt：栈指针
son[N]：重儿子
pre[N]：父节点
top[N]：链顶节点
 *
*S[pt-1] - p[i] 的含义
S[pt-1]：栈中倒数第一个点
p[i]：当前正在处理的点
S[pt-1] - p[i]：从p[i]指向S[pt-1]的向量
S[pt-2] - p[i] 的含义
S[pt-2]：栈中倒数第二个点
S[pt-2] - p[i]：从p[i]指向S[pt-2]的向量
 *
*从p[i] → S[pt-1] 再到 p[i] → S[pt-2] 形成了逆时针转向
当前的S[pt-1]点破坏了凸包的性质
需要弹出S[pt-1]来维持凸包的凸性
 *
*由于是从后往前构造凸包并建图
节点n很可能成为树的根（没有出边的节点）
 *
 *
*预处理：O(n) - 凸包构造 + 树链剖分
单次查询：O(log n) - LCA查询
总体：O(n + q log n)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define M 200005
using namespace std;

struct Edge {
    int v;
    Edge *nxt;
} E[M], *H[N], *edge;

struct Point {
    ll x{}, y{};//坐标和索引
    int idx{};
    Point() = default;
    Point(const ll x, const ll y) : x(x), y(y) {}
    Point operator-(const Point &o) const {
        return {x - o.x, y - o.y};
    }
    void input(const int p) { cin >> x >> y; idx = p; }
} p[N], S[N];

int siz[N], pt, son[N], pre[N], top[N];
void clear() {
    edge = E; siz[0] = 0; pt = 0;
    memset(H, 0, sizeof H);
    memset(son, 0, sizeof son);
    memset(pre, 0, sizeof pre);
    memset(top, 0, sizeof top);
}

void add(const int u, const int v) {
    edge->v = v; edge->nxt = H[u]; H[u] = edge++;
}

int dep[N];
void dfs(const int u) {
    siz[u] = 1; son[u] = 0;
    for (auto e = H[u]; e; e = e->nxt) {
        const int v = e->v;
        if (v == pre[u]) continue;
        pre[v] = u;
        dep[v] = dep[u] + 1;//设置深度和父节点
        dfs(v);//计算子树大小
        if (siz[v] > siz[son[u]]) son[u] = v;//找出重儿子
    }
}

void dfs2(const int u, const int t) {
    top[u] = t;//设置链顶节点
    if (son[u]) dfs2(son[u], t);//先处理重儿子，再处理轻儿子
    for (auto e = H[u]; e; e = e->nxt) {
        if (const int v = e->v; v != son[u] && v != pre[u])
            dfs2(v, v);
    }
}

int query(int x, int y) {
    while (top[x] != top[y]) {//在不同链上跳跃直到同一条链
        if (dep[top[x]] > dep[top[y]]) x = pre[top[x]];
        else y = pre[top[y]];
    }
    if (dep[x] < dep[y]) return x;//返回深度较小的节点（LCA）
    return y;
}

int cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x > 0;
}

int n, q;
void f() {
    clear();
    for (int i = 1; i <= n; ++i) p[i].input(i);
    for (int i = n; i >= 1; --i) {//逆序处理点
        while (pt > 1 && cross(S[pt-1] - p[i], S[pt-2] - p[i])) --pt;
        S[pt++] = p[i];//将当前点入栈
        if (pt > 1) add(S[pt-2].idx, S[pt-1].idx);//凸包上的相邻点连边
    }
    dfs(n);
    dfs2(n, n);
    cin >> q;
    int x, y;
    while (q--) {
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
}



int main() {
    fast;
    cin >> n; f();
    return 0;
}