//
// Created by Psy.C on 2026/1/30.
//
/**
 * N表示节点数上限，Q表示查询数上限，M表示边数上限
 *
*获取边在向量中的索引
如果第一个端点大于第二个端点则交换（保证边的方向统一）
使用lower_bound查找边在排序后的向量中的位置
 *
*ds[N]：存储节点状态（是否被激活）
es[M]：存储边的状态（是否存在）
fs[N]：存储节点的辅助值
 *
*修改节点u的状态
将节点u的状态设为st
计算变化量dt（状态从0变1则+1，从1变0则-1）
遍历u的所有邻居，如果边存在则更新邻居的辅助值
 *
*修改边(u,v)的存在状态
获取边的索引并设置边的状态
如果u的度数大于v，则交换它们（优化策略）
如果u节点处于激活状态，则更新v的辅助值
 *
*查询节点u的值
初始值为fs[u]
遍历u的所有邻居，如果边存在则加上邻居节点的状态值
 *
*m：初始边的数量
ua[M], ub[M]：存储边的两个端点
on：激活节点数量
fo[N]：存储初始激活的节点
nq：查询数量
qa[Q], qb[Q]：存储查询参数
 *
*对边向量进行排序并去重
统计每个节点的度数
构建邻接表，总是将度数小的节点连接到度数大的节点
设置初始边的状态
激活初始节点
执行查询序列：
'O'操作：激活节点
'F'操作：关闭节点
'A'操作：添加边
'D'操作：删除边
'?'操作：查询节点值
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 55555, Q = 255555, M = 401000;

vector<ii> e;
int get(ii z) {
    if (z.first > z.second) swap(z.first, z.second);
    return static_cast<int>(ranges::lower_bound(e, z) - e.begin());
}

int ds[N], es[M], fs[N];
vector<ii> g[N];//邻接表，每个节点存储与之相连的邻居节点及对应边的索引
void modify(const int u, const int st) {
    ds[u] = st;
    const int dt = st == 1 ? 1 : -1;
    for (auto &[fst, snd] : g[u]) {
        const int v = fst;
        if (const int id = snd; !es[id]) continue;
        fs[v] += dt;
    }
}

int deg[N];//每个节点的度数
void modify(int u, int v, const int st) {
    const int id = get({u, v});
    es[id] = st;
    if (deg[u] > deg[v]) swap(u, v);
    if (ds[u] == 1) fs[v] += st == 1 ? 1 : -1;
}

int query(const int u) {
    int ret = fs[u];
    for (auto &[fst, snd] : g[u]) {
        const int v = fst;
        if (const int id = snd; es[id] == 0) continue;
        ret += ds[v];
    }
    return ret;
}

char op[Q];//操作类型的数组
int m, ua[M], ub[M], on, fo[N], nq, qa[Q], qb[Q];
void solve() {
    ranges::sort(e);
    e.erase(ranges::unique(e).begin(), e.end());
    const int sz = static_cast<int>(e.size());
    for (int i = 0; i < sz; ++i) {
        deg[e[i].first]++; deg[e[i].second]++;
    }
    for (int i = 0; i < sz; ++i) {
        int u = e[i].first, v = e[i].second;
        if (deg[u] > deg[v]) swap(u, v);
        g[u].emplace_back(v, i);
    }
    for (int i = 0; i < m; ++i) {
        const int id = get({ua[i], ub[i]});
        es[id] = 1;
    }
    for (int i = 0; i < on; ++i) modify(fo[i], 1);
    for (int i = 0; i < nq; ++i) {
        const int u = qa[i], v = qb[i];
        if (op[i] == 'O') modify(u, 1);
        else if (op[i] == 'F') modify(u, 0);
        else if (op[i] == 'A') modify(u, v, 1);
        else if (op[i] == 'D') modify(u, v, 0);
        else cout << query(u) << '\n';
    }
}

int main() {
    fast;
    int n; cin >> n >> m >> nq;
    cin >> on;
    for (int i = 0; i < on; ++i) { cin >> fo[i]; fo[i]--; }
    for (int i = 0; i < m; ++i) {
        cin >> ua[i] >> ub[i]; ua[i]--; ub[i]--;
        if (ua[i] > ub[i]) swap(ua[i], ub[i]);
        e.emplace_back(ua[i], ub[i]);
    }
    for (int i = 0; i < nq; ++i) {
        char s[3]; cin >> s;
        op[i] = s[0];
        if (op[i] == 'A' || op[i] == 'D') {
            cin >> qa[i] >> qb[i]; qa[i]--; qb[i]--;
            if (qa[i] > qb[i]) swap(qa[i], qb[i]);
            e.emplace_back(qa[i], qb[i]);
        } else {
            cin >> qa[i]; qa[i]--;
        }
    }
    solve();
    return 0;
}