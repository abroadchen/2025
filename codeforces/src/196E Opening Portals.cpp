//
// Created by Psy.C on 2025/12/3.
//
/*
*n: 节点数
m: 边数
fa[N]: 并查集父节点数组
id[N]: 边的索引数组
k: 特殊节点数
a[N]: 存储特殊节点
p[N]: 记录每个节点属于哪个特殊节点的集合
 *
 *
*获取边两端点所属的特殊节点集合
计算边的权重（考虑到特殊节点的距离）
查找两个集合的根节点
 *如果两个节点属于不同集合，合并集合并累加权重
 *加上节点1到最近特殊节点的距离
 *
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int,int>
#define li pair<ll,int>
using namespace std;

constexpr int N = 1e5+7;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, fa[N], id[N], k, a[N], p[N];
ll d[N];//每个节点到最近特殊节点的最短距离
pair<ii,int> e[N];//((起点,终点),权重)
vector<li> g[N];//相邻节点及边权重

int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
    fast;
    for (auto& i : d) i = inf;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1, x, y, w; i <= m; ++i) {
        cin >> x >> y >> w;
        e[i].first.first = x, e[i].first.second = y, e[i].second = w;
        g[x].emplace_back(w,y);
        g[y].emplace_back(w,x);
        id[i] = i;
    }
    cin >> k;
    priority_queue<li, vector<li>, greater<>> q;//小顶堆优先队列，用于Dijkstra算法
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
        p[a[i]] = a[i];//记录每个特殊节点属于自己的集合
        d[a[i]] = 0;//特殊节点的距离为0
        q.emplace(0, a[i]);
    }
    while (!q.empty()) {
        const int u = q.top().second;
        const ll dis = q.top().first; q.pop();//取出距离最小的节点
        if (dis > d[u]) continue;//如果该节点已经被更新过
        for (auto& v : g[u]) {//遍历当前节点的所有邻接节点
            if (dis + v.first < d[v.second]) {//如果找到更短路径，更新距离和所属集合，并加入队列
                d[v.second] = dis + v.first;
                p[v.second] = p[u];
                q.emplace(d[v.second], v.second);
            }
        }
    }
    ll ans = 0;//排序键值 = 起点到特殊节点距离 + 终点到特殊节点距离 + 边权重
    sort(id + 1, id + 1 + m, [](const int& a, const int& b) {
        return d[e[a].first.first] + d[e[a].first.second] + e[a].second <
            d[e[b].first.first] + d[e[b].first.second] + e[b].second;
    });
    for (int i = 1; i <= m; ++i) {//遍历排序后的边
        const int u = p[e[id[i]].first.first], v = p[e[id[i]].first.second];
        const ll w = e[id[i]].second + d[e[id[i]].first.first] + d[e[id[i]].first.second];
        const int x = find(u), y = find(v);
        if (x != y) { fa[y] = x; ans += w; }
    }
    ans += d[1];
    cout << ans << '\n';
    return 0;
}