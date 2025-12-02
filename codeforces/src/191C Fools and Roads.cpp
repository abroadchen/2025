//
// Created by Psy.C on 2025/12/2.
//
/*
*N: 节点数量上限（100010）
M: 边数量上限（200010）
*n: 节点数
m: 查询数
 *line结构体表示边，包含两个端点x和y，并声明数组l存储所有边
*dge结构体表示邻接表中的边：
v: 邻接点
nxt: 下一条边的索引
*cnt: 边计数器
head[N]: 邻接表头数组
*添加从u到v的有向边：
cnt自增，e[cnt].v设为v
e[cnt].nxt指向原来的head[u]
head[u]更新为cnt
*dep[N]: 存储每个节点的深度
fa[N][25]: 倍增数组，fa[u][i]表示节点u的第2^i个祖先
 *
 *dfs函数，用于预处理树的信息
 *设置节点u的深度为父节点pre的深度加1
 *设置节点u的直接父节点
 *
 *
*id[N]: 边的标识数组
dif[N]: 差分数组
ans[N]: 答案数组
 *
*fa[u][i-1]：节点 u 的第 2^(i-1) 个祖先
fa[fa[u][i-1]][i-1]：以上述祖先为起点，再向上跳 2^(i-1) 步
*2^i = 2^(i-1) + 2^(i-1)
所以节点 u 的第 2^i 个祖先 = (节点 u 的第 2^(i-1) 个祖先) 的第 2^(i-1) 个祖先
 *
 *O(n log n + m log n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 100010, M = 200010;
int n, m;
struct line { int x, y; } l[N];
struct edge { int v, nxt; } e[M];

int cnt, head[N];
void add(const int u, const int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int dep[N], fa[N][25];
void dfs(const int u, const int pre) {
    dep[u] = dep[pre] + 1;
    fa[u][0] = pre;
    for (int i = 1; (1<<i) <= dep[u]; ++i)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; i; i = e[i].nxt) {
        const int v = e[i].v;
        if (v != pre) dfs(v, u);//如果v不是父节点，则递归处理v
    }
}

int lca(int u, int v) {//求最近公共祖先
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 20; i >= 0; --i) {
        if (dep[u] <= dep[v] - (1<<i)) v = fa[v][i];//将v向上跳到与u同一深度
    }
    if (u == v) return u;//如果u等于v，说明u是v的祖先，直接返回
    for (int i = 20; i >= 0; --i) {//同时向上跳跃寻找LCA
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];//返回最近公共祖先
}

int id[N], dif[N], ans[N];

void sum(const int u) {//计算每条边被多少路径经过
    for (int i = head[u]; i; i = e[i].nxt) {//遍历u的所有子节点
        const int v = e[i].v;
        if (v != fa[u][0]) {//如果v不是父节点，递归处理并累加差分值
            sum(v);
            dif[u] += dif[v];
        }
    }
    ans[id[u]] = dif[u];//将dif[u]的值存入对应边的答案中
}


int main() {
    fast;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> l[i].x >> l[i].y;
        add(l[i].x, l[i].y); add(l[i].y, l[i].x);
    }
    dfs(1, 0);
    for (int i = 1; i < n; ++i) {//为每条边分配ID：指向深度较大节点的边
        if (dep[l[i].x] > dep[l[i].y]) id[l[i].x] = i;
        else id[l[i].y] = i;
    }
    cin >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        const int t = lca(x, y);
        dif[x]++; dif[y]++;
        dif[t] -= 2;
    }
    sum(1);//从根节点开始计算每条边的答案
    for (int i = 1; i < n; ++i) cout << ans[i] << ' ';
    return 0;
}