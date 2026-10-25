//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
v[N]：DFS 访问标记。
a[N]：邻接表，每项 (邻居, 边编号带符号)。
val[N]：点权（初始供需）。
ans[N]：每条边的最终权值（流量，带符号表示方向）
标记 x 已访问。
遍历 x 的所有邻接点，若未访问过，则 DFS 到子节点，传入 fa=x 和该边的带符号编号（a[x][i].second）。
含义：树的后序遍历（先处理子节点，再处理父节点）
若点 x 处理完子树后仍有余量 val[x] != 0：
在边 id 上记录流量：
若 id < 0（这条边在邻接表中被记为从父到子的反向，即 -id）：ans[-id] -= val[x]（流量取负，表示反向）。
若 id >= 0：ans[id] += val[x]（正向流量）。
把 val[x] 转移给父节点：val[fa] += val[x]；然后 val[x] = 0。
核心思想：DFS 后序处理。每次把"子树内多出的供需"通过连接父亲的边，转移到父亲。这样每条边最终承担一个权值 = 子树内部的总供需差，方向由符号表示。整个树的供需差最终汇聚到根（根没有父边，所以总和必须为 0 才能平衡——这就是 sum != 0 → Impossible 的原因）
读入 n。
读入每个点的 val[i]，累加 sum。
若 sum != 0：点权总和不为 0 → 无解，输出 Impossible。
否则输出 Possible
读入边数 m。
对每条边 i（u↔v）：
a[u] 加入 (v, +i)：从 u 出发方向记边号为 +i。
a[v] 加入 (u, -i)：从 v 出发方向记边号为 -i。
通过正负号区分"这条边在 DFS 中被访问时，是从哪一端进入的"，从而能正确给边定方向
从根节点 1 出发 DFS，父节点为 0（虚拟），根无父边（id=0）。
处理完所有边后，ans[i] 就是每条边 i 的带符号流量。
逐个输出。
注意：根节点 1 若 val 最后归零（因为 sum=0），所以根不存在未平衡的多余流量
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+10;

bool v[N];
vector<ii> a[N];
int val[N], ans[N];
void dfs(int x, int fa, int id) {
    v[x] = 1;
    rep(i,a[x].size()) if (v[a[x][i].first] == 0) dfs(a[x][i].first, x, a[x][i].second);
    if (val[x] != 0) {
        if (id < 0) ans[-id] -= val[x]; else ans[id] += val[x];
        val[fa] += val[x]; val[x] = 0;
    }
}

int n, m;
int main() {
    fast;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) { cin >> val[i]; sum += val[i]; }
    if (sum != 0) { cout << "Impossible"; return 0; }
    cout << "Possible\n";
    cin >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        a[u].emplace_back(v,i); a[v].emplace_back(u,-i);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
    return 0;
}