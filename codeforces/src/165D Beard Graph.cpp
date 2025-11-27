//
// Created by Psy.C on 2025/11/27.
//
/*
*N: 常量，最大节点数(100005)
n: 节点数
q: 查询数
id[N<<2]: 存储边的信息，id[i]表示第i条边连接的两个节点
e[N]: 邻接表，存储树的结构
 *
 *树链剖分所需的数组
*dep[N]: 节点深度
sz[N]: 子树大小
son[N]: 重儿子
p[N]: 父亲节点
vis[N]: 访问标记
 *
*第一次DFS，计算树的基本信息：
标记节点u已访问
初始化子树大小为1
设置父节点为root
计算节点深度
*遍历节点u的所有邻接点：
如果不是父节点且未访问过，则递归处理
累加子树大小
选择子树最大的子节点作为重儿子
 *
*树链剖分第二阶段所需数组：
top[N]: 链顶节点
pos[N]: 节点在线段树中的位置
lev[N]: 位置对应的节点编号
cnt: 位置计数器
 *
*第二次DFS，进行树链剖分：
标记节点u已访问
分配在线段树中的位置
设置链顶节点
优先处理重儿子（在同一链中）
 *处理轻儿子，每个轻儿子开启新链
 *
*线段树数组：
sum[N<<2]: 区间和
mn[N<<2]: 区间最小值
*ql,qr: 查询区间
l,r: 当前区间
rt: 当前节点
ok: true表示查询和，false表示查询最小值
*树上路径查询：
当两个节点不在同一链时，跳转到链顶较深的节点
查询该链上的信息并累加/比较
 *当两个节点在同一链时，直接查询区间信息
 *
*op=1/2: 修改第a条边的状态（1表示激活，2表示禁用）
op=3: 查询从a到b的路径，如果路径全通则输出路径长度，否则输出-1
 *
 *时间复杂度：每次操作O(log²n)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;
int n, q;
pair<int,int> id[N<<2];
vector<int> e[N];

int dep[N], sz[N], son[N], p[N];
bool vis[N];
void dfs1(const int u, const int root) {
    vis[u] = true; sz[u] = 1; p[u] = root;
    dep[u] = dep[root] + 1;
    const int siz = static_cast<int>(e[u].size());
    for (int i = 0; i < siz; ++i) {
        const int v = e[u][i];
        if (v != p[u] && !vis[v]) {
            dfs1(v, u);
            sz[u] += sz[v];
            if (son[u] == 0 || sz[son[u]] < sz[v]) son[u] = v;
        }
    }
}
int top[N], pos[N], lev[N], cnt;
void dfs2(const int u, const int root) {
    vis[u] = true; pos[u] = ++cnt; lev[cnt] = u; top[u] = root;
    if (son[u]) dfs2(son[u], root);
    const int siz = static_cast<int>(e[u].size());
    for (int i = 0; i < siz; ++i) {
        const int v = e[u][i];
        if (v != p[u] && v != son[u] && !vis[v]) dfs2(v, v);
    }
}

//构建线段树
int sum[N<<2], mn[N<<2];
void build(const int l, const int r, const int rt) {
    sum[rt] = r - l + 1; mn[rt] = 1;
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1|1);
}

//线段树查询函数
int query(const int ql, const int qr, const int l, const int r, const int rt, const bool ok) {
    if (ql <= l && r <= qr) return ok ? sum[rt] : mn[rt];
    const int mid = (l + r) >> 1;
    int x = ok ? 0 : 1;
    if (ql <= mid) {
        const int t = query(ql, qr, l, mid, rt<<1, ok);
        x = ok ? x + t : min(x, t);
    }
    if (qr > mid) {
        const int t = query(ql, qr, mid + 1, r, rt<<1|1, ok);
        x = ok ? x + t : min(x, t);
    }
    return x;
}

//树上路径查询
int search(int x, int y, const bool ok) {
    int ans = ok ? 0 : 1;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        int t = query(pos[top[x]], pos[x], 1, cnt, 1, ok);
        ans = ok ? ans + t : min(ans, t);
        x = p[top[x]];
    }
    if (x == y) return ans;
    if (dep[x] > dep[y]) swap(x, y);
    const int t = query(pos[son[x]], pos[y], 1, cnt, 1, ok);
    return ok ? ans + t : min(ans, t);
}

//向上更新函数
void push_up(const int rt) {
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    mn[rt] = min(mn[rt<<1], mn[rt<<1|1]);
}

//单点修改函数
void modify(const int o, const int val, const int l, const int r, const int rt) {
    if (l == r) { sum[rt] = val; mn[rt] = val; return; }
    const int mid = (l + r) >> 1;
    if (o <= mid) modify(o, val, l, mid, rt<<1);
    else modify(o, val, mid + 1, r, rt<<1|1);
    push_up(rt);
}

int main() {
    fast;
    cin >> n;
    int op, a, b;
    for (int i = 1; i < n; ++i) {
        cin >> a >> b;
        e[a].push_back(b); e[b].push_back(a);
        id[i] = {a, b};
    }
    dfs1(1, 0);
    for (auto& x : vis) x = false;
    dfs2(1, 1);
    build(1, cnt, 1);
    for (int i = 1; i < n; ++i) if (dep[id[i].first] < dep[id[i].second]) {
        swap(id[i].first, id[i].second);
    }//调整边的方向，确保first是深度更深的节点（子节点）
    cin >> q;
    while (q--) {
        cin >> op >> a;
        if (3 == op) {
            cin >> b;
            const int t = search(a, b, false);
            if (t == 0) cout << -1 << '\n';
            else cout << search(a, b, true) << '\n';
        } else {
            modify(pos[id[a].first], op == 1 ? 1 : 0, 1, cnt, 1);
        }
    }
    return 0;
}