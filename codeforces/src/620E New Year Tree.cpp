//
// Created by Psy.C on 2026/3/26.
//
/**
l, r：线段树节点对应区间范围
laz：懒惰标记，用于区间更新
x：存储颜色集合的位掩码
L[N], R[N]：DFS序中每个节点的进入和退出时间戳
dep：DFS深度计数器
val[N]：DFS序对应的颜色值
col[N]：每个节点的颜色
g[N]：邻接表存储树结构
建立DFS序，将树上子树操作转化为区间操作
L[u]：进入节点u的时间戳
R[u]：离开节点u的时间戳
val[dep] = col[u]：保存DFS序中的颜色值
递归建树
叶子节点：tr[st].x = 1ll<<val[l]，用位掩码表示单个颜色
非叶子节点：tr[st].x = 左子树颜色集合 | 右子树颜色集合
将懒惰标记向下传递
更新左右子树的颜色集合和懒惰标记
清除当前节点的懒惰标记
区间赋值操作：将区间[l,r]内的所有颜色改为v
如果完全覆盖，设置懒惰标记并返回
否则下传懒惰标记，递归更新
更新完成后合并子树信息
查询区间[l,r]内的颜色集合
如果完全覆盖，直接返回
否则下传懒惰标记，递归查询并合并结果

读入节点数n和操作数m
读入每个节点的颜色
构建邻接表表示树结构
从根节点1开始DFS，建立DFS序
基于DFS序构建线段树
操作1：update(L[x], R[x], y, 1)
将节点x的子树全部染色为y
在DFS序中，子树对应区间[L[x], R[x]]
操作2：查询节点x子树中的不同颜色数量
query(L[x], R[x], 1)：获取子树颜色集合的位掩码
统计位掩码中1的个数（不同颜色的数量）
ans -= ans&-ans：每次清除最低位的1，直到ans为0
时间复杂度：O((n+m)log n) 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;

struct node { int l, r, laz; ll x; } tr[N<<2];
int L[N], R[N], dep, val[N], col[N];
vector<int> g[N];
void dfs(int u, int fa) {
    L[u] = ++dep; val[dep] = col[u];
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v != fa) dfs(v, u);
    }
    R[u] = dep;
}

void build(int l, int r, int st) {
    tr[st].laz = 0;
    tr[st].l = l, tr[st].r = r;
    if (l == r) {
        tr[st].x = 1ll<<val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, st<<1); build(mid+1, r, st<<1|1);
    tr[st].x = tr[st<<1].x|tr[st<<1|1].x;
}
void pushdown(int st) {
    if (tr[st].laz) {
        tr[st<<1].x = tr[st<<1|1].x = 1ll<<tr[st].laz;
        tr[st<<1].laz = tr[st<<1|1].laz = tr[st].laz;
        tr[st].laz = 0;
    }
}
void update(int l, int r, int v, int st) {
    if (tr[st].l >= l && tr[st].r <= r) {
        tr[st].laz = v;
        tr[st].x = 1ll<<v;
        return;
    }
    pushdown(st);
    int mid = (tr[st].l + tr[st].r) >> 1;
    if (r <= mid) update(l, r, v, st<<1);
    else if (l > mid) update(l, r, v, st<<1|1);
    else {
        update(l, mid, v, st<<1);
        update(mid+1, r, v, st<<1|1);
    }
    tr[st].x = tr[st<<1].x|tr[st<<1|1].x;
}
ll query(int l, int r, int st) {
    if (tr[st].l >= l && tr[st].r <= r) return tr[st].x;
    pushdown(st);
    int mid = (tr[st].l + tr[st].r) >> 1;
    if (r <= mid) return query(l, r, st<<1);
    if (l > mid) return query(l, r, st<<1|1);
    return query(l, mid, st<<1)|query(mid+1, r, st<<1|1);
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> col[i];
    for (int i = 0, u, v; i < n-1; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, -1); build(1, n, 1);
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y;
            update(L[x], R[x], y, 1);
        } else {
            int x; cin >> x;
            ll ans = query(L[x], R[x], 1);
            int sum = 0;
            while (ans > 0) {
                ans -= ans&-ans;
                sum++;
            }
            cout << sum << '\n';
        }
    }
    return 0;
}