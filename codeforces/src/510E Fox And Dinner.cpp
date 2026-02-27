//
// Created by Psy.C on 2026/2/27.
//
/**
g[i]存储以i为起点的边在e中的索引

BFS寻找增广路径，构建层次图
从源点s开始，标记可达点并计算距离
只考虑还有剩余容量的边（v.cap > v.flow）
返回是否能到达汇点t

DFS在层次图中找增广路径
x == t || a == 0：到达汇点或无可用流量时返回
d[x] + 1 == d[u.to]：只走层次图中的边
更新正向边流量和反向边流量
如果没找到流量，将距离设为-1

重复BFS构建层次图和DFS寻找增广路径
直到无法到达汇点为止
返回最大流

判断x是否为素数
遍历2到√x，检查是否有因子
f[N]：访问标记数组
ans[N]：存储结果的向量数组
find函数：DFS遍历连通块，将节点加入当前连通块

e1, e2：分别统计偶数和奇数的数量
将偶数连接到源点，容量为2；奇数连接到汇点，容量为2
如果奇数和偶数数量不相等，设置flag=1
否则，在偶数和奇数之间建立边，如果它们的和是素数，容量为1
运行最大流，如果结果不等于2*e1，说明无法完美匹配

如果flag=1，输出"Impossible"
否则，重新构建图，只保留流量为1的边（匹配边）
DFS找到所有连通块并输出结果
输出连通块的数量和每个连通块的节点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 501, inf = 0x7fffffff;
struct node { int from, to, cap, flow; };
vector<node> e;
vector<int> g[N];
void add(const int from, const int to, const int cap) {
    e.push_back({from, to, cap, 0});
    e.push_back({to, from, 0, 0});
    const int w = e.size();
    g[from].push_back(w - 2);
    g[to].push_back(w - 1);
}

bool vis[N];
int s, d[N], t;
bool bfs() {
    memset(vis, false, sizeof vis);
    queue<int> q; q.push(s); d[s] = 0; vis[s] = true;
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            if (auto v = e[g[u][i]]; !vis[v.to] && v.cap > v.flow) {
                vis[v.to] = true;
                d[v.to] = d[u] + 1;
                q.push(v.to);
            }
        }
    }
    return vis[t];
}

int cur[N];
int dfs(const int x, int a) {
    if (x == t || a == 0) return a;
    int flow = 0, f;
    for (int& i = cur[x]; i < g[x].size(); ++i) {
        if (const auto u = e[g[x][i]]; d[x] + 1 == d[u.to] &&
            (f=dfs(u.to, min(a, u.cap-u.flow))) > 0) {
            e[g[x][i]].flow += f;
            e[g[x][i]^1].flow -= f;
            flow += f;
            a -= f;
            if (a == 0) break;
        }
    }
    if (!flow) d[x] = -1;
    return flow;
}

int dinic(const int ss, int tt) {
    int flow = 0;
    while (bfs()) {
        memset(cur, 0, sizeof(cur));
        flow += dfs(ss, inf);
    }
    return flow;
}

bool prime(const int x) {
    for (int i = 2; i*i <= x; ++i)
        if (x%i == 0) return false;
    return true;
}

bool f[N];
vector<int> ans[N];
int b;
void find(const int now) {
    f[now] = true;
    ans[b].push_back(now);
    for (const int i : g[now]) {
        if (f[i]) continue;
        find(i);
    }
}

void init() {
    for (auto& i : g) i.clear();
    e.clear();
}


int n, num[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> num[i];
    init(); s = 0; t = n + 1;
    int e1 = 0, e2 = 0, flag = 0;
    for (int i = 1; i <= n; ++i) {
        if (num[i]%2 == 0) { e1++; add(s, i, 2); }
        else { e2++; add(i, t, 2); }
    }
    if (e1 != e2) flag = 1;
    else {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (num[i]%2 == 0 && num[j]%2 == 1 && prime(num[i]+num[j]))
                    add(i, j, 1);
        if (const int flow = dinic(s, t); flow != 2*e1) flag = 1;
    }
    if (flag == 1) cout << "Impossible";
    else {
        b = 0; memset(f, 0, sizeof f);
        for (int i = 0; i < N; ++i) {
            g[i].clear();
            ans[i].clear();
        }
        for (int i = 0; i < e.size(); i += 2) {
            if (e[i].flow == 1) {
                int u = e[i].from, v = e[i].to;
                g[u].push_back(v); g[v].push_back(u);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (f[i]) continue;
            find(i);
            b++;
        }
        cout << b << '\n';
        for (int i = 0; i < b; ++i) {
            cout << ans[i].size() << ' ';
            for (const int j : ans[i]) cout << j << ' ';
            cout << '\n';
        }
    }
    return 0;
}