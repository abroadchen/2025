//
// Created by Psy.C on 2025/12/16.
//
/*
*定义边结构体，包含目标节点(to)和下一条边的索引(nxt)
e[N<<1]：边数组，大小为2*N（因为是无向图）
head[N]：每个节点的第一条边索引
cnt：边的计数器
add函数：添加无向边(u,v)，使用链式前向星存储
 *
*siz[N]：子树大小
son[N]：重儿子（子树最大的儿子）
fa[N]：父节点
dep[N]：节点深度
DFS函数计算树的基本信息
*遍历u的所有邻居
如果不是父节点：
设置父子关系和深度
递归处理子节点
更新重儿子（子树最大的儿子）
累加子树大小

*name[N][22]：存储节点名称
s[N<<1]：按深度分类的名称集合
vis[N]：访问标记数组
dfs3函数：
如果c>0：将当前节点名称按深度插入对应集合
如果c≤0：清空对应深度的集合
递归处理未访问的子节点
 *
*node结构体：存储查询索引和深度
ex[N]：每个节点的查询列表
ans[N]：查询结果数组
 *
*DSU on Tree算法的核心
先递归处理轻儿子，处理完后清理信息(f=1)
 *递归处理重儿子，保留信息(f=0)，标记为已访问
*收集当前子树的信息
处理u节点上的所有查询
*取消重儿子的访问标记
如果需要清理(f=1)，则清空相关信息
 *
 *查询(x,y)表示询问节点x的子树中深度为dep[x]+y的节点数
 *
 *时间复杂度：O(n log n)
 */
#include <iostream>
#include <set>
#include <cstring>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;

struct edge { int to, nxt; } e[N<<1];
int cnt, head[N];
void add(const int u, const int v) {
    e[cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt++;
    e[cnt].to = u; e[cnt].nxt = head[v]; head[v] = cnt++;
}

int siz[N], son[N], fa[N], dep[N];
void dfs(const int u) {
    siz[u] = 1; son[u] = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u]) {
            fa[e[i].to] = u;
            dep[e[i].to] = dep[u] + 1;
            dfs(e[i].to);
            if (siz[e[i].to] > siz[son[u]]) son[u] = e[i].to;
            siz[u] += siz[e[i].to];
        }
    }
}

char name[N][22];
set<string> s[N<<1];
int vis[N];
void dfs3(const int u, const int c) {
    if (c > 0) s[dep[u]].insert(name[u]); else s[dep[u]].clear();
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u] && !vis[e[i].to])
            dfs3(e[i].to, c);
    }
}

struct node { int x, c; };
vector<node> ex[N];
int ans[N];
void dfs2(const int u, const int f) {
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u] && e[i].to != son[u])
            dfs2(e[i].to, 1);
    }
    if (son[u]) { dfs2(son[u], 0); vis[son[u]] = 1; }
    dfs3(u, 1);
    const int sz = static_cast<int>(ex[u].size());
    for (int i = 0; i < sz; ++i)
        ans[ex[u][i].x] = static_cast<int>(s[ex[u][i].c].size());
    if (son[u]) vis[son[u]] = 0;
    if (f) dfs3(u, -1);
}

int main() {
    fast;
    int n; cin>>n;
    memset(head, -1, sizeof(head)); cnt = 0;
    for (int i = 1, x; i <= n; ++i) {
        cin >> name[i] >> x; add(i, x);
    }
    dfs(0);
    int m; cin>>m;

    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        ex[x].push_back({i, dep[x] + y});
    }
    dfs2(0, 0);
    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
    return 0;
}