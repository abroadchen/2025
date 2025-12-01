//
// Created by Psy.C on 2025/11/30.
//
/*
*N：最大节点数常量
n, m：节点数和边数
g[N]：原图的邻接表，存储pair(目标节点, 边的编号)
g2[N]：缩点后的图的邻接表
 *
*cnt：时间戳计数器
dfn[N]：节点的DFS访问时间戳
low[N]：节点能回溯到的最小时间戳
sum：强连通分量计数器
bl[N]：节点所属的强连通分量编号
st：Tarjan算法使用的栈
 *
*为当前节点设置时间戳
将节点压入栈中
遍历所有邻接节点：
跳过反向边（i.second == (e^1)）
如果未访问过，递归处理并更新low值
如果已访问过，用dfn值更新low值
如果low值等于dfn值，说明找到了一个强连通分量
从栈中弹出节点直到当前节点，标记为同一SCC
 *
*dep[N]：节点深度
f[N][32]：倍增数组，f[x][i]表示节点x的2^i级祖先
 *
*设置当前节点深度
构建倍增数组（动态规划）：f[x][i] = f[f[x][i-1]][i-1]
遍历子节点，设置父节点关系并递归处理
 *
*确保x更深，如果不是则交换
将x向上跳到与y同一深度
如果此时x==y，返回结果
同时将x和y向上跳，直到它们的父节点相同
返回最近公共祖先
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 1e5+5;
int n, m;
vector<pair<int, int>> g[N];
vector<int> g2[N];

int cnt, dfn[N], low[N], sum, bl[N];
stack<int> st;
void tarjan(const int x, const int e) {
    ++cnt;
    dfn[x] = low[x] = cnt;
    st.push(x);
    for (const auto i : g[x]) {
        if (i.second == (e^1)) continue;
        if (!dfn[i.first]) tarjan(i.first, i.second),
            low[x] = min(low[x], low[i.first]);
        else low[x] = min(low[x], dfn[i.first]);
    }
    if (low[x] == dfn[x]) {
        int t; sum++;
        do {
            t = st.top(); st.pop();
            bl[t] = sum;
        } while (t != x);
    }
}

int dep[N], f[N][32];
void dfs(const int x, const int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 1; (1<<i) <= dep[x]; ++i)
        f[x][i] = f[f[x][i-1]][i-1];
    for (const auto i : g2[x]) {
        if (i == fa) continue;
        f[i][0] = x;
        dfs(i, x);
    }
}

int query(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = __lg(n); i >= 0; --i)
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = __lg(n); i >= 0; --i)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,m) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v, i<<1); g[v].emplace_back(u, i<<1|1);
    }
    rep(i,n) if (!dfn[i]) tarjan(i, 0);//对所有未访问节点运行Tarjan算法求强连通分量
    rep(i,n) for (const auto j : g[i]) if (bl[i] != bl[j.first]) {
        g2[bl[i]].push_back(bl[j.first]);//构建缩点后的图：如果两点不在同一SCC中，则在对应的SCC间连边
    }
    dfs(1, 0);
    int k; cin >> k;
    while (k--) {
        int u, v; cin >> u >> v;
        if (bl[u] == bl[v]) { cout << "0\n"; continue; }//如果u,v在同一SCC中，距离为0
        const int lca = query(bl[u], bl[v]);//所在SCC的LCA
        cout << dep[bl[u]] + dep[bl[v]] - 2 * dep[lca] << '\n';//树上距离
    }
    return 0;
}