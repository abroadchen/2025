
/*
 * sv存储区间和，av存储懒惰标记（延迟更新标记）
*build函数：构建线段树，参数为节点编号p，区间左右端点l,r
初始化当前节点的区间和与懒惰标记为0
如果区间只有一个点，递归结束
否则计算中点，递归构建左右子树（p<<1是左子树，p<<1|1是右子树）
*push_down函数：下推懒惰标记
如果当前节点有懒惰标记，则将其传递给左右子树
更新子树的区间和，并清空当前节点的懒惰标记
*query函数：单点查询，返回位置pos的值
如果到达叶子节点，返回该节点的值
否则先下推懒惰标记，然后递归查询左子树或右子树
 *push_up函数：上传子节点信息，更新父节点的区间和
*modify函数：区间修改，将[ql,qr]区间加上val
如果当前区间完全在修改区间内，直接更新区间和和懒惰标记
否则下推懒惰标记，递归修改左右子树，最后上传信息
 *
*n：节点数，tim：时间戳
g[N]：邻接表存储树
 *init函数：初始化图和线段树
 *add函数：在邻接表中添加边
 *
*dep[i]：节点i的深度
id[i]：节点i的时间戳编号
son[i]：节点i的子树大小
dfs函数：深度优先遍历，计算每个节点的深度、时间戳和子树大小
 *query函数：查询节点v的值，返回两个线段树查询结果的和
*modify函数：对以节点v为根的子树中距离不超过dist的节点加上val
特殊处理根节点情况
计算查询区间，根据距离条件更新线段树
 *
*读入节点数n和操作数m
读入n-1条边构建树
执行DFS遍历
执行m个操作：操作1为查询，操作2为修改
 *
 *
* len：剩余距离，表示从节点v往下还能走多远
ql, qr：查询区间的左右端点，用于在cn线段树中操作
*如果剩余距离为正，说明从节点v出发还能向下走
在lr线段树的[1, len+1]区间增加val，处理路径上的节点
*计算在cn线段树中操作的左端点
id[v]是节点v的DFS序编号
len - dep[v]考虑了距离和深度的关系
这个公式计算从节点v开始，在DFS序中应该从哪个位置开始修改
*计算在cn线段树中操作的右端点
如果dist大于节点v的子树大小，说明能遍历完整个子树
否则只能遍历到距离限制的位置
id[v] + son[v]表示v子树的结束位置
id[v] + dist表示按距离限制的结束位置
 *在cn线段树的[ql, qr]区间增加val
 *
*当剩余距离非正时，计算左端点
从节点v的DFS序位置减去dist，得到操作的起始位置
 *计算右端点，逻辑同上
*如果dep[v] - dist == 0，意味着操作会涉及到根节点
此时需要额外对根节点（在cn线段树位置1）增加val
同时对区间[ql+1, qr]进行操作
否则直接对[ql, qr]区间操作
 *
 */

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

struct node {
    int sv[N<<2], av[N<<2];
    void build(const int p, const int l, const int r) {
        sv[p] = av[p] = 0;
        if (l == r) return;
        const int mid = (l + r) >> 1;
        build(p<<1, l, mid);
        build(p<<1|1, mid+1, r);
    }

    void push_down(const int p, const int l, const int r) {
        if (av[p]) {
            const int mid = (l + r) >> 1;
            av[p<<1] += av[p], av[p<<1|1] += av[p];
            sv[p<<1] += av[p] * (mid - l + 1);
            sv[p<<1|1] += av[p] * (r - mid);
            av[p] = 0;
        }
    }

    int query(const int p, const int l, const int r, const int pos) {
        if (l == r) return sv[p];
        push_down(p, l, r);
        const int mid = (l + r) >> 1;
        if (pos <= mid) return query(p<<1, l, mid, pos);
        return query(p<<1|1, mid+1, r, pos);
    }

    void push_up(const int p) { sv[p] = sv[p<<1] + sv[p<<1|1]; }

    void modify(const int p, const int l, const int r, const int ql, const int qr, const int val) {
        if (ql <= l && r <= qr) {
            sv[p] += val * (r - l + 1);
            av[p] += val;
            return;
        }
        push_down(p, l, r);
        const int mid = (l + r) >> 1;
        if (ql <= mid) modify(p<<1, l, mid, ql, qr, val);
        if (qr > mid) modify(p<<1|1, mid+1, r, ql, qr, val);
        push_up(p);
    }
} lr, cn;


int n, tim;
vector<int> g[N];
void init() {
    for (int i = 1; i <= n; ++i) g[i].clear();
    tim = 0;
    lr.build(1, 1, N);
    cn.build(1, 1, N);
}
void add(const int u, const int v) { g[u].push_back(v); }

int dep[N], id[N], son[N];
void dfs(const int u, const int pre, const int d) {
    id[u] = ++tim;
    dep[u] = d;
    son[u] = 0;
    for (int i = 0; i < g[u].size(); ++i) {
        const int v = g[u][i];
        if (pre == v) continue;
        dfs(v, u, d+1);
        son[u] = son[v] + 1;
    }
}

int query(const int v) {
    return cn.query(1, 1, N, id[v]) +
        lr.query(1, 1, N, dep[v] + 1);
}

void modify(const int v, const int val, const int dist) {
    if (v == 1) {//是根节点
        lr.modify(1, 1, N, 1, dist + 1, val);
        return;
    }
    const int len = dist - dep[v]; int ql, qr;
    if (len > 0) {
        lr.modify(1, 1, N, 1, len + 1, val);
        ql = id[v] + len - dep[v] + 1;
        qr = dist > son[v] ? id[v] + son[v] : id[v] + dist;
        cn.modify(1, 1, N, ql, qr, val);
    } else {
        ql = id[v] - dist;
        qr = dist > son[v] ? id[v] + son[v] : id[v] + dist;
        if (dep[v] - dist == 0) {
            cn.modify(1, 1, N, 1, 1, val);
            cn.modify(1, 1, N, ql + 1, qr, val);
        } else cn.modify(1, 1, N, ql, qr, val);
    }
}

int main() {
    fast;
    int m; cin >> n >> m; init();
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(1, -1, 0);
    for (int i = 0, op, v, x, d; i < m; ++i) {
        cin >> op;
        if (op == 1) {
            cin >> v; cout << query(v) << '\n';
        } else {
            cin >> v >> x >> d;
            modify(v, x, d);
        }
    }
    return 0;
}