//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
g[u]：u 的出边（有向边 u→v）。
f[u]：节点 u 向下能到达的"叶子集合"的状态掩码。
b[now]：叶子节点的编号（重新编号用，使叶子能映射到位中）
若是叶子节点（无出边），它的 f 被置为 1 << (b[now]-1)，即用位代表这个叶子。
若是内部节点，则 f[now] = 所有子节点 f 的按位或，表示它向下能覆盖到的叶子集合。
注意这里 f 也充当了记忆化/访问标记（if(!f[..]) dfs(..)），因为初始值为 0，叶子位从 1 开始所以非 0
读 N 个节点、M 条有向边。
in[v]：统计入度。
叶子编号：对无出边的节点 b[i] = ++num，把这些叶子映射到 1..num，作为位的位置。
源点处理：对入度为 0 的点（in[i]==0，即 DAG 的入口/源点）执行 dfs(i) 求出其向下覆盖的叶子掩码 f[i]，存入 fr[++num]。
到这里 num 被复用为"源点个数"。fr[] 存每个源点可影响到的叶子集合
这是一个子集枚举：now 表示枚举到第几个源点；o 表示当前已选的源点个数；dt 是已选源点覆盖叶子的并集掩码。
枚举所有源点子集：
若 o == num（选全部）或 o == 0（不选）则跳过；
否则 __builtin_popcount(dt) = 并集覆盖到的叶子数。
若出现 叶子数 ≤ 源点数 的非平凡子集，则置 flg = 1
dfs(1,0,0) 从枚举第 1 个源点开始，初始没选任何源点、无覆盖。
若发现存在"覆盖叶子数 ≤ 源点数"的方案则输出 NO，否则输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e6+2e3;

vector<int> g[N];
int f[N], b[N];
void dfs(int now) {
    if (g[now].empty()) f[now] = 1<<(b[now]-1);
    for (int i = 0; i < g[now].size(); i++) {
        if (!f[g[now][i]]) dfs(g[now][i]);
        f[now] |= f[g[now][i]];
    }
}

int n, m, in[N], num, fr[N];
void init() {
    cin >> n >> m;
    rep(i,m) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); in[v]++;
    }
    rep(i,n) if (g[i].empty()) b[i] = ++num;
    num = 0;
    rep(i,n) if (!in[i]) dfs(i), fr[++num] = f[i];
}

int flg;
void dfs(int now, int o, int dt) {
    if (now > num) {
        if (o == num) return;
        if (o == 0) return;
        if (__builtin_popcount(dt) <= o) flg = 1;//覆盖叶子数 ≤ 源点数 → 置标志
    } else {
        dfs(now+1,o,dt);//不选第 now 个源点
        dfs(now+1,o+1,dt|fr[now]);//选第 now 个源点，并集加入
    }
}

void solve() {
    dfs(1,0,0);
    if (flg) cout << "NO\n"; else cout << "YES\n";
}

int main() {
    fast;
    init(); solve();
    return 0;
}