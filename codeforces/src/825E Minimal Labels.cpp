//
// Created by Psy.C on 2026/9/23.
//
/**
e[u]：u 指向的后继。
f[v]：指向 v 的前驱（反向边），用于拓扑时"删出度"
用大根堆 priority_queue<int>（默认最大堆）。
deg[0] 未初始化默认为 0；deg[u] 记录的是……（见下）。
注意：deg[] 在这里实际记录的是出度（每次 e[u].push_back(v); deg[u]++; 对起点 u 的 deg+1），而非传统意思的入度
每次从堆顶取编号最大的当前"叶子/可输出"节点。
给它赋当前剩余最大值 n - cnt（cnt 从 0 递增 → 赋值从 n 递减到 1）。
然后沿着反向边（即删掉 x 指向后继这条边对前驱的影响）减少前驱的 deg，若某个前驱出度归 0 就放入堆。
这样优先给编号大的节点赋更大的值，加上大根堆取最大，得到字典序最大的拓扑序赋值
按节点编号 1..n 输出各自的赋值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
vector<int> e[N], f[N];
int deg[N], ans[N];
priority_queue<int> q;
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        e[u].push_back(v); deg[u]++;
        f[v].push_back(u);
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!deg[i]) q.push(i);
    while (cnt < n) {
        int x = q.top(); q.pop();
        ans[x] = n - (cnt++);
        for (int v : f[x]) {//f[x] = 所有指向 x 的节点（前驱）
            deg[v]--;//前驱的"出度"减少
            if (!deg[v]) q.push(v);//出度清 0 的前驱入堆
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}