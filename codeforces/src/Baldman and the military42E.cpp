//
// Created by Psy.C on 2025/9/25.
//
/*
*n: 节点数，m: 边数
tot: 剩余需要连接的边数（初始为n-1）
r[N]: 并查集的秩
fa[N]: 并查集的父节点
w[N]: 边权重
cnt: 边计数器
head[N]: 链式前向星的头指针
dep[N]: 节点深度
sum: 总权重
Node: 边结构体，包含起点、终点、权重，按权重排序
Edge: 链式前向星的边结构体
 *
*find: 并查集查找函数（路径压缩）
add: 添加无向边（链式前向星）
dfs: 深度优先搜索，计算节点深度
 *
*读入节点数n和边数m
读入所有边信息
按权重对边进行排序
初始化：tot=n-1（需要n-1条边构成树），并查集秩都为1
 *
*Kruskal算法构建最小生成树：
对每条边，检查两端点是否在同一连通分量
如果不在同一连通分量，则合并
记录边权重，构建树结构
当tot减到0时停止（已构成完整的生成树）
 *
 *如果成功构建了生成树，则进行DFS计算各节点深度
 *如果图不连通（tot>1）或两点在同一连通分量但图未完全连通，则输出-1
 *如果图连通但两点在不同连通分量，则输出总权重
 *
*计算两点间路径上的最大边权：
先让深度较深的节点上移到同一深度
然后同时向上移动直到相遇
记录路径上的最大边权
输出总权重减去最大边权

如果图不连通，输出-1
如果两点不连通但图连通，输出MST权重
如果两点连通，计算最小生成树中两点路径上的最大边，并输出MST权重减去该最大边的值（即次小生成树权重）
这是经典的次小生成树(Second Minimum Spanning Tree)问题

 */
#include <algorithm>
#include <cstdio>
#define rep(i,a,b) for(int i=int(a), I=(b);i<=I;++i)
using namespace std;
typedef long long ll;
const int N = 100000+10;
//快速读取整数函数，支持负数
inline int read() {
    int x(0), c = getchar(), f(0);
    for (; c > '9' || c < '0'; f = c == '-', c = getchar());
    for (; c >= '0' && c <= '9'; x = (x << 1) + (x << 3) + c - '0', c = getchar());
    return f ? -x : x;
}


int n, m, tot, r[N], fa[N], w[N], cnt, head[N], dep[N];
ll sum;

struct Node {
    int x, y, z;
    bool operator<(const Node& b) const { return z < b.z; }
} E[N<<1];

struct Edge { int to, nxt; } e[N<<1];

int find(int x) { return fa[x] ? find(fa[x]) : x; }

void add(int u, int v) {
    e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
    e[++cnt] = (Edge){u, head[v]}; head[v] = cnt;
}

void dfs(int u) {
    for (int i = head[u], v; i; i = e[i].nxt) {
        if ((v = e[i].to) != fa[u])
            dep[v] = dep[u] + 1, dfs(v);
    }
}
//快速输出长整数函数，递归处理多位数
inline void write(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 10) write(x/10);
    putchar(x % 10 + 48);
}

int main() {

    n = read(), m = read();
    rep (i, 1, m) E[i] = (Node){read(), read(), read()};
    sort(E + 1, E+m+1);
    tot = n - 1;
    rep (i, 1, n) r[i] = 1;
    rep (i, 1, m) {
        int x = find(E[i].x), y = find(E[i].y);
        if (x != y) {
            if (r[x] > r[y]) swap(x, y);
            fa[x] = y; r[y]++; w[x] = E[i].z;
            add(x, y);
            sum += w[x];
            if (--tot == 0) break;
        }
    }
    if (!tot) dfs(find(1));

    for (int i = read(); i--;) {
        int x = read(), y = read();
        if (tot > 1 || (tot == 1 && find(x) == find(y))) {
            puts("-1");
            continue;
        }
        if (tot == 1 && find(x) != find(y)) {
            write(sum);
            puts("");
            continue;
        }
        int l(0);
        if (dep[x] < dep[y]) swap(x, y);
        for (int j = dep[x] - dep[y]; j; --j, x = fa[x])
            l = max(l, w[x]);
        for (; x != y; x = fa[x], y = fa[y])
            l = max(l, max(w[x], w[y]));
        write(sum - l);
        puts("");
    }
    return 0;
}