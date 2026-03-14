//
// Created by Psy.C on 2026/3/13.
//
/**
存储树结构，v[i]存储节点i的所有相邻节点
如果当前节点的度数（连接的边数）小于等于2，则标记该节点为已访问（vis[x]=1）
遍历当前节点的所有相邻节点，跳过父节点，对其他未访问节点递归执行DFS

遍历所有节点，找到度数为1的节点（叶子节点）
从每个叶子节点开始进行DFS遍历，标记路径上的节点（度数≤2的节点）
对每个节点i，统计其相邻节点中被标记过的节点数量
ans[i]记录节点i连接的被标记节点数量

遍历所有未被标记的节点
对于每个未被标记的节点i，统计满足条件的相邻节点数量：
相邻节点x也未被标记
节点x的度数大于min(ans[x], 2) + 1
如果这样的节点数量超过2个，则输出"No"，否则输出"Yes"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

vector<int> v[N];
int vis[N];
void dfs(int x, int fa) {
    if (v[x].size() <= 2) {
        vis[x] = 1;
        for (int i = 0; i < v[x].size(); ++i)
            if (v[x][i] != fa)
                dfs(v[x][i], x);
    }
}

int n, ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        v[a].push_back(b); v[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i)
        if (v[i].size() == 1) dfs(i, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < v[i].size(); ++j)
            if (vis[v[i][j]]) ans[i]++;
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        int cnt = 0;
        for (int j = 0; j < v[i].size(); ++j) {
            int x = v[i][j];
            if (!vis[x] && v[x].size() > min(ans[x], 2) + 1)
                cnt++;
        }
        if (cnt > 2) { cout << "No\n"; return 0; }
    }
    cout << "Yes\n";
    return 0;
}