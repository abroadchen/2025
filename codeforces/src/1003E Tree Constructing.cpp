//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
n <= d：直径 d 最大就是 n-1（一条链），所以若 n≤d 必无解。
n > 2 && k == 1：k=1 时度数最多 1，即只能是一条单独边或两个点；若 n>2 无法让全部节点连通，故无解
deg[]：每个节点当前的度数，用来确保不超过 k。
adj：邻接表（作 DFS 用）。
e：边列表（最终输出）。
mx[u]：节点 u 距离直径两端点的最大距离（即 u 的"深度上限"），用来控制不把直径撑得超过 d
先造一条长度恰为 d 的链：节点 0 - 1 - 2 - … - d，共 d+1 个节点。
这条链本身直径就是 d。
mx[i] = max(i, d-i)：节点 i 在这条链上距离两端 0 和 d 的较远距离。例如 d=3 时：
mx[0]=max(0,3)=3，mx[1]=max(1,2)=2，mx[2]=max(2,1)=2，mx[3]=max(3,0)=3
中段（1、2）的 mx 较小 = 2。
关键思想：往某个节点 u 下面挂子节点时，会让"从该子节点到直径最远端"的距离变成 mx[u]+1。只要 mx[u]+1 <= d，挂上去就不会撑破直径 d。所以我们要优先在 mx 小（靠中间）‍的节点上挂新点，避免深度涨破 d
tag 从 d+1 递增：第一个新节点编号是 d+1（链末端后的节点）。
从节点 1 开始 DFS（故意跳过端点 0，因为端点 mx=d 已经没法再挂了），逐个访问链上节点。
对每个节点 fr：
若 mx[fr]+1 <= d：说明还能安全地挂子节点（不会让直径超 d）。
在 deg[fr] < k（度数未超上限）且 tag < n（点数未用尽）的条件下，不断给它挂新节点 tag，并设 mx[tag]=mx[fr]+1。
用 vis 防止重复访问，visit 后在链上递归。
由于链中越是中间节点 mx 越小，DFS 从节点 1 开始会先碰到中段节点（mx 小），它们能挂的子节点更深上限更大，从而优先把新节点挂在中段附近，尽量多塞点且不撑破直径。节点 0（端点 mx=d）是不挂的——端点挂了子节点直径就超 d 了
校验三件事，任一不满足就 NO：
max(deg) > k：有节点度数超上限。
min(deg) == 0：存在孤立点（不连通）。
e.size() != n-1：边数不对（不是树）。
通过则输出 YES 和所有边（编号 +1，因内部从 0 计）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

int n, d, k;
int main() {
    fast;
    cin >> n >> d >> k;
    if (n <= d || (n > 2 && k == 1)) { cout << "NO\n"; return 0; }
    vector<ii> e; e.reserve(n+1);
    vector<int> deg(n), mx(n);
    vector adj(n, vector<int>());
    auto add = [&](int u, int v) -> void {
        deg[u] += 1; deg[v] += 1;
        adj[u].emplace_back(v); adj[v].emplace_back(u);
        e.emplace_back(u, v);
    };
    for (int i = 0; i < d+1; i++) mx[i] = max(i, d-i);
    for (int i = 0; i+1 < d+1; i++) add(i, i+1);
    int tag = d+1;
    vector<bool> vis(n);
    auto dfs = [&](auto &self, int fr, int fa) -> void {
        if (vis[fr]) return;
        vis[fr] = true;
        if (tag >= n) return;
        if (mx[fr]+1 <= d) {
            while (deg[fr] < k && tag < n) {
                add(fr, tag);
                mx[tag] = mx[fr] + 1;
                tag += 1;
            }
        }
        for (auto to : adj[fr]) if (to != fa) self(self, to, fr);
    };
    for (int i = 1; i <= d && tag < n; i++) dfs(dfs, i, -1);
    if (ranges::max(deg) > k || ranges::min(deg) == 0 || (int)e.size() != n-1) cout << "NO\n";
    else {
        cout << "YES\n";
        for (auto [u, v] : e) cout << u+1 << ' ' << v+1 << '\n';
    }
    return 0;
}