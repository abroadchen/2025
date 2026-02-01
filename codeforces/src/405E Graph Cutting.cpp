//
// Created by Psy.C on 2026/2/1.
//
/**
* vis[N]：访问标记数组
g[N]：邻接表存储图
q[N]：每个节点的待处理队列
ans：存储三元环结果
 *
*时间复杂度
DFS遍历：O(n + m)
环构造：O(m)（每条边最多参与一次构造）
总体：O(n + m)
空间复杂度
O(n + m)（邻接表、访问数组、队列等）
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
#define ii pair<int, int>
using namespace std;

bool vis[N];
vector<int> g[N];
queue<int> q[N];
vector<pair<int, ii>> ans;
void dfs(const int u, const int fa) {
    vis[u] = true;
    for (const auto& v : g[u]) {
        if (!vis[v]) dfs(v, u);
        else if (v != fa && vis[v]) q[v].push(u);//当前节点加入其队列（形成回边）
    }
    while (q[u].size() >= 2) {
        int x = q[u].front(); q[u].pop();
        int y = q[u].front(); q[u].pop();
        ans.push_back({x, {u, y}});//构造三元环
    }
    if (!q[u].empty()) {
        if (!fa) { cout << "No solution\n"; exit(0); }
        int x = q[u].front(); q[u].pop();
        ans.push_back({x, {u, fa}});//与父节点形成三元环
    } else q[fa].push(u);//将当前节点传递给父节点
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    if (m&1) cout << "No solution\n"; else {
        dfs(1, 0);
        for (auto&[fst, snd] : ans) {//输出所有三元环
            cout << fst << ' ' << snd.first << ' ' << snd.second << '\n';
        }
    }
    return 0;
}