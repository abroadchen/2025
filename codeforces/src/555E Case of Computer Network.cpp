//
// Created by Psy.C on 2026/3/11.
//
/**
dfn: 深度优先搜索序
low: 能回溯到的最小dfn值
tot: 时间戳
st: Tarjan栈
tp: 栈顶指针
vis: 栈中访问标记
now: SCC编号计数
b: 节点所属SCC编号
遍历所有邻接点
flag: 避免立即回到父节点
DFS递归处理未访问节点
更新low值
发现强连通分量时出栈
将栈中节点分配到同一SCC

构建DFS树，计算深度和父节点
dep: 节点深度
ff[i][j]: 节点i向上跳2^j步到达的节点
使用倍增法求LCA
先将两点调整到同一深度
然后同时向上跳跃直到相遇
统计每条边被多少条路径覆盖
path[i][0]: 从下方经过的路径数
path[i][1]: 从上方经过的路径数

对每个未访问节点运行Tarjan算法
缩点：将强连通分量合并成单个节点
构建缩点后的树结构
构建DFS树并计算深度
预处理倍增数组
对每条查询路径进行差分标记
在起点和终点处标记，LCA处消除重复
统计每条边的路径覆盖情况
检查冲突条件
输出结果

Tarjan: O(n + m)
倍增预处理: O(n log n)
查询处理: O(Q log n)
总体: O(n + m + Q log n)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5;

struct node { int s, t; } q[N];

int nxt[N<<1], to[N<<1], head[N], cnt;
void add(int x, int y) {
    to[++cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
}

int dfn[N], low[N], tot, st[N], tp, vis[N], now, b[N];
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++tot;
    st[++tp] = x; vis[x] = 1;
    for (int i = head[x], flag = 1; i; i = nxt[i]) {
        if (to[i] == fa && flag) { flag = 0; continue; }
        if (!dfn[to[i]]) {
            tarjan(to[i], x);
            low[x] = min(low[x], low[to[i]]);
        }
        else if (vis[to[i]])
            low[x] = min(low[x], dfn[to[i]]);
    }
    if (dfn[x] == low[x]) {
        int id = 0; now++;
        while (id != x) {
            id = st[tp--]; b[id] = now; vis[id] = 0;
        }
    }
}

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> e[N];
int dep[N], ff[N][23];
void dfs(int x, int f) {
    for (int i = 0; i < e[x].size(); ++i)
        if (e[x][i] != f) {
            dep[e[x][i]] = dep[x] + 1;
            ff[e[x][i]][0] = x;
            dfs(e[x][i], x);
        }
}

int query(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; ~i; --i)
        if (dep[ff[x][i]] >= dep[y]) x = ff[x][i];
    if (x == y) return x;
    for (int i = 19; ~i; --i)
        if (ff[x][i] != ff[y][i])
            x = ff[x][i], y = ff[y][i];
    return ff[x][0];
}

int path[N][2], v[N];
void dfs2(int x, int f) {
    v[x] = 1;
    for (int i = 0; i < e[x].size(); ++i) {
        int t = e[x][i];
        if (t == f) continue;
        dfs2(t, x);
        path[x][0] += path[t][0]; path[x][1] += path[t][1];
    }
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
#define R(x) x=read()

int n, m, Q;
int main() {
    R(n); R(m); R(Q);
    for (int i = 1, x, y; i <= m; ++i) {
        R(x); R(y); add(x, y); add(y, x);
    }
    for (int i = 1; i <= Q; ++i) { R(q[i].s); R(q[i].t); }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i, 0);
    for (int i = 1; i <= now; ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i)
        for (int j = head[i]; j; j = nxt[j]) {
            int o1 = find(b[i]), o2 = find(b[to[j]]);
            if (o1 == o2) continue;
            e[b[i]].push_back(b[to[j]]);
            e[b[to[j]]].push_back(b[i]);
            fa[o1] = o2;
        }
    for (int i = 1; i <= now; ++i)
        if (!dep[i]) { dep[i] = 1; dfs(i, 0); }
    for (int i = 1; i <= 19; ++i)
        for (int j = 1; j <= now; ++j)
            ff[j][i] = ff[ff[j][i-1]][i-1];
    for (int i = 1; i <= Q; ++i) {
        int s = b[q[i].s], t = b[q[i].t];
        if (find(s) != find(t))
            return puts("No"), 0;
        int lca = query(s, t);
        path[s][0]++; path[lca][0]--;
        path[t][1]++; path[lca][1]--;
    }
    for (int i = 1; i <= now; ++i)
        if (!v[i]) dfs2(i, 0);
    for (int i = 1; i <= Q; ++i) {
        int s = b[q[i].s], t = b[q[i].t];
        if (s == t) continue;
        if ((path[s][0] && path[s][1]) ||
            (path[t][0] && path[t][1]))
            return puts("No"), 0;
    }
    puts("Yes");
    return 0;
}