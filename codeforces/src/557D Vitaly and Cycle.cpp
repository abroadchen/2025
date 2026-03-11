//
// Created by Psy.C on 2026/3/11.
//
/**
vis[N]: 访问标记数组
num[N]: 每个连通分量的节点数量
p[N]: 节点所属连通分量ID
c[N]: 节点颜色（1或2）
g[N]: 邻接表存储图

检验连通分量是否为二分图
为当前节点u分配连通分量ID并增加计数
遍历邻接节点v：
如果颜色冲突，返回false
如果邻接点未着色，赋予相反颜色（3-c[u]）
递归处理邻接点

特殊情况: 如果没有边，输出3和所有可能的三元组数量
遍历所有连通分量
对每个未访问节点进行二分图检验
如果发现非二分图，设置错误标志
情况1: 如果图不是二分图，输出0和1
统计每个连通分量中两种颜色的节点数量
计算每个连通分量内部的三元组数量
对于每个连通分量，计算同色节点对的数量（组合数C(k,2)）
情况2: 如果ans=0，输出2和另一种计算方式的结果
情况3: 否则输出1和ans

图遍历：O(n + m)
总体：O(n + m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

int vis[N], num[N], p[N], c[N];
vector<int> g[N];
bool dfs(int u, int id) {
    if (!vis[u]) num[id]++;
    p[u] = id; vis[u] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (c[u] == c[v]) return false;
        if (!c[v]) {
            c[v] = 3 - c[u];
            if (!dfs(v, id)) return false;
        }
    }
    return true;
}

int n, m, c1[N], c2[N];
int main() {
    fast;
    cin >> n >> m;
    if (m == 0) {
        cout << "3 " << 1ll*n*(n-1)*(n-2)/6 << '\n';
        return 0;
    }
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    int flag = 0, cnt = 1;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        c[i] = 1;
        if (!dfs(i, cnt)) { flag = 1; break; }
        cnt++;
    }
    if (flag) { cout << "0 1\n"; return 0; }
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 1) c1[p[i]]++;
        else c2[p[i]]++;
    }
    ll ans = 0;
    for (int i = 1; i < cnt; ++i) {
        if (num[i] <= 2) continue;
        ans += 1ll*c1[i]*(c1[i]-1)/2 + 1ll*c2[i]*(c2[i]-1)/2;
    }
    if (ans == 0) cout << "2 " << 1ll*(n-2)*m << '\n';
    else cout << "1 " << ans << '\n';
    return 0;
}