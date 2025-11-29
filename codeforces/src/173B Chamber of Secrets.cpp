//
// Created by Psy.C on 2025/11/29.
//
/*
*vis[N] 用于标记节点是否被访问过
d[N] 用于存储从终点到各点的最短距离
 *
*从节点n开始搜索（将n视为终点）
标记节点n已访问，距离为0，并将其加入队列
 *
*使用双重循环遍历所有可能的连接关系
对于每一对(i,j)，读入一个字符c
如果c是'#'，表示节点i和节点j+n之间有边：
在i的邻接表中添加j+n
在j+n的邻接表中添加i
这实际上是构建一个二分图，前n个节点代表一种类型，后m个节点代表另一种类型
 *
*如果节点1可达（d[1]不为0），输出从n到1的距离
否则输出"-1"表示不可达
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 1e6+5;
int n, m;
vector<int> e[N];//邻接表，用于表示图的连接关系

int vis[N], d[N];
void bfs() {
    queue<int> q;
    vis[n] = 1; d[n] = 0; q.push(n);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (int i = 0; i < static_cast<int>(e[u].size()); ++i) {
            int v = e[u][i];
            if (!vis[v]) {
                vis[v] = 1; q.push(v);
                d[v] = d[u] + 1;
            }
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) {
        char c; cin >> c;
        if (c == '#') {
            e[i].push_back(j + n);
            e[j + n].push_back(i);
        }
    }
    bfs();
    if (d[1]) cout << d[1] << "\n";
    else cout << "-1\n";
    return 0;
}