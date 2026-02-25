//
// Created by Psy.C on 2026/2/25.
//
/**
e[color][u]存储颜色为color的边中，与节点u相连的所有节点
第一维：边的颜色（权重）
第二维：起始节点
第三维：相邻节点列表

取出队首节点u
如果u就是目标节点y，返回true
弹出队首元素
遍历u的所有邻居：
如果v已访问过，跳过
标记v为已访问
将v加入队列
如果队列为空仍未找到y，返回false
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
vector<int> e[N][N];
bool vis[N];
void add(const int u, const int v, const int w) {
    e[w][u].push_back(v);
    e[w][v].push_back(u);
}

int x, y;///查询的起点和终点
bool bfs(const int c) {//在颜色c的子图中x和y是否连通
    memset(vis, false, sizeof(vis));
    queue<int> q; q.push(x);
    while (!q.empty()) {
        const int u = q.front();
        if (u == y) return true; q.pop();
        for (int i = 0; i < e[c][u].size(); ++i) {
            int v = e[c][u][i];
            if (vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }
    return false;
}


int n, m, q;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) e[i][j].clear();
    for (int i = 0, c; i < m; ++i) {
        cin >> x >> y >> c; add(x, y, c);
    }
    cin >> q;
    while (q--) {
        int ans = 0;//满足条件的颜色数量
        cin >> x >> y;
        for (int i = 1; i <= m; ++i)
            if (bfs(i)) ans++;
        cout << ans << '\n';
    }
    return 0;
}