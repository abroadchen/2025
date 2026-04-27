//
// Created by Psy.C on 2026/4/27.
//
/**
cnt: 缩点后的连通块计数
c[N]: 每个节点的颜色值
bel[N]: 节点所属的连通块编号
g[N]: 缩点后每个连通块包含的原始节点
G[N]: 缩点后形成的新的图
e[N]: 原始图的邻接表
vis[N]: 访问标记数组
使用BFS构建颜色相同的连通块
从起始节点st开始，找到所有颜色相同且相连的节点
将这些节点归为一个连通块，编号为cnt
从起点st开始进行BFS，找到距离最远的节点
返回距离起点最远的节点编号
这个函数用于计算树的直径

遍历所有未访问的节点
对颜色相同的连通区域进行缩点
遍历每个连通块
如果两个相邻节点属于不同的连通块，则在新图中添加边
形成缩点后的新图G
两次BFS计算树的直径:
第一次从节点1出发，找到距离最远的点x
第二次从x出发，找到距离x最远的点y
x到y的距离就是树的直径
输出(直径+1)/2，即树的半径
时间复杂度为O(n)，适用于大规模数据
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e6+7;

int cnt, c[N], bel[N];
vector<int> g[N], G[N], e[N];
bool vis[N];
void build(int st) {
    cnt++;
    g[cnt].push_back(st);
    queue<int> q; q.push(st);
    int cur = c[st]; vis[st] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        bel[u] = cnt;
        for (auto v : e[u]) {
            if (vis[v] || c[v] != cur) continue;
            vis[v] = true;
            g[cnt].push_back(v);
            q.push(v);
        }
    }
}

int dis[N];
int bfs(int st) {
    queue<int> q; q.push(st);
    memset(dis, 0, sizeof dis);
    memset(vis, 0, sizeof vis);
    dis[st] = 0; vis[st] = true;
    int ed = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : G[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            dis[v] = dis[u] + 1;
            q.push(v);
            ed = v;
        }
    }
    return ed;
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) build(i);
    for (int i = 1; i <= cnt; ++i) {
        for (auto u : g[i])
            for (auto v : e[u])
                if (bel[u] != bel[v]) {
                    G[bel[u]].push_back(bel[v]);
                    G[bel[v]].push_back(bel[u]);
                }
    }
    int x = bfs(1), y = bfs(x);
    cout << (dis[y]+1)/2 << '\n';
    return 0;
}