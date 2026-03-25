//
// Created by Psy.C on 2026/3/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pl pair<ll, ll>
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    vector<string> g(n);//原始地图
    for (auto &i : g) cin >> i;//读入每一行的地图数据
    int u[] = {1, -1, 0, 0}, v[] = {0, 0, 1, -1};//下、上、右、左
    vector G(n, vector(m, 0));//连通块编号
    int num = 0;//连通块编号计数器
    vector vis(n, vector<bool>(m));//BFS访问标记
    auto bfs = [&](int x, int y) {//从(x,y)开始遍历连通块
        queue<pl> q;
        G[x][y] = num; //当前位置属于第num号连通块
        q.emplace(x, y);//将起点加入队列
        ll res = 1;//当前连通块大小
        vis[x][y] = true;
        while (!q.empty()) {
            auto [x1, y1] = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {//遍历四个相邻方向
                int dx = x1 + u[i], dy = y1 + v[i];//计算相邻位置
                //检查边界、是否已访问、是否为障碍物
                if (dx < 0 || dy < 0 || dx >= n || dy >= m ||
                    vis[dx][dy] || g[dx][dy] == '*') continue;
                q.emplace(dx, dy);//将新位置加入队列
                vis[dx][dy] = true;
                res++;// 连通块大小加1
                G[dx][dy] = num;//标记该位置属于当前连通块
            }
        }
        return res%10;
    };
    //遍历整个地图，对每个未访问的'.'区域进行BFS，标记连通块
    vector<int> ans(1e6);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (g[i][j] == '.' && !G[i][j]) {//空地且未被标记
                ++num;//新增连通块编号
                ans[num] = bfs(i, j);//计算连通块信息并存储
            }
    //遍历每个'*'位置，计算周围不同连通块的大小之和
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            if (g[i][j] == '*') {//当前位置是障碍物
                int res = 1, f[4]{};//记录已经计算过的连通块编号，避免重复计算
                for (int k = 0; k < 4; ++k) {
                    int dx = i + u[k], dy = j + v[k];
                    if (dx < 0 || dy < 0 || dx >= n || dy >= m ||
                        g[dx][dy] == '*') continue;
                    //检查该连通块是否已经计算过
                    if (G[dx][dy] == f[0] || G[dx][dy] == f[1] ||
                        G[dx][dy] == f[2] || G[dx][dy] == f[3]) continue;
                    f[k] = G[dx][dy];//记录该连通块编号
                    res += ans[G[dx][dy]];//累加该连通块的大小
                }
                cout << res%10;
            } else cout << g[i][j];//不是障碍物，直接输出原字符
        cout << '\n';
    }
    return 0;
}