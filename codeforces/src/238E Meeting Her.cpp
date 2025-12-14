//
// Created by Psy.C on 2025/12/13.
//
/*
*vis[N]: 访问标记数组
cnt: 访问计数器
dp[N]: 动态规划数组
n: 节点数
g[N][N]: 原始图的邻接矩阵
d[N][N]: 所有点对最短距离矩阵
S[N], T[N]: 查询的起点和终点数组
ans[N]: 答案数组
 *
*计算节点u在查询fa中的最优值
vis[u] == cnt检查是否已访问（记忆化搜索）
寻找满足最短路径条件的邻接点v
条件：d[S[fa]][u] + d[v][T[fa]] + 1 == d[S[fa]][T[fa]]
这表示边(u,v)在从S[fa]到T[fa]的最短路径上
返回最小的ans值
 *
*读入节点数n、边数m、起点a、终点b
初始化图和距离矩阵为无穷大
设置对角线为0（自己到自己的距离为0）
*读入m条有向边
使用Floyd算法计算所有点对最短距离
*读入查询数q
对每个查询(s,t)：
如果s到t不可达则跳过
找出所有在最短路径上的节点
条件：d[s][i] + d[j][t] + 1 == d[s][t]表示边(i,j)在最短路径上
*对节点按距离排序并去重
只保留那些在唯一距离位置的节点
 *
*初始化终点b的答案为0
迭代更新所有节点的答案：
对每个查询，使用DFS计算相关节点的最优值
如果有任何更新则继续迭代
输出从a到b的最优解
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 107
#define inf 0x3f3f3f3f
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;
template<class T, class V>// 如果b<a则更新a为b并返回true
bool minn(T& a, V b) { return a > b ? a = b, true : false; }
template<class T, class V>
bool maxx(T& a, V b) { return a < b ? a = b, true : false; }

int vis[N], cnt, dp[N], n, g[N][N], d[N][N], S[N], T[N], ans[N];
int dfs(const int u, const int fa) {
    if (vis[u] == cnt) return dp[u];
    vis[u] = cnt;
    int ret = -1;
    rep(v,n) {
        if (g[u][v] == 1 &&
            d[S[fa]][u] + d[v][T[fa]] + 1 == d[S[fa]][T[fa]]) {
            maxx(ret, dfs(v, fa));
        }
    }
    if (ret == -1) ret = inf;
    minn(ret, ans[u]);
    return dp[u] = ret;
}

int main() {
    fast;
    int m, a, b, q; cin >> n >> m >> a >> b;
    memset(g, 0x3f, sizeof(g));
    memset(d, 0x3f, sizeof(d));
    memset(ans, 0x3f, sizeof(ans));
    rep(i,n) g[i][i] = d[i][i] = 0;
    rep(i,m) {
        int u, v; cin >> u >> v;
        g[u][v] = d[u][v] = 1;
    }
    rep(k,n) rep(i,n) rep(j,n) minn(d[i][j], d[i][k] + d[k][j]);
    cin >> q; vector<pair<int, int>> v; vector<int> V[N];
    rep(o,q) {
        int s, t; cin >> s >> t; S[o] = s; T[o] = t; v.clear();
        if (d[s][t] >= inf) continue;
        rep(i,n) rep(j,n) {
            if (g[i][j] != 1) continue;
            if (d[s][i] + d[j][t] + 1 == d[s][t]) {
                v.emplace_back(d[s][i], i);
                v.emplace_back(d[s][j], j);
            }
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (int i = 0; i < v.size(); ++i) {
            if (i && v[i].first == v[i-1].first) continue;
            if (i < v.size() - 1 && v[i].first == v[i+1].first) continue;
            V[o].push_back(v[i].second);
        }
    }
    ans[b] = 0;
    while (true) {
        bool ok = false;
        rep(o,q) {
            if (d[S[o]][T[o]] >= inf) continue;
            for (const auto& u : V[o]) {
                cnt++;
                const int ret = dfs(u, o) + 1;
                if (minn(ans[u], ret)) ok = true;
            }
        }
        if (!ok) break;
    }
    cout << (ans[a] < inf ? ans[a] : -1) << '\n';
    return 0;
}