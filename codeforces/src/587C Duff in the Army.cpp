//
// Created by Psy.C on 2026/3/18.
//
/**
nxt: 指向邻接表中下一条边的指针
to: 边的目标节点
tot: 边的总数计数器
head[i]: 节点i在邻接表中的第一条边
存储路径上的前10个最小值
sz: 当前存储的元素个数
num[12]: 存储最多10个元素的数组
operator+=: 重载+=运算符，将值x插入到有序数组的合适位置
lower_bound(): 查找插入位置
最多保存10个元素
p[i][j]: 从节点i向上走2^j步路径上的前10个最小值

dep[i]: 节点i的深度
fa[i][j]: 节点i的第2^j个祖先
构建倍增表，用于LCA查询
1<<i表示2^i
更新祖先关系和路径信息
遍历当前节点的所有邻居
跳过父节点（避免回溯）
设置u的父节点为now
更新u的深度
递归处理子节点
将节点x向上移动y距离，并累积路径值
1<<i&y检查y的第i位是否为1
使用二进制分解的方式跳跃
确保y的深度不小于x
将y提升到与x相同的深度
如果x=y，说明x是LCA，加上节点值
从高位到低位查找LCA
当两个节点的2^i祖先不同时，同时向上跳跃
最后加上从LCA到两个节点的路径信息

n: 树的节点数
m: 特殊值的数量
q: 查询数量
val[i]: 存储特殊节点的值
将节点值i添加到对应节点的路径信息中
处理q个查询
每个查询包含起点u、终点v和要求的前a个最小值
调用LCA函数计算路径上的值
输出前min(a, 实际个数)个最小值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node { int nxt, to; } e[N<<1];

int tot, head[N];
void add(int a, int b) {
    e[++tot] = {head[a], b}, head[a] = tot;
}

struct path {
    int sz, num[12];
    void operator+=(const int& x) {
        int p = lower_bound(num, num + sz, x) - num;
        for (int i = sz; i >= p; --i) num[i] = num[i-1];
        num[p] = x;
        sz = min(sz + 1, 10);
    }
    path operator+(const path& o) const {
        path res;
        int i = 0, j = 0, k = 0;
        while (k < 10 && i < sz && j < o.sz) {
            if (num[i] <= o.num[j]) res.num[k++] = num[i++];
            else res.num[k++] = o.num[j++];
        }
        while (i < sz && k < 10) res.num[k++] = num[i++];
        while (j < o.sz && k < 10) res.num[k++] = o.num[j++];
        res.sz = k;
        return res;
    }
} p[N][20], res;

int dep[N], fa[N][20];
void dfs(int now) {
    for (int i = 1; 1<<i <= dep[now]; ++i) {
        fa[now][i] = fa[fa[now][i-1]][i-1];
        p[now][i] = p[now][i-1] + p[fa[now][i-1]][i-1];
    }
    for (int i = head[now]; i; i = e[i].nxt) {
        int u = e[i].to;
        if (u == fa[now][0]) continue;
        fa[u][0] = now;
        dep[u] = dep[now] + 1;
        dfs(u);
    }
}

void push_up(int& x, int y) {
    for (int i = 0; i < 20; ++i)
        if (1<<i&y) {
            res = res + p[x][i];
            x = fa[x][i];
        }
}

void lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    push_up(y, dep[y] - dep[x]);
    if (x == y) {
        res = res + p[x][0];
        return;
    }
    for (int i = 19; i >= 0; --i)
        if (fa[x][i] != fa[y][i]) {
            res = res + p[x][i] + p[y][i];
            x = fa[x][i];
            y = fa[y][i];
        }
    res = res + p[x][1] + p[y][0];
}

int n, m, q, val[N];
int main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    for (int i = 1; i <= m; ++i) {
        cin >> val[i];
        p[val[i]][0] += i;
    }
    dep[1] = 1; dfs(1);
    for (int i = 1, u, v, a; i <= q; ++i) {
        res.sz = 0;
        cin >> u >> v >> a; lca(u, v);
        int k = min(a, res.sz);
        cout << k << ' ';
        for (int j = 0; j < k; ++j)
            cout << res.num[j] << ' ';
        cout << '\n';
    }
    return 0;
}