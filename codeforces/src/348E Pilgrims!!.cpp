//
// Created by Psy.C on 2026/1/14.
//
/**
 * to存储邻接点，ew存储边权，nxt用于链式前向星
 *head[u]指向节点u的第一条边
 *
*f[x]: x的父亲节点
sz[x]: x的子树大小
dep[x]: x的深度
son[x]: x的重儿子（子树最大的儿子）
dfs函数计算这些基础信息
*top[x]: x所在重链的顶部节点
dfs2将树分割成重链，为LCA查询做准备
*ini()初始化LCA预处理
lca函数找到x和y的最近公共祖先
 *
*dfn[x]: x的DFS序号
dfn2[i]: DFS序为i的节点
F[x]: x的父节点
sz[x]: x子树中特殊点数量
f[x][0-2]: 从x出发的最长、次长、第三长路径长度
g[x][0-2]: 对应路径经过的子节点
p[x]: 记录最长路径的实际起点 确定LCA（最近公共祖先）的位置
 *
 *
 *
*to[]: 存储边的目标节点
cnt: 边的计数器，用于标识每条边
nxt[]: 链式前向星中的下一个边的索引
head[]: 每个节点的第一条边的索引
ew[]: 存储边的权重
*++cnt: 先自增cnt，然后使用新的值
to[++cnt] = v: 新边的终点是v
ew[cnt] = w: 新边的权重是w
nxt[cnt] = head[u]: 新边指向原来u的首条边
head[u] = cnt: u的首条边更新为新边
 *
*x: 当前节点
fa: 父节点
d: 当前深度
 *
*dfn[x] = ++tot: 为x分配DFS序号并递增计数器
dfn2[dfn[x]] = x: 保存DFS序到节点的映射
dfn2[dfn[x] = ++tot] = x: 三步连续执行
 *
*if (v == g[x][0]) {           // 如果v是x的最长路径方向的子节点
    a = f[x][1];              // a取次长路径长度
    bb = f[x][2];             // bb取第三长路径长度
} else if (v == g[x][1]) {    // 如果v是x的次长路径方向的子节点
    a = f[x][0];              // a取最长路径长度
    bb = f[x][2];             // bb取第三长路径长度
} else {                      // 如果v既不是最长也不是次长路径方向
    a = f[x][0];              // a取最长路径长度
    bb = f[x][1];             // bb取次长路径长度
}
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int to[N<<1], cnt, nxt[N<<1], head[N], ew[N<<1];
void add(const int u, const int v, const int w) {
    to[++cnt] = v, ew[cnt] = w, nxt[cnt] = head[u], head[u] = cnt;
}

namespace LCA {
    int top[N], son[N], dep[N], sz[N], f[N];
    void dfs(const int x, const int fa, const int d) {
        f[x] = fa; sz[x] = 1; dep[x] = d;
        for (int i = head[x]; i; i = nxt[i]) {
            if (const int v = to[i]; v != fa) {
                dfs(v, x, d + 1);//递归处理子节点
                sz[x] += sz[v];//累加子树大小
                if (sz[v] > sz[son[x]]) son[x] = v;//更新重儿子
            }
        }
    }
    void dfs2(const int x, const int t) {//t: 当前重链的顶端节点
        top[x] = t;
        if (!son[x]) return;//没有重儿子，返回（叶子节点）
        dfs2(son[x], t);// 优先处理重儿子，延续当前重链
        for (int i = head[x]; i; i = nxt[i]) {//遍历轻儿子（非重儿子且非父节点的邻居）
            if (const int v = to[i]; v != son[x] && v != f[x]) dfs2(v, v);//为轻儿子创建新的重链
        }
    }
    void ini() { dfs(1, 0, 1), dfs2(1, 1); }
    int lca(int x, int y) {
        //x和y不在同一条重链时继续 深度大的节点向上跳到链顶的父节点
        while (top[x] ^ top[y]) dep[top[x]] < dep[top[y]] ? y = f[top[y]] : x = f[top[x]];
        return dep[x] < dep[y] ? x : y;// 返回深度浅的节点（LCA）
    }
}

int dfn[N], dfn2[N], tot, F[N], sz[N], f[N][3], g[N][3], p[N];
bool b[N];//标记节点x是否为特殊点
void dfs(const int x, const int fa) {
    dfn2[dfn[x] = ++tot] = x;//DFS序编号
    F[x] = fa;
    sz[x] = b[x];//以x为根的子树中特殊点数量
    for (int i = head[x]; i; i = nxt[i]) {
        if (const int v = to[i]; v != fa) {
            dfs(v, x);
            sz[x] += sz[v];
            if (sz[v]) {
                if (const int k = f[v][0] + ew[i]; k > f[x][0]) {//更新最长路径
                    f[x][2] = f[x][1], f[x][1] = f[x][0], f[x][0] = k,
                    g[x][2] = g[x][1], g[x][1] = g[x][0], g[x][0] = v;
                } else if (k > f[x][1]) {//更新第二长路径
                    f[x][2] = f[x][1], f[x][1] = k, g[x][2] = g[x][1], g[x][1] = v;
                } else if (k > f[x][2]) {//更新第三长路径
                    f[x][2] = k, g[x][2] = v;
                }
            }
        }
    }
    ///如果最长和次长路径长度相同，p[x] = x
    ///否则p[x] = 最长路径来源点的p值
    p[x] = f[x][0] == f[x][1] ? x : p[g[x][0]];//p[x]记录最长路径来源
}

//m: 特殊点总数
int m, s[N];// 差分数组，用于统计路径覆盖次数
void dfs2(const int x, const int fa, int len, int lca) {
    if (m - sz[x] == 0) len = lca = 0;//没有特殊点，重置参数
    if (b[x]) {
        if (len > f[x][0]) {
            const int t = LCA::lca(x, lca);
            //差分标记路径覆盖：在路径两端+1，在LCA处-1，在LCA父节点处-1
            s[x]++, s[lca]++, s[t]--, s[F[t]]--;//差分标记路径
        } else if (len < f[x][0]) {
            s[F[x]]--, s[p[x]]++;//更新贡献
        }
    }
    for (int i = head[x]; i; i = nxt[i]) {
        if (const int v = to[i]; v != fa) {
            int a, bb;//除v方向外的最大、第二大路径长度
            v == g[x][0] ? (a = f[x][1], bb = f[x][2]) : (v == g[x][1] ? (
                a = f[x][0], bb = f[x][2]) : (a = f[x][0], bb = f[x][1]));
            const int c = g[x][v == g[x][0]];// 对应a路径的子节点
            //根据当前路径长度调整传递给子节点的参数
            if (len > a) dfs2(v, x, len + ew[i], lca);
            else if (len == a) dfs2(v, x, len + ew[i], x);
            else if (len < a) dfs2(v, x, a + ew[i], a == bb ? x : p[c]);
        }
    }
}



int main() {
    fast;
    int n; cin >> n >> m;
    for (int i = 1, x; i <= m; ++i) cin >> x, b[x] = true;//标记特殊点
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    LCA::ini();
    dfs(1, 0); dfs2(1, 0, 0, 0);
    int mx = 0, num = 0;
    for (int i = n; i; --i) {//计算子树贡献
        const int x = dfn2[i];
        s[F[x]] += s[x];//向上传递差分标记
        if (!b[x]) {//不是特殊点
            s[x] > mx ? (mx = s[x], num = 0) : 0;//更新最大值
            num += mx == s[x];//统计最优点数量
        }
    }
    cout << mx << ' ' << num << '\n';//最大覆盖次数和最优点数量
    return 0;
}