//
// Created by Psy.C on 2026/2/26.
//
/**
n：节点数
m：边数
x[N], y[N]：查询的节点对
ans[N]：查询结果数组
v[i]存储权重为i的所有边
mp[{a,b}]存储所有询问节点对(a,b)的查询编号
num[i]存储属于并查集集合i的所有节点

确保x[i] ≤ y[i]（标准化）
将查询按节点对分类存储到map中
阈值s = √m，用于区分大小边集的处理策略
按权重从小到大处理每种边
如果当前权重的边数较少（≤√m）
处理这些边：
将涉及的节点收集到st中
在并查集中合并节点a和b
去重排序st中的节点
将每个节点按其所属集合分组存储到num中
统计同一集合内节点对的查询：
遍历每个集合的所有节点对
如果该节点对在查询中存在，增加对应查询的计数
清理临时数据，恢复并查集初始状态

如果当前权重的边数较多（>√m）
直接处理所有边，合并节点
对所有查询检查两个节点是否在同一集合中
恢复并查集初始状态

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1;
int fa[N];
inline int find(const int& x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, m, x[N], y[N], ans[N];
vector<ii> v[N];
map<ii, vector<int>> mp;
vector<int> num[N];
int main() {
    fast; cin >> n >> m;
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c;
        v[c].push_back({a, b});
    }
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> x[i] >> y[i];
        if (x[i] > y[i]) swap(x[i], y[i]);
        mp[{x[i], y[i]}].push_back(i);
    }
    const int s = sqrt(m);
    for (int i = 1; i <= m; ++i) {
        if (v[i].size() <= s) {
            vector<int> st;
            for (auto [a, b] : v[i])
                st.push_back(a), st.push_back(b), fa[find(a)] = find(b);
            ranges::sort(st);
            st.erase(ranges::unique(st).begin(), st.end());
            for (auto j : st) num[find(j)].push_back(j);
            for (auto u : st) if (find(u) == u) {
                for (int j = 0; j < num[u].size(); ++j)
                    for (int k = j + 1; k < num[u].size(); ++k) {
                        int a = num[u][j], b = num[u][k];
                        if (a > b) swap(a, b);
                        if (mp.contains({a, b}))
                            for (const auto it : mp[{a, b}])
                                ++ans[it];
                    }
            }
            for (const auto j : st) num[j].clear(), fa[j] = j;
        } else {
            for (auto [a, b] : v[i]) fa[find(a)] = find(b);
            for (int j = 1; j <= q; ++j) ans[j] += find(x[j]) == find(y[j]);
            for (int j = 1; j <= n; ++j) fa[j] = j;
        }
    }
    for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
    return 0;
}