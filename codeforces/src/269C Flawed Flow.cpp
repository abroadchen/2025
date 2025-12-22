//
// Created by Psy.C on 2025/12/21.
//
/*
 *g[u]存储从节点u出发的所有边
 *每条边存储{{目标节点,权重}, 边的编号(正负表示方向)}
 *边的起点a、终点b和权重c
 *正向边，编号为+i
 *反向边，编号为-i
 *累计每个节点连接的所有边的权重总和
 *
*时间复杂度：O(n + m) - 每个节点和每条边最多被处理一次
空间复杂度：O(n + m) - 存储图和辅助数组
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200007
using namespace std;


int main() {
    fast;
    int n, m, all[N], ans[N], sum[N]; cin >> n >> m;
    memset(ans, -1, sizeof(ans));//未确定状态
    vector<pair<pair<int, int>, int> > g[N];
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c;
        g[a].push_back({{b,c}, i});
        g[b].push_back({{a,c}, -i});
        all[a] += c; all[b] += c;
    }
    queue<int> q; q.push(1);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (auto& v : g[u]) {//遍历从节点u出发的所有边
            if (~ans[abs(v.second)]) continue;
            if (v.second < 0) {//反向边
                ans[-v.second] = 1;//标记对应边的状态为1
                sum[v.first.first] += v.first.second;//累加到目标节点的权重和
            } else {
                ans[v.second] = 0;
                sum[v.first.first] += v.first.second;
            }
            if (sum[v.first.first] * 2 == all[v.first.first])//已选边权重和等于总权重和的一半
                if (v.first.first != n) q.push(v.first.first);//满足且不是终点n则将该节点加入队列继续处理
        }
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}