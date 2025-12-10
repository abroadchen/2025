//
// Created by Psy.C on 2025/12/10.
//
/*
*s[N]: 并查集父节点数组
find(x): 查找x的根节点，带路径压缩优化
add(x, y): 合并x和y所在的集合
 *
*g[N]: 原图的邻接表
g2[N]: 缩点后的树的邻接表
fa[N]: 父节点数组
dep[N]: 深度数组
vis[N]: 访问标记数组
 *
*处理环的函数： get
如果x的深度小于y，返回（避免重复处理）
标记y为已访问
从x向上走到y，将路径上的点合并到同一个集合中
 *
*DFS遍历原图：
设置x的父节点为f，深度为dep[f]+1
遍历x的所有邻居y：
如果y是x的父节点，跳过
如果y已经被访问过(dep[y]非0)，调用get处理环
否则递归DFS
 *
*第二次DFS，构建树的信息：
sz[x]: x子树大小
v2[x]: 从根到x路径上被标记的点数
son[x]: x的重儿子
计算子树大小并找出重儿子
 *
*树链剖分的第三次DFS：
top[x]: x所在重链的顶端节点
先处理重儿子，再处理轻儿子
 *
*树链剖分求最近公共祖先(LCA)：
当x和y不在同一重链时，跳转到深度较浅的链顶端
最后在同一链上时，返回深度较小的节点
 *
*v2[x] + v2[y]: 包含了两倍的从根到l路径上的标记点数
- v2[l]: 减去一次从根到l的标记点数
- v2[fa[l]]: 再减去一次从根到fa[l]的标记点数
这样正好得到了从x到y路径上的标记点数
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
#define mod 1000000007
using namespace std;

int s[N];
int find(const int x) { return s[x] ? s[x] = find(s[x]) : x; }
void add(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) s[x] = y;
}

vector<int> g[N], g2[N];
int fa[N], dep[N], vis[N];

void get(int x, const int y) {
    if (dep[x] < dep[y]) return;
    vis[y] = 1;
    for (; x != y; x = fa[x]) add(x, y), vis[x] = 1;
}
void dfs(const int x, const int f) {
    fa[x] = f, dep[x] = dep[f] + 1;
    for (const int y : g[x]) if (y != f) {
        if (dep[y]) get(x, y);
        else dfs(y, x);
    }
}

int sz[N], v2[N], son[N];
void dfs2(const int x, const int f, const int d) {
    sz[x] = 1, fa[x] = f, dep[x] = d, v2[x] = v2[f] + vis[x];
    for (const int y : g2[x]) if (y != f) {
        dfs2(y, x, d + 1), sz[x] += sz[y];
        if (sz[y] > sz[son[x]]) son[x] = y;
    }
}

int top[N];
void dfs3(const int x, const int f) {
    top[x] = f;
    if (son[x]) dfs3(son[x], f);
    for (const int y : g2[x]) if (!top[y]) dfs3(y, y);
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int main() {
    fast;
    int fac[N]; fac[0] = 1;//fac[i] = 2^i % mod
    for (int i = 1; i <= N - 1; ++i) fac[i] = fac[i - 1] * 2 % mod;
    int n, m; cin>>n>>m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin>>u>>v;
        if (u == v) continue;//忽略自环
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, 0); int rt = 1;
    for (int i = 1; i <= n; ++i) if (vis[i]) rt = find(i);//找到一个被标记的节点作为根
    for (int i = 1; i <= n; ++i) {//构建缩点后的树
        for (const int j : g[i]) {
            const int u = find(i), v = find(j);
            if (u != v) g2[u].push_back(v);//如果两端点属于不同集合，连边
        }
    }
    dfs2(rt, 0, 0), dfs3(rt, rt);//树链剖分的预处理
    cin >> m;
    while (m--) {
        int x, y; cin>>x>>y;
        x = find(x), y = find(y);
        const int l = lca(x, y);
        cout << fac[v2[x]+v2[y]-v2[l]-v2[fa[l]]] << '\n';
    }
    return 0;
}