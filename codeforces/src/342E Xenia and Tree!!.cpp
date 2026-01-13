//
// Created by Psy.C on 2026/1/13.
//
/**
* siz[u]：以u为根的子树大小
fa[u]：u的父节点
dep[u]：u的深度
son[u]：u的重儿子（子树最大的儿子）
构建重链剖分，预处理树的结构
 *
*top[u]：u所在重链的顶端节点
构建重链，将树分解为多条重链
 *
*计算u和v之间的距离：dep[u] + dep[v] - 2*dep[lca(u,v)]
使用树链剖分快速找到最近公共祖先(LCA)
 *
 *len：分块大小，使用 sqrt(n*log(n)) 优化
 *构建无向树
*DFS预处理
mn[i]：节点i到最近激活点的最短距离
初始化为深度（到根的距离）
*op[i]：操作类型（1激活点，2查询距离）
nd[i]：操作的节点
id[i]：第i个操作所属的块编号
*当进入新块时，对上一块的激活点进行BFS
更新每个节点到激活点的最短距离
*查询操作：当前块内最新激活点的查询
使用预处理结果和当前块内的激活点共同计算最短距离
 *
 *vector<int> g[N]：邻接表存储树的结构
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

template<typename T>//不仅返回最小值还会更新原变量
bool minn(T& x, const T& y) { return x > y ? x = y, true : false; }


int siz[N], fa[N], dep[N], son[N];
vector<int> g[N];
void dfs(const int u) {//以u为根进行DFS
    siz[u] = 1;//包含自身
    for (const int v : g[u]) {
        if (fa[u] == v) continue;
        fa[v] = u, dep[v] = dep[u] + 1;//设置v的父节点和深度
        dfs(v);//递归遍历子节点
        siz[u] += siz[v];//累加子树大小
        if (siz[son[u]] < siz[v]) son[u] = v;//更新重儿子
    }
}

int top[N];
void dfs2(const int u) {
    if (son[u]) top[son[u]] = top[u], dfs2(son[u]);//如果u有重儿子，重儿子的顶端节点与u相同
    for (const int v : g[u]) if (!top[v]) {//遍历轻儿子
        top[v] = v, dfs2(v);//轻儿子开始新的重链
    }
}

int get(int u, int v) {
    const int res = dep[u] + dep[v];
    while (top[u] != top[v]) {//两个节点不在同一条重链上时
        if (dep[top[u]] < dep[top[v]]) swap(u, v);//将深度大的节点向上移动
        u = fa[top[u]];//跳到当前重链顶端的父节点
    }
    if (dep[u] > dep[v]) swap(u, v);//确保u是LCA
    return res - (dep[u]<<1);
}


int main() {
    fast;
    int n, m; cin >> n >> m;
    const int len = static_cast<int>(sqrt(n * log(n) / log(2)));
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    int mn[N];
    dfs(1), memcpy(mn + 1, dep + 1, n * sizeof(int));//复制深度数组
    top[1] = 1, dfs2(1);//根节点的顶端节点是自己
    int op[N], nd[N], id[N], dis[N];
    for (int i = 1; i <= m; ++i) cin >> op[i] >> nd[i];
    id[0] = 1;
    for (int i = 1; i <= m; ++i) id[i] = (i - 1) / len + 1;//计算操作i所属的块编号
    queue<int> q;
    for (int i = 1; i <= m; ++i) {
        if (id[i] != id[i-1]) {//当进入新块时执行
            memset(dis + 1, 0x3f, n * sizeof(int));
            for (int j = i - len; j < i; ++j) if (op[j] == 1) {//处理上一块的激活操作
                q.push(nd[j]), dis[nd[j]] = 0;//将激活点加入队列，距离设为0
            }
            while (!q.empty()) {//更新到各点的最短距离
                const int u = q.front(); q.pop();
                for (int v : g[u]) if (minn(dis[v], dis[u] + 1)) {
                    q.push(v);
                }
            }
            for (int j = 1; j <= n; ++j) minn(mn[j], dis[j]);//更新全局最短距离
        }
        if (op[i] == 2) {
            int ans = mn[nd[i]];//初始化答案为预处理的结果
            for (int j = i - 1; j && id[j] == id[i]; --j) if (op[j] == 1) {//遍历当前块内的激活操作
                minn(ans, get(nd[j], nd[i]));//考虑当前块内激活点的影响
            }
            cout << ans << '\n';
        }
    }
    return 0;
}