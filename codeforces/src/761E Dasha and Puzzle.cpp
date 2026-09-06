//
// Created by Psy.C on 2026/9/5.
//
/**
度数检查：首先确保树中没有节点的连接边数超过 4，否则无法在二维平面上以四个方向展开。
深度优先搜索 (DFS)：从根节点出发，递归地为每个子节点分配坐标。
指数级缩放：利用位运算 (1 << tag) 动态计算距离，使得不同层级的节点之间的间距呈指数级递减，防止重叠。
方向控制：通过 pos 数组和 fr 参数，精确控制子树展开的方向，避免交叉
u：当前处理的节点编号。
f：父节点编号（用于跳过回边）。
x, y：当前节点的坐标。
tag：层级标记，用于计算距离 1 << tag（即
2
tag
2
tag
 ）。
fr：跳过特定方向的索引，防止子树冲突

tot 表示当前遍历到的是第几个子节点。fr 是一个特殊的“禁用”方向索引。如果当前子节点的序号恰好等于 fr，则直接跳过这个方向（tot++），
改为使用下一个方向。这是为了让同一个父节点的不同子树尽量分散开来，避免相互挤压
位移量：(1 << tag)。随着递归深入，tag 会减小，导致位移量呈指数级递减（例如 2^30, 2^29, ...）。这样可以保证根部之间的间距很大，而叶子节点之间的间距很小，防止重叠。
方向：pos[tot][0] 和 pos[tot][1] 决定了具体往哪个方向移动（右、上、左、下）。
层级下降：tag-1 表示进入下一层，距离缩小一半。
更新禁用方向：(tot+2)%4 通常是当前方向的反方向。例如，如果当前方向是右 (0)，那么 (0+2)%4 = 2 对应左。这意味着下一个子树会优先避开当前方向的反方向，从而均匀分布
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 55;
struct edge { int to, nxt; } e[N<<1];

int cnt, head[N];
inline void add(int u, int v) {
    e[++cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int ax[N], ay[N], pos[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
inline void dfs(int u, int f, int x, int y, int tag, int fr) {
    int tot = 0;
    ax[u] = x, ay[u] = y;//置当前节点坐标
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == f) continue;
        if (tot == fr) tot++;//跳过特定方向
        dfs(v, u, x+(1<<tag)*pos[tot][0], y+(1<<tag)*pos[tot][1], tag-1, (tot+2)%4);
        tot++;
    }
}

int n, du[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
        du[u]++; du[v]++;
        if (du[u] > 4 || du[v] > 4) { cout << "NO"; return 0; }
    }
    dfs(1, 0, 0, 0, 30, -1);
    cout << "YES\n";
    for (int i = 1; i <= n; ++i)
        cout << ax[i] << ' ' << ay[i] << '\n';
    return 0;
}