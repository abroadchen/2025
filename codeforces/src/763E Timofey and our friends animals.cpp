//
// Created by Psy.C on 2026/9/6.
//
/**
离线构建：预处理所有可能出现的小区间（长度 ≤ k）的连通性信息。
在线查询：对于大于 k 的区间，通过线段树快速合并结果
状态压缩：将一个小区间的连通块压缩成唯一编号（check() 函数）。
离线枚举 + 记忆化：暴力枚举所有可能的子集状态（trans() 函数），存入 a[][] 表中。
线段树合并：自定义 node 类型，实现区间内连通块的“拼接”与映射（operator+ 重载
N：用于处理状态压缩时的最大节点数上限（通常是 k 的最大值）。
M：图中边的最大数量（因为是稀疏图，最多 1e5 条边）。
K：线段树节点数上限。由于线段树需要维护 [k, n] 区间，节点数远大于 n，因此设置较大的安全阈值

to[i]：表示将左半区间的第 i 个连通块映射到右半区间后对应的编号。
lt[i]：表示从左到右映射过程中，新增了多少条跨越两个子区间的边（即连接了多少对不同连通块
cnt：当前已知的独特小区间状态总数。
a[i][j]：状态 i 在加入边集合 j（j 为二进制掩码）后的新状态编号。
edg[i]：第 i 条边的二进制掩码（表示它连接了哪些位置）。
b[i][j]：记录状态 i 在加入边集合 j 后产生的跨越次数（lt 的来源
qwq[] 数组中存放了当前子区间每个点所属的连通块编号
暴力枚举 k 个位置的初始划分（即每个点单独为一类），共
k
k
k
k
  种组合（由于 k 很小，这里是可行的）。
每生成一种组合，就调用 check() 进行压缩登记

模拟在已有状态 id 的基础上，添加一组新的边（由 edges 掩码决定）后，状态如何变化以及跨越次数。
步骤：
初始化 fa[] 为当前状态的连通块编号。
遍历 edges 中的每一条边，将其所在的连通块统一标记为 k+1（临时合并）。
统计跨越次数（即是否有新的连接产生）。
对临时合并后的编号进行重新编号（避免冲突）。
调用 check() 获取新状态的 ID，并记录在 a[id][edges] 中

针对长度不超过 k 的短区间，直接使用并查集（DSU）计算连通块数量。
逻辑：
初始化每个点为独立集合。
遍历区间内的所有边，执行合并操作。
最后统计根节点的数量，即为连通块个数。

第一步：dfs(1) 枚举出所有可能的 k 长度子区间划分方式，并压缩成唯一 ID。
第二步：对每个状态遍历所有可能的边集合（2^k 种），调用 trans() 预处理转移表 a[][] 和跨越次数表 b[][]。
第三步：滑动窗口处理，从第 k 位开始，每次向右扩展一个点：
使用 lek() 计算当前窗口的连通块数。
将窗口状态压缩为唯一 ID 存入 fst[i]。
将第 i 条边转换为二进制掩码存入 edg[i]

叶子节点 (l == r)：对应一个具体的右端点 r。
t[u].to[i] = a[i][edg[l]]：读取状态 i 在加入当前边 edg[l] 后的映射目标。
t[u].lt[i] = b[i][edg[l]]：读取该变换产生的跨越次数。
内部节点：递归构建左右子树后，使用前面重载的 operator+ 合并两个区间的信息
标准的线段树查询函数，返回区间 [L,R] 内的合并结果 node

读取输入：n 为节点数，k 为阈值（最长离线处理长度），m 为边数。
构建图：将所有边存入邻接表 g[]，并记录最大的跨度 mx（用来限制 k 的实际大小）。
初始化：init() 完成离线预处理；build() 构建线段树。
查询处理：
短区间：若区间长度 <= k，直接使用 lek() 暴力 DSU 求解。
长区间：利用线段树查询 [l+k, r] 区间的合并结果 x。
* fst[l+k-1] 是左侧窗口 [l, l+k-1] 的状态 ID。
x.to[fst[l+k-1]] 映射到了右侧的状态编号。
x.lt[fst[l+k-1]] 是跨越次数。
ctt[...] 是右侧状态对应的连通块数。
两者相加即为完整区间 [l, r] 的连通块数量
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 55, M = 1e5+5, K = 4e5+5;

//描述一个区间内的映射关系
struct node { int to[N], lt[N]; } t[K];
int cnt, a[N][N], edg[M], b[N][N];
node operator+(node p, node q) {
    node tmp{};
    for (int i = 1; i <= cnt; ++i)
        tmp.to[i] = q.to[p.to[i]], tmp.lt[i] = p.lt[i]+q.lt[p.to[i]];
    return tmp;
}

inline void build(int u, int l, int r) {
    if (l == r) {
        for (int i = 1; i <= cnt; ++i)
            t[u].to[i] = a[i][edg[l]], t[u].lt[i] = b[i][edg[l]];
        return;
    }
    int mid = (l+r)>>1;
    build(u<<1, l, mid); build(u<<1|1, mid+1, r);
    t[u] = t[u<<1] + t[u<<1|1];
}

inline node query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[u];
    int mid = (l+r)>>1;
    if (L > mid) return query(u<<1|1, mid+1, r, L, R);
    if (R <= mid) return query(u<<1, l, mid, L, R);
    return query(u<<1, l, mid, L, R) + query(u<<1|1, mid+1, r, L, R);
}

int k, qwq[10], sst[N], ctt[N], st[N][10];
map<int, int> stt;
//将一个长度为 k 的子区间的连通块划分情况转化为一个唯一的整数 ID
inline int check() {
    int mn[10], a[10], b[10];
    memset(mn, 0x3f, sizeof mn);
    vector<int> bl[10];
    //统计每个颜色出现的位置并记录最小下标
    for (int i = 1; i <= k; ++i)
        bl[qwq[i]].emplace_back(i), mn[qwq[i]] = min(mn[qwq[i]], i), b[i] = i;
    //按照最小下标进行排序，重新编号
    sort(b+1, b+k+1, [&](int x, int y) {
        return mn[x] < mn[y];
    });
    //重新编号过程
    int S = 0, c = 0;
    for (int i = 1; i <= k; ++i)
        if (!bl[b[i]].empty()) {
            c++;
            for (int v : bl[b[i]]) a[v] = c;
        }
    //将编号序列压缩成唯一整数 S
    for (int i = 1; i <= k; ++i) S = S*10 + a[i];
    if (stt.contains(S)) return stt[S];//检查是否已经存在该状态
    //新增状态
    cnt++;
    sst[cnt] = S; ctt[cnt] = c;
    for (int i = 1; i <= k; ++i) st[cnt][i] = a[i];
    stt[S] = cnt;
    return 0;
}

//枚举所有可能的划分
inline void dfs(int id) {
    if (id > k) { check(); return; }
    for (int i = 1; i <= k; ++i) qwq[id] = i, dfs(id+1);
}

int fa[10];
inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

//状态转移
inline void trans(int id, int edges) {
    int s = 0;
    for (int i = 1; i <= k; ++i) fa[i] = st[id][i];
    fa[k+1] = k+1;
    //根据 edges 掩码合并连通块
    for (int i = 1; i <= k; ++i)
        if ((edges>>(i-1))&1) {
            int bl = fa[i];
            for (int j = 1; j <= k; ++j)
                if (fa[j] == bl) fa[j] = k+1;
        }
    //统计跨越次数
    int h[10] = {}, nd = 1;
    for (int i = 2; i <= k+1; ++i)
        qwq[i-1] = fa[i], h[fa[i]] = 1, s += (fa[i] == fa[1]);
    if (!s) b[id][edges] = 1;
    while (h[nd]) nd++;
    for (int i = 1; i <= k; ++i)
        if (qwq[i] == k+1) qwq[i] = nd;
    int to = check();
    a[id][edges] = to;
}

vector<int> g[M];
//离线求解小区间连通块数量
inline int lek(int l, int r) {
    for (int i = l; i <= r; ++i) fa[i-l+1] = i-l+1;
    for (int i = l+1; i <= r; ++i)
        for (int v : g[i])
            if (v >= l) fa[find(v-l+1)] = find(i-l+1);
    int s = 0;
    for (int i = l; i <= r; ++i)
        s += find(i-l+1) == i-l+1;
    return s;
}

int n, fst[M];
inline void init() {
    dfs(1);//枚举并压缩所有可能的 k 长度划分
    for (int i = 1; i <= cnt; ++i)
        for (int s = 0; s < 1<<k; ++s) trans(i, s);//预处理所有状态转移
    for (int i = k; i <= n; ++i) {
        lek(i-k+1, i);//计算初始窗口的连通块数
        for (int j = 1; j <= k; ++j) qwq[j] = find(j);
        fst[i] = check();//获取窗口状态的唯一 ID
        int s = 0;
        for (int v : g[i]) s |= 1<<(v-(i-k));
        edg[i] = s;//记录第 i 条边的二进制掩码
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int m, q;
int main() {
    rd(n), rd(k), rd(m);
    int mx = 0;
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u), rd(v);
        if (u < v) swap(u, v);
        mx = max(mx, u-v);
        g[u].emplace_back(v);
    }
    k = min(k, mx); init(); build(1, k, n); rd(q);
    while (q--) {
        int l, r; rd(l), rd(r);
        if (r-l+1 <= k) {
            printf("%d\n", lek(l, r));
            continue;
        }
        node x = query(1, k, n, l+k, r);
        printf("%d\n", x.lt[fst[l+k-1]]+ctt[x.to[fst[l+k-1]]]);
    }
    return 0;
}