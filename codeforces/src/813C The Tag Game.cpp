//
// Created by Psy.C on 2026/9/21.
//
/**
对树做 DFS，记录每个节点到起点的距离到数组 d
a[i] = 节点 i 到 Alice 起点(节点1) 的距离。
b[i] = 节点 i 到 Bob 起点(节点 x) 的距离
遍历每个节点 i：

若 a[i] > b[i]：说明 Alice 到节点 i 比 Bob 更远——即 Alice 能先于 Bob 到达该节点，可安全抵达。
对这样的节点，Alice 到达用时为 a[i]。由于两人等速交替，Alice 到达后 Bob 还需 a[i] 步追到该节点，Alice 能维持的最大时间约为 2 * a[i]（去程 a[i] 步 + 被追上前的逗留/往返）。
取所有满足 a[i] > b[i] 的节点中 2 * a[i] 的最大值作为答案。

逻辑核心：Alice 只能去"她比 Bob 更早到达"的节点；在这些节点中选一个距离最远的，其往返/存活时间为 2 × 距起点的距离，取最大。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1e4;

vector<int> e[N];
void dfs(int u, int fa, int step, int* d) {
    d[u] = step;
    for (int v : e[u])
        if (v != fa) dfs(v, u, step+1, d);
}

int a[N], b[N], ans;
int main() {
    fast;
    int n, x; cin >> n >> x;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1, -1, 0, a), dfs(x, -1, 0, b);
    for (int i = 1; i <= n; ++i)
        if (a[i] > b[i]) ans = max(ans, a[i]*2);
    cout << ans;
    return 0;
}