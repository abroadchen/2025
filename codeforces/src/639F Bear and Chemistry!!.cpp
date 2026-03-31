//
// Created by Psy.C on 2026/3/31.
//
/**
fr：边的起点
to：边的终点
nxt：链式前向星的下一个边索引
e[(N<<1)+5]：边数组，<<1 表示乘以2（预留空间）
nd[N+5]：节点列表
head[N+5]：邻接表头指针
esz：边的数量
vsz：节点的数量
将节点x添加到节点列表中
vsz++ 增加节点计数
nd[vsz] = x 存储节点
对节点列表进行排序和去重
unique() 函数将重复元素移到末尾并返回新末尾迭代器
添加边 (u,v) 到邻接表
使用链式前向星存储
e[++esz] = {u, v, head[u]} 创建新边
head[u] = esz 更新头指针
初始化 esz = 1（边索引从1开始，第0条边保留）
清空图结构
重置边计数和节点计数
G1：原图
G2：边双连通分量缩点后的树
G3：虚树

dfn[N+5]：DFS序
tim：时间戳
low[N+5]：Low值（最早可达祖先）
bg[(N<<1)+5]：桥标记数组
Tarjan算法找割边（桥）
dfn[x] = ++tim; low[x] = dfn[x]; 初始化节点
遍历邻接节点 y = G.e[i].to
!dfn[y]：如果y未访问，递归调用
dfn[x] < low[y]：发现桥，标记边 i 和反向边 i^1
i != (lst^1)：避免回到父边
用DFS对边双连通分量染色
bel[x] = col：标记节点属于哪个边双连通分量
!vis[y] && !bg[i]：只走非桥边
获取边双连通分量数量
初始化所有相关数组
对每个未访问节点运行Tarjan
对每个未访问节点运行DFS染色
将原图缩点为边双连通分量树
如果两端点属于不同边双连通分量，连边
out.vsz = cnt：设置新图的节点数

dfn[N+5]：DFS序
tim：时间戳
rt[N+5]：所属连通块的根
dep[N+5]：深度
anc[N+5][M+5]：倍增祖先数组
l2n：log₂(n)
DFS预处理LCA所需信息
dfn[x] = ++tim：记录DFS序
dep[x] = dep[fa] + 1：计算深度
anc[x][0] = fa：直接父亲
anc[x][i] = anc[anc[x][i-1]][i-1]：倍增预处理
计算最近公共祖先
将x调整到不低于y的深度
二分查找公共祖先
向虚树插入节点
s[N]：单调栈维护虚树路径
lc = lca(x, s[top])：计算与栈顶的LCA
弹出深度大于等于LCA的节点
连接必要的边
初始化LCA预处理
计算倍增层数 l2n
对每个连通块进行DFS
构建虚树
按DFS序排序
按连通块分组处理
使用单调栈构建虚树
检查所有查询点是否在同一个边双连通分量中


缩点得到边双连通分量树G2
记录原节点对应的边双连通分量编号
初始化LCA预处理
动态读入tn(关键点数), tm(额外边数)
处理关键点，应用加密（基于上次结果）
只在不同边双连通分量间连边
将所有涉及节点加入虚树构建点集
去重并构建虚树
在虚树上再次计算边双连通分量
检查关键点是否在同一边双连通分量
更新加密参数
清空虚树
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 5e5, M = 25;

struct grf {
    struct edge { int fr, to, nxt; } e[(N<<1)+5]{};
    int nd[N+5]{}, head[N+5]{}, esz, vsz{};
    void add(int x) { vsz++; nd[vsz] = x; }
    void uni() {
        sort(nd+1, nd+vsz+1);
        vsz = unique(nd+1, nd+vsz+1)-nd-1;
    }
    void add(int u, int v) {
        e[++esz] = {u, v, head[u]}, head[u] = esz;
    }
    grf() { esz = 1; }
    void clear() {
        esz = 1;
        for (int i = 1; i <= vsz; i++) head[nd[i]] = 0;
        vsz = 0;
    }
} G1, G2, G3;

namespace e_dcc {
    int dfn[N+5], tim, low[N+5];
    bool bg[(N<<1)+5];
    void tarjan(int x, int lst, grf& G) {
        dfn[x] = ++tim; low[x] = dfn[x];
        for (int i = G.head[x]; i; i = G.e[i].nxt) {
            int y = G.e[i].to;
            if (!dfn[y]) {
                tarjan(y, i, G);
                low[x] = min(low[x], low[y]);
                if (dfn[x] < low[y]) bg[i] = bg[i^1] = 1;
            } else if (i != (lst^1))
                low[x] = min(low[x], dfn[y]);
        }
    }
    int bel[N+5], cnt;
    bool vis[N+5];
    void dfs(int x, int col, grf& G) {
        bel[x] = col, vis[x] = 1;
        for (int i = G.head[x]; i; i = G.e[i].nxt) {
            int y = G.e[i].to;
            if (!vis[y] && !bg[i]) dfs(y, col, G);
        }
    }
    int get(grf& G) {
        for (int i = 1; i <= G.vsz; i++) {
            int u = G.nd[i];
            low[u] = dfn[u] = bel[u] = vis[u] = 0;
        }
        for (int i = 1; i <= G.esz; i++) bg[i] = 0;
        tim = 0;
        for (int i = 1; i <= G.vsz; i++)
            if (!dfn[G.nd[i]])
                tarjan(G.nd[i], 0, G);
        cnt = 0;
        for (int i = 1; i <= G.vsz; i++)
            if (!vis[G.nd[i]]) {
                cnt++;
                dfs(G.nd[i], cnt, G);
            }
        return cnt;
    }
    void g2t(grf& in, grf& out) {
        get(in);
        for (int i = 2; i <= in.esz; i++)
            if (bel[in.e[i].fr] != bel[in.e[i].to])
                out.add(bel[in.e[i].fr], bel[in.e[i].to]);
        out.vsz = cnt;
    }
}

namespace vtr {
    int dfn[N+5], tim, rt[N+5], dep[N+5], anc[N+5][M+5], l2n;
    void dfs(int x, int fa, int root, grf& T1) {
        dfn[x] = ++tim; rt[x] = root; dep[x] = dep[fa] + 1;
        anc[x][0] = fa;
        for (int i = 1; i <= l2n; i++)
            anc[x][i] = anc[anc[x][i-1]][i-1];
        for (int i = T1.head[x]; i; i = T1.e[i].nxt) {
            int y = T1.e[i].to;
            if (y != fa) dfs(y, x, root, T1);
        }
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = l2n; i >= 0; i--)
            if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
        if (x == y) return x;
        for (int i = l2n; i >= 0; i--)
            if (anc[x][i] != anc[y][i]) {
                x = anc[x][i]; y = anc[y][i];
            }
        return anc[x][0];
    }
    int top, s[N];
    void insert(int x, grf& T2) {
        if (top < 1) { s[++top] = x; return; }
        int lc = lca(x, s[top]);
        if (lc == s[top]) { s[++top] = x; return; }
        while (top > 1 && dep[s[top-1]] >= dep[lc]) {
            T2.add(s[top-1], s[top]);
            T2.add(s[top], s[top-1]);
            T2.add(s[top]); T2.add(s[top-1]);
            top--;
        }
        if (s[top] != lc) {
            T2.add(lc, s[top]); T2.add(s[top], lc);
            T2.add(lc); T2.add(s[top]);
        }
        s[top] = lc;
        s[++top] = x;
    }
    void init(grf& in) {
        l2n = log2(in.vsz)+1;
        for (int i = 1; i <= in.vsz; i++)
            if (!dep[i]) dfs(i, 0, i, in);
    }
    void get(int *in, int k, grf& out) {
        sort(in + 1, in + 1 + k, [](int x, int y) {
            return dfn[x] < dfn[y];
        });
        int r = 0;
        for (int l = 1; l <= k; l = r+1) {
            r = l;
            while (r < k && rt[in[r]] == rt[in[r+1]]) r++;
            top = 0;
            for (int i = l; i <= r; i++) insert(in[i], out);
            while (top > 1) {
                out.add(s[top-1], s[top]);
                out.add(s[top], s[top-1]);
                out.add(s[top-1]); out.add(s[top]);
                top--;
            }
            if (l == r) out.add(in[l]);
        }
    }
}

int pt[N+5];
bool check(int tn) {
    for (int i = 2; i <= tn; i++)
        if (e_dcc::bel[pt[i]] != e_dcc::bel[pt[1]])
            return false;
    return true;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m, q, ob[N+5], p[N+5];
int main() {
    rd(n); rd(m); rd(q);
    for (int i = 1; i <= n; i++) G1.add(i);
    for (int i = 1, u, v; i <= m; i++) {
        rd(u); rd(v);
        G1.add(u, v); G1.add(v, u);
    }
    e_dcc::g2t(G1, G2);
    for (int i = 1; i <= n; i++) ob[i] = e_dcc::bel[i];
    vtr::init(G2);
    for (int i = 1, rnt = 0, tn, tm, tsz; i <= q; i++) {
        rd(tn); rd(tm); tsz = 0;
        for (int j = 1; j <= tn; j++) {
            rd(pt[j]);
            pt[j] = (pt[j] + rnt) % n;
            if (pt[j] == 0) pt[j] = n;
            pt[j] = ob[pt[j]];
            p[++tsz] = pt[j];
        }
        for (int j = 1, u, v; j <= tm; j++) {
            rd(u); rd(v);
            u = (u+rnt)%n; if (u == 0) u = n;
            v = (v+rnt)%n; if (v == 0) v = n;
            if (ob[v] != ob[u]) {
                G3.add(ob[u], ob[v]);
                G3.add(ob[v], ob[u]);
                G3.add(ob[u]); G3.add(ob[v]);
            }
            p[++tsz] = ob[u]; p[++tsz] = ob[v];
        }
        sort(p + 1, p + 1 + tsz);
        tsz = unique(p + 1, p + 1 + tsz) - p - 1;
        vtr::get(p, tsz, G3); G3.uni();
        e_dcc::get(G3);
        if (tn == 1 || check(tn)) {
            printf("YES\n");
            rnt += i; rnt %= n;
        } else printf("NO\n");
        G3.clear();
    }
    return 0;
}