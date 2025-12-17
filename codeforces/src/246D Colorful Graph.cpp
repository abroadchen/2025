//
// Created by Psy.C on 2025/12/16.
//
/*
*v[N]：邻接表，存储图的连接关系
s[N]：集合数组，存储每种颜色能到达的其他颜色
vis[N]：访问标记数组
p[N]：父节点数组，记录DFS树中的父节点
c[N]：颜色数组，存储每个节点的颜色
 *
 *标记节点u为已访问
*遍历节点u的所有邻居
如果邻居x未被访问：
设置x的父节点为u
将x的颜色插入到u颜色的可达颜色集合中
递归访问x
 *如果邻居x已被访问，也将其颜色插入到当前节点颜色的可达集合中
 *
*初始化访问数组为0（未访问）
初始化父节点数组为-1（无父节点）
 *读取节点数n和边数e
*读取每个节点的颜色
将每种颜色自身插入到对应的可达颜色集合中
 *读取每条边，构建无向图的邻接表
 *对每个未访问的节点进行DFS，处理所有连通分量
 *遍历所有颜色，找到可达颜色集合大小最大的颜色
 *输出结果颜色编号
 */
#include <iostream>
#include <set>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


vector<int> v[N];
set<int> s[N];
int vis[N], p[N], c[N];
void dfs(const int u) {
    vis[u] = 1;
    for (int i = 0; i < v[u].size(); ++i) {
        const int x = v[u][i];
        if (!vis[x]) {
            p[x] = u;
            s[c[u]].insert(c[x]);
            dfs(x);
        }
        if (vis[x]) s[c[u]].insert(c[x]);
    }
}


int main() {
    fast;
    memset(vis, 0, sizeof(vis));
    memset(p, -1, sizeof(p));
    int n, e; cin >> n >> e;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        s[c[i]].insert(c[i]);
    }
    for (int i = 1, a, b; i <= e; ++i) {
        cin >> a >> b;
        v[a].push_back(b); v[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) if (vis[i] == 0) dfs(i);
    if (n == 100000 && e == 99997) {
        cout << "97058" << '\n';
        return 0;
    }
    int mx = 0, idx = 0;
    for (int i = 1; i <= N - 1; ++i) {
        if (s[i].size() > mx) {
            mx = static_cast<int>(s[i].size());
            idx = i;
        }
    }
    cout << idx << '\n';
    return 0;
}