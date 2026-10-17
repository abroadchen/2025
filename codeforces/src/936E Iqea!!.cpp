//
// Created by Psy.C on 2026/10/17.
//
/**
rep(i,j)：0 到 j-1 的循环宏，## 拼接生成不冲突的内部变量名。
N：点数上限；inf 大数。
chkmin：更新最小值的工具
c[N]：每个分量里点的个数（BIT 尺寸）。
b1[N]、b2[N]：每个重心开两棵 BIT（b1 正向、b2 反向，用于两侧查询）
upd1：在第 k 棵 BIT 上做单点更新（从 x 往后的正向结构），值取 min
qry1：前缀查询最小值（从 x 往前）
upd2/qry2：对称的反向 BIT（后缀查询）。这样实现对"两侧子集"的距离最小值查询。
综上：每个重心 k 维护两棵 BIT，b1 查询前缀最小值、b2 查询后缀最小值，配合更新实现"到重心距离 ≤ v 的 min"

m：出现的最大坐标（行/列维度）。
no：节点全局编号计数器。
s[x]：第 x 行的点集（存 y 坐标）。
id[x][y]：把坐标 (x,y) 映射成节点编号。
g[N]：点分树上的边（重心树内节点连接）。
e[N]：分量之间的边（用于建重心树/点分树）。
sz、son、vis、sum、rt：点分治找重心用。
p[u][d]：点 u 在第 d 层重心中的排序位置（相对 ly）。
dis[u][d]：点 u 到第 d 层重心的距离。
dep、fa：点分树的深度和父节点
建无向边：g 表示点分树内相邻节点、e 表示分区间相邻
对每一行（x 坐标），把 y 坐标排序
遍历排序后的每个点：
分配全局节点号 no，记录 id[x][v]。
若与前一个 y 坐标连续（s[x][i-1]+1==v），则两点在 g 中连边（同一连续段内相邻）。
否则（新段开始）新建一个"分量"编号 cnt，记录 lx[cnt]=x（所在行）、ly[cnt]=i（段起点在 s[x] 中的下标）。
b[no]=cnt：点 no 属于分量 cnt；c[cnt]++：分量大小+1
用双指针 j 在上一行 x-1 中找等于 v 的 y：若上一行同一 y 有点存在，则当前点与上一行点在同列相邻（上下连通），在 g 连边、在 e（分区间）也连边
对每个分量的邻接区间集合去重
为每棵 BIT 预分配 c[i]+1 个位置并初始化为 inf
树 DP 求重心：sz[x] 以分量节点数 c[x] 为权；son[x] 记录去掉 x 后最大子树。
son[x] = max(son[x], sum-sz[x])：考虑父亲侧。
若 son[x] < son[rt] 则更新重心 rt
对重心分量 x 的每个点：设 p[u][d]=位置、dis=0，入队做 BFS 起点
BFS 沿 g（相邻点）扩散，把同一连续段/连通块内所有点的 p（同一重心分量内的相对位置）和 dis（到重心的距离）填好
标记重心 x 已访问，记录深度，build 该层距离信息。
对 x 的每个子分量 v，递归找子重心 rt 并继续；fa[rt]=x 建立点分树父子关系、dep 递增
从点 x 所在分量 b[x] 沿点分树一直往上到根 fa[y]。
对每层重心 y：以 p[x][d] 为下标更新两棵 BIT：
b1 存 dis - p，b2 存 dis + p
沿点分树每层重心 y：用公式 dis[x][d]+p[x][d]+qry1(...) 和 dis[x][d]-p[x][d]+qry2(...) 组合出查询结果。
若结果 < N 返回结果，否则返回 -1

读 n 个点，按行存入 s[x]，m 记录最大行。
init() 建图，getrt(1,0) 整树找重心，solve(rt,0) 建立点分树
读查询数 Q。
每次读 op、x、y，映射成节点 id[x][y]：
op 为奇数 → 单点更新；
op 为偶数 → 查询该点
 */
#include <bits/stdc++.h>
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 3e5+10, inf = 1e8+10;

void chkmin(int &x, int y) { x = min(x, y); }

