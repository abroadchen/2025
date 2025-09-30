//
// Created by Psy.C on 2025/9/29.
//
/*
*定义常量N为905，表示最大节点数
timer: 时间戳计数器，用于Tarjan算法
comp_cnt: 连通分量计数器
g[N]: 原图的邻接表表示
G[N]: 缩点后的图(树)的邻接表表示
tin[N]: 每个节点的访问时间戳
low[N]: 节点能够回溯到的最早时间戳
comp[N]: 每个节点所属的连通分量编号
vis[N]: 访问标记数组
is_leaf[N]: 标记缩点后树中的叶子节点
bridges: 存储桥边的集合
 *
*使用Tarjan算法寻找图中的桥边
u: 当前节点，p: 父节点(默认为-1)
标记当前节点已访问，设置时间戳
遍历u的所有邻接点v
如果v是父节点则跳过
如果v已访问，则用v的时间戳更新u的low值
如果v未访问，递归访问v，然后更新u的low值
如果low[v] > tin[u]，说明(u,v)是桥边，将其加入bridges集合
 *
*在原图中进行DFS，将不属于桥边的边连接的节点标记为同一连通分量
u: 当前节点
将u标记为当前连通分量comp_cnt
遍历u的所有邻接点v
如果v已访问或(u,v)是桥边则跳过
递归访问v
 *
*在缩点后的树中DFS，标记叶子节点并设置时间戳
u: 当前节点，p: 父节点
如果节点度数小于2，则标记为叶子节点
设置节点时间戳
递归访问所有子节点
 *
 *
 *给定一个无向图，找到最少需要添加多少条边才能使图变成边双连通图，并输出这些边
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int N = 905;
int timer(0), comp_cnt(0);
vector<int> g[N], G[N], tin(N), low(N), comp(N, -1);
vector<bool> vis(N), is_leaf(N);
set<pair<int, int> > bridges;

void dfs(int u, int p=-1) {
    vis[u] = true;
    tin[u] = low[u] = timer++;
    for (auto v : g[u]) {
        if (v == p) continue;
        if (vis[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridges.insert({u, v});
                bridges.insert({v, u});
            }
        }
    }
}

void dfs_G(int u) {
    comp[u] = comp_cnt;
    vis[u] = true;
    for (auto v : g[u]) {
        if (vis[v] || bridges.count({u, v})) continue;
        dfs_G(v);
    }
}


void dfs_leaves(int u, int p=-1) {
    if (G[u].size() < 2) is_leaf[u] = true;
    tin[u] = timer++;
    for (auto v : G[u]) {
        if (v == p) continue;
        dfs_leaves(v, u);
    }
}



int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; ++i) {//读取m条边，构建无向图
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (n == 2) {
        cout << -1 << endl;
        return 0;
    }
    dfs(0);
    for (int i = 0; i < n; ++i) vis[i] = false;
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        dfs_G(i);
        comp_cnt++;//统计连通分量数量
    }
    //构建缩点后的图：如果两个节点属于不同连通分量，则在对应的分量间连边
    for (int u = 0; u < n; ++u) {
        for (auto v : g[u]) {
            if (comp[u] == comp[v]) continue;
            int pu = comp[u], pv = comp[v];
            G[pu].push_back(pv);
        }
    }

    timer = 0; int root(0);//初始化timer，选择一个度数>=2的节点作为根
    for (int i = 0; i < comp_cnt; ++i) {
        if (G[i].size() >= 2) {
            root = i;
            break;
        }
    }
    dfs_leaves(root, root);

    vector<int> leaves;//收集所有叶子节点
    for (int i = 0; i < comp_cnt; ++i) {
        if (is_leaf[i])
            leaves.push_back(i);
    }
    if (leaves.size() % 2) leaves.push_back(leaves[0]);//如果叶子节点数为奇数，则复制第一个叶子节点使其变为偶数
    sort(leaves.begin(), leaves.end(), [&](int a, int b) {
        return tin[a] < tin[b];//按照时间戳排序叶子节点
    });
    if (comp_cnt == 1) {//如果只有一个连通分量(无桥)，输出0并结束
        cout << 0 << endl;
        return 0;
    }
    cout << leaves.size() / 2 << endl;//输出需要添加的边数(叶子节点数的一半)

    for (int i = 0; i < leaves.size() / 2; ++i) {//将排序后的叶子节点两两配对
        int comp_u = leaves[i], comp_v = leaves[leaves.size() / 2 + i];
        bool found = false;
        for (int u = 0; u < n; ++u) {//对每一对叶子节点，找到各自连通分量中的任意两个不通过桥边相连的节点
            for (int v = 0; v < n; ++v) {
                if (comp[u] == comp_u && comp[v] == comp_v &&
                    !bridges.count({u, v})) {
                    cout << u + 1 << " " << v + 1 << endl;//输出需要添加的边(将1-based编号转回)
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    return 0;
}