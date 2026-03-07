//
// Created by Psy.C on 2026/3/7.
//
/**
b[N]：记录每个节点属于哪个连通分量
c[N]：记录每个节点的颜色（0或1，用于二分图判断）
cnt：连通分量的数量
a[N]：邻接表，存储无向图
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1001;

ll b[N], c[N], cnt;
vector<ll> a[N];
void dfs(ll x) {
    b[x] = cnt;//标记节点x属于第cnt个连通分量
    for (ll i = 0; i < a[x].size(); ++i) {
        ll t = a[x][i];//获取邻居节点
        //邻居节点未被访问 给邻居节点涂相反颜色 递归访问邻居节点
        if (!b[t]) c[t] = c[x]^1, dfs(t);
        else if (c[t] == c[x]) {//邻居已被访问且颜色相同
            cout << "-1\n";//奇环，不是二分图
            exit(0);
        }
    }
}

ll dis[N];
queue<ll> q;
void bfs(ll x) {
    memset(dis, -1, sizeof dis); dis[x] = 0;//起点距离为0
    q.push(x);//起点入队
    while (!q.empty()) {
        ll t = q.front(); q.pop();
        for (ll i = 0; i < a[t].size(); ++i) {//遍历当前节点的邻居
            ll to = a[t][i];
            if (dis[to] == -1) {//邻居未被访问
                dis[to] = dis[t] + 1;//更新距离
                q.push(to);//邻居入队
            }
        }
    }
}

ll n, m, ans[N];
int main() {
    fast;
    cin >> n >> m;//节点数和边数
    for (ll i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        a[u].push_back(v); a[v].push_back(u);
    }
    //对每个未访问的节点进行DFS，统计连通分量
    for (ll i = 1; i <= n; ++i) if (!b[i]) {
        cnt++; dfs(i);//给每个连通分量编号，并验证是否为二分图
    }
    for (ll i = 1; i <= n; ++i) {
        bfs(i);//以每个节点为起点进行BFS 计算它到其他所有节点的距离
        for (ll j = 1; j <= n; ++j)
            ans[b[i]] = max(ans[b[i]], dis[j]);//更新当前连通分量的直径 最长的最短路径
    }
    ll sum = 0;
    for (ll i = 1; i <= cnt; ++i) sum += ans[i];//所有连通分量直径之和
    cout << sum;
    return 0;
}