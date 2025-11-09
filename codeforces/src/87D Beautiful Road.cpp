//
// Created by Psy.C on 2025/11/8.
//
/*
*N: 最大节点数
n: 节点数量
p[N]: 并查集父节点数组
sz[N]: 并查集中每个集合的大小
szx[N]: 临时大小数组
cnt[N]: DFS计数数组
sm: 当前连通分量大小
mark[N]: 标记数组
ans[N]: 存储每条边的答案
 *
*edges: 存储边信息，格式为{{权重,索引},{端点1,端点2}}
adj[N]: 邻接表，存储图结构
ca: 存储当前批次的边信息
 *
*并查集操作：
find: 路径压缩的查找函数
merge: 按秩合并的合并函数
 *
*深度优先搜索函数：
标记节点v已访问，初始化计数为szx[v]
遍历v的所有邻居u：
如果u未访问，递归DFS并累加计数
如果不是根节点（j != -1），计算边j的贡献值
 *
*按权重分批处理边：
获取当前权重w
处理所有权重为w的边：
记录边信息到ca
在邻接表中添加边
设置临时大小szx
 *合并当前批次所有边连接的节点
 *对当前批次每条边的端点进行DFS计算贡献
 *清理临时数据，为下一批边做准备
*找到最大答案值
收集所有达到最大值的边
输出最大值和边的数量，以及边的编号
 *
*iota(p, p + n, 0) 的作用是：
将数组p的前n个元素依次赋值为：0, 1, 2, 3, ..., n-1
 *
 *
 *时间复杂度约为O(n log n + nα(n))，其中α是阿克曼函数的反函数
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long int ll;
typedef pair<int, int> pii;
const int N = 1e5+5;
int n, p[N], sz[N], szx[N], cnt[N], sm;
bool mark[N];
ll ans[N];

vector<pair<pii, pii>> edges;
vector<pii> adj[N];
vector<pair<int, pii>> ca;

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    p[a] = b; sz[b] += sz[a]; sz[a] = 0;
}

void dfs(int v, int j=-1) {
    mark[v] = 1; cnt[v] = szx[v];
    for (auto x : adj[v]) {
        int u = x.first, i = x.second;
        if (!mark[u]) { dfs(u, i); cnt[v] += cnt[u]; }
    }
    if (j != -1) ans[j] = 2ll * cnt[v] * (sm - cnt[v]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        edges.push_back({{w, i}, {u, v}});
    }
    sort(edges.begin(), edges.end());
    iota(p, p + n, 0); fill(sz, sz + n, 1);
    int j = 0;
    while (j < n - 1) {
        int w = edges[j].first.first;
        while (j < n - 1 && edges[j].first.first == w) {
            int i = edges[j].first.second,
            u = find(edges[j].second.first),
            v = find(edges[j].second.second);
            ca.push_back({i, {u, v}});
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            szx[u] = sz[u]; szx[v] = sz[v];
            j++;
        }
        for (auto x : ca) {
            int i = x.first, u = x.second.first, v = x.second.second;
            merge(u, v);
        }
        for (auto x : ca) {
            for (int u : {x.second.first, x.second.second}) {
                if (!mark[u]) { sm = sz[find(u)]; dfs(u); }
            }
        }
        for (auto x : ca) {
            int i = x.first, u = x.second.first, v = x.second.second;
            mark[u] = 0; mark[v] = 0;
            cnt[u] = 0; cnt[v] = 0; szx[u] = 0; szx[v] = 0;
            adj[u].clear(); adj[v].clear();
        }
        ca.clear();
    }

    ll mx = *max_element(ans, ans + (n - 1));
    vector<int> res;
    for (int i = 0; i < n - 1; ++i) if (ans[i] == mx) res.push_back(i);
    cout << mx << ' ' << (ll)(res.size()) << '\n';
    for (int i : res) cout << i + 1 << ' ';
    cout << '\n';
    return 0;
}