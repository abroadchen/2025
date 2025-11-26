//
// Created by Psy.C on 2025/11/26.
//
/*
*定义常量N=1000007（数组大小）
定义常量inf=1000000（权重上限）
*n: 节点数
m: 边数
fa[N]: 并查集父节点数组
idx: 时间戳计数器
ans[N]: 答案数组（存储每条边的重要性）
dfn[N]: DFS访问时间戳
low[N]: 节点能到达的最早时间戳
*定义边结构体：
a, b: 边的两个端点
id: 边的编号
tmp1, tmp2: 临时变量（用于存储并查集根节点）
*vc[N]: 按权重分组存储边的向量
g[N]: 图的邻接表表示
f[N]: 标记数组（标记桥边）
*Tarjan算法求桥边：
u: 当前节点
id: 父边ID（避免走回头路）
dfn[u] = low[u] = ++idx: 初始化时间戳
遍历u的所有邻边：
跳过父边
如果邻节点未访问：递归访问，更新low值，判断是否为桥
如果邻节点已访问：更新low值
 *
*按权重从小到大处理每组边
如果该权重没有边则跳过
重置时间戳计数器
*计算每条边两端点在并查集中的根节点
确保tmp1 ≤ tmp2（标准化表示）
*处理每条边：
如果两端点在同一连通分量：边冗余（ans=3）
否则：清空相关节点的邻接表和时间戳
 *构建当前权重下的子图（只包含跨连通分量的边）
 *对子图运行Tarjan算法找桥边
*标记边的重要性：
桥边：重要性为1（any）
非桥边：重要性为2（at least one）
 *合并边连接的连通分量
 *
 *时间复杂度：O(M log N + M + N)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define sz(x) (static_cast<int>(x.size()))
using namespace std;

typedef pair<int,int> ii;
constexpr int N = 1e6+7, inf = 1e6;
int n, m, fa[N], idx, ans[N], dfn[N], low[N];
struct edge { int a, b, id, tmp1, tmp2; };
vector<edge> vc[N];
vector<ii> g[N];
bool f[N];

int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void tarjan(const int u, const int id) {
    dfn[u] = low[u] = ++idx;
    for (const auto& e : g[u]) {
        if (e.second == id) continue;
        if (!dfn[e.first]) {
            tarjan(e.first, e.second);
            low[u] = min(low[u], low[e.first]);
            if (dfn[u] < low[e.first]) f[e.second] = true;
        } else low[u] = min(low[u], dfn[e.first]);
    }
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n) fa[i] = i;
    rep(i,m) {
        int a, b, w; cin >> a >> b >> w;
        vc[w].push_back({a, b, i, 0, 0});
    }
    rep(i,inf) {
        if (!sz(vc[i])) continue; idx = 0;
        for (auto& e : vc[i]) {
            e.tmp1 = find(e.a); e.tmp2 = find(e.b);
            if (e.tmp1 > e.tmp2) swap(e.tmp1, e.tmp2);
        }
        for (const auto& e : vc[i]) {
            if (e.tmp1 == e.tmp2) ans[e.id] = 3;
            else {
                g[e.tmp1].clear(); g[e.tmp2].clear();
                dfn[e.tmp1] = dfn[e.tmp2] = 0;
            }
        }
        for (auto& e : vc[i]) {
            if (e.tmp1 != e.tmp2) {
                g[e.tmp1].emplace_back(e.tmp2, e.id);
                g[e.tmp2].emplace_back(e.tmp1, e.id);
            }
        }
        for (const auto& e : vc[i]) {//不会修改循环中的元素
            if (e.tmp1 != e.tmp2) {
                if (!dfn[e.tmp1]) tarjan(e.tmp1, 0);
                if (!dfn[e.tmp2]) tarjan(e.tmp2, 0);
            }
        }
        for (const auto& e : vc[i]) {
            if (e.tmp1 != e.tmp2) {
                if (f[e.id]) ans[e.id] = 1;
                else ans[e.id] = 2;
            }
        }
        for (const auto& e : vc[i]) {
            const int x = find(e.a), y = find(e.b);
            if (x != y) fa[x] = y;
        }
    }
    rep(i,m) {
        if (ans[i] == 1) cout << "any" << '\n';
        else if (ans[i] == 2) cout << "at least one" << '\n';
        else cout << "none" << '\n';
    }
    return 0;
}