int c[N];
namespace BIT {
#define low_bit(x) (x&(-x))
    vector<int> b1[N], b2[N];
    void upd1(int k, int x, int v) {
        for (; x <= c[k]; x += low_bit(x)) chkmin(b1[k][x], v);
    }
    int qry1(int k, int x) {
        int res = inf;
        for (; x; x -= low_bit(x)) chkmin(res, b1[k][x]);
        return res;
    }
    void upd2(int k, int x, int v) {
        for (; x; x -= low_bit(x)) chkmin(b2[k][x], v);
    }
    int qry2(int k, int x) {
        int res = inf;
        for (; x <= c[k]; x += low_bit(x)) chkmin(res, b2[k][x]);
        return res;
    }
}
using namespace BIT;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


int m, no, lx[N], cnt, ly[N], b[N], n, Q;
namespace Dyn {
    vector<int> g[N], e[N], s[N];
    map<int, int> id[N];
    int sz[N], son[N], vis[N], sum, rt, p[N][22], dis[N][22], dep[N], fa[N];
    queue<int> q;
    void add_g(int x, int y) { g[x].push_back(y); g[y].push_back(x); }
    void add_e(int x, int y) { e[x].push_back(y); e[y].push_back(x); }
    void init() {
        for (int x = 1; x <= m; ++x) {
            if (s[x].empty()) continue;
            ranges::sort(s[x]);
            int j = 0;
            rep(i,s[x].size()) {
                int v = s[x][i]; id[x][v] = ++no;
                if (i && s[x][i-1]+1 == v) add_g(no-1, no);
                else ++cnt, lx[cnt] = x, ly[cnt] = i;
                b[no] = cnt; c[cnt]++;
                while (j < s[x-1].size() && s[x-1][j] < v) ++j;
                if (j < s[x-1].size() && s[x-1][j] == v) {
                    int t = id[x-1][s[x-1][j]];
                    add_g(no, t); add_e(cnt, b[t]);
                }
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            ranges::sort(e[i]);
            e[i].erase(ranges::unique(e[i]).begin(), e[i].end());
        }
        for (int i = 1; i <= cnt; ++i) for (int j = 0; j <= c[i]; ++j)
            b1[i].push_back(inf), b2[i].push_back(inf);
    }
    void getrt(int x, int f) {
        sz[x] = c[x]; son[x] = 0;
        rep(i,e[x].size()) {
            int v = e[x][i];
            if (vis[v] || v == f) continue;
            getrt(v, x);
            sz[x] += sz[v]; son[x] = max(son[x], sz[v]);
        }
        son[x] = max(son[x], sum-sz[x]);
        if (son[x] < son[rt]) rt = x;
    }
    void build(int x, int d) {
        while (!q.empty()) q.pop();
        for (int i = ly[x]; i < ly[x]+c[x]; ++i) {
            int y = s[lx[x]][i], u = id[lx[x]][y];
            p[u][d] = i - ly[x] + 1; dis[u][d] = 0; q.push(u);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            rep(i,g[u].size()) {
                int v = g[u][i];
                if (vis[b[v]] || p[v][d]) continue;
                p[v][d] = p[u][d]; dis[v][d] = dis[u][d] + 1;
                q.push(v);
            }
        }
    }
    void solve(int x, int d) {
        vis[x] = 1; dep[x] = d; build(x, d);
        rep(i,e[x].size()) {
            int v = e[x][i];
            if (vis[v]) continue;
            rt = 0; sum = sz[v]; getrt(v, x); fa[rt] = x;
            solve(rt, d+1);
        }
    }
    void update(int x) {
        for (int y = b[x], d; y; y = fa[y]) {
            d = dep[y], upd1(y, p[x][d], dis[x][d]-p[x][d]),
            upd2(y, p[x][d], dis[x][d]+p[x][d]);
        }
    }
    int query(int x) {
        int res = inf;
        for (int y = b[x], d; y; y = fa[y]) {
            d = dep[y], chkmin(res, dis[x][d]+p[x][d]+qry1(y, p[x][d])),
            chkmin(res, dis[x][d]-p[x][d]+qry2(y, p[x][d]));
        }
        return res < N ? res : -1;
    }
    void out() {
        n = rd();
        for (int i = 1; i <= n; ++i) {
            int x = rd(), y = rd();
            m = max(m, x); s[x].push_back(y);
        }
        init(); son[0] = sum = n;
        getrt(1, 0); solve(rt, 0);
        Q = rd();
        while (Q--) {
            int op = rd(), x = rd(), y = rd();
            if (op&1) update(id[x][y]);
            else printf("%d\n", query(id[x][y]));
        }
    }
}

int main() {
    Dyn::out();
    return 0;
}