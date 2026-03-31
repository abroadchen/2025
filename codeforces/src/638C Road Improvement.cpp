//
// Created by Psy.C on 2026/3/31.
//
/**
e[N]：邻接表，存储树的边信息（目标节点，边编号）
tot：使用的颜色总数
ans[N]：每个颜色对应的边列表
初始化计数器：now = 0，用于分配当前可用的颜色
遍历邻接节点：对当前节点的所有邻居
跳过父节点：if (v == fa) continue，避免回溯
分配颜色：now++，递增颜色编号
避免冲突：if (now == t) now++，如果当前颜色与父节点传来的颜色相同，则跳过
更新总数：tot = max(tot, now)，记录使用的最大颜色数
记录边：ans[now].push_back(e[x][i].second)，将边添加到对应颜色组
递归处理：dfs(v, x, now)，对子节点继续DFS
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5;

vector<ii> e[N];
int tot;
vector<int> ans[N];
void dfs(int x, int fa, int t) {
    int now = 0;
    for (int i = 0; i < e[x].size(); ++i) {
        int v = e[x][i].first;
        if (v == fa) continue;
        now++;
        if (now == t) now++;
        tot = max(tot, now);
        ans[now].push_back(e[x][i].second);
        dfs(v, x, now);
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        e[u].emplace_back(v, i);
        e[v].emplace_back(u, i);
    }
    dfs(1, -1, 0);
    cout << tot << '\n';
    for (int i = 1; i <= tot; ++i) {
        cout << ans[i].size() << ' ';
        for (int j : ans[i]) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}