//
// Created by Psy.C on 2026/4/23.
//
/**
pre[N]：并查集/连通块标记数组
vis[N]：访问标记数组
ve[N]：邻接表
z：存储同时与s和t相连的连通块
ans：存储答案边

将连通块标记为col
用DFS遍历连通块，建立生成树
将遍历的边加入答案

读入n个点和m条边
构建邻接表表示无向图
读入特殊节点s和t，以及度数限制ds和dt
标记s和t为已访问
将s和t标记为特殊连通块(n+1)
对所有未访问的节点进行DFS，形成连通块
每个连通块用其第一个节点编号标记
统计与s相邻的连通块：cnt[pre[v]] |= 1（设置最低位）
记录与s相邻的节点：e[pre[v]][0] = v
统计与t相邻的连通块：cnt[pre[v]] |= 2（设置第二位）
记录与t相邻的节点：e[pre[v]][1] = v
遍历所有连通块（i == pre[i]表示连通块代表节点）
cnt[i] == 1：仅与s相连的连通块，连接s并减少ds
cnt[i] == 2：仅与t相连的连通块，连接t并减少dt
cnt[i] == 3：同时与s和t相连的连通块，加入z数组
处理同时与s和t相连的连通块：
第一个连通块：同时减少ds和dt
后续连通块：优先连接度数限制更大的节点
检查度数限制是否满足
输出结果和边列表
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+7;

int pre[N], vis[N];
vector<int> ve[N], z;
vector<ii> ans;
void dfs(int col, int u) {
    pre[u] = col; vis[u] = 1;
    for (int v : ve[u]) {
        if (vis[v]) continue;
        ans.push_back({u, v});
        dfs(col, v);
    }
}

int n, m, s, t, ds, dt, cnt[N], e[N][2];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        ve[u].push_back(v); ve[v].push_back(u);
    }
    cin >> s >> t >> ds >> dt;
    vis[s] = vis[t] = 1; pre[s] = pre[t] = n+1; pre[n+1] = n+1;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        dfs(i, i);
    }
    for (int v : ve[s]) { cnt[pre[v]] |= 1; e[pre[v]][0] = v; }
    for (int v : ve[t]) { cnt[pre[v]] |= 2; e[pre[v]][1] = v; }
    for (int i = 1; i <= n+1; ++i) {
        if (i != pre[i]) continue;
        if (cnt[i] == 1) {
            ds--;
            ans.push_back({s, e[i][0]});
        }
        if (cnt[i] == 2) {
            dt--;
            ans.push_back({t, e[i][1]});
        }
        if (cnt[i] == 3) z.push_back(i);
    }
    for (int i = 0, v; i < z.size(); ++i) {
        v = z[i];
        if (!i) {
            ds--, dt--;
            if (v == n+1) ans.push_back({t, s});
            else ans.push_back({s, e[v][0]}), ans.push_back({t, e[v][1]});
        } else {
            if (v == n+1) continue;
            if (ds > 0) {
                ds--;
                ans.push_back({s, e[v][0]});
            } else if (dt > 0) {
                dt--;
                ans.push_back({t, e[v][1]});
            } else {
                cout << "No\n";
                return 0;
            }
        }
    }
    if (ds < 0 || dt < 0) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (auto&[fst, snd] : ans)
        cout << fst << ' ' << snd << '\n';
    return 0;
}