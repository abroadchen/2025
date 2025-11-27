//
// Created by Psy.C on 2025/11/27.
//
/*
*n: 节点数
m: 边数
w[N]: 存储每个节点的权重值
e[N]和g[N]: 邻接表表示图，e存储正向边，g存储反向边
vi[N]和vs[N]: 布尔数组，用于标记访问状态
 *
*创建队列q
将所有权重为1的节点加入队列并标记已访问
BFS遍历：对于队列中的每个节点u，访问其所有未被访问且权重不为1的邻居节点v
这个过程标记了所有可以从权重为1的节点到达的节点
 *
*从所有权重为2的节点开始搜索
使用反向图g进行遍历
如果遇到权重为1的节点则跳过
标记所有可以从权重为2的节点通过反向边到达的节点
 */
#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 1e5+5;
int n, m, w[N];
vector<int> e[N], g[N];
bool vi[N], vs[N];

void bf() {
    queue<int> q;
    rep(i,n) if (w[i] == 1) { q.push(i); vi[i] = true; }
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (auto v : e[u]) if (!vi[v] && w[v] != 1) {
            vi[v] = true;
            q.push(v);
        }
    }
}

void bs() {
    queue<int> q;
    rep(i,n) if (w[i] == 2) { q.push(i); vs[i] = true; }
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        if (w[u] == 1) continue;
        for (auto v : g[u]) if (!vs[v]) {
            vs[v] = true;
            q.push(v);
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> w[i];
    rep(i,m) {
        int u, v; cin >> u >> v;
        e[u].push_back(v);
        g[v].push_back(u);
    }
    bf(); bs();
    rep(i,n) {
        if (vi[i] && vs[i]) cout << "1" << '\n';
        else cout << "0" << '\n';
    }
    return 0;
}