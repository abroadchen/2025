//
// Created by Psy.C on 2026/10/9.
//
/**
T(x)=1+2+⋯+x=
2
x(x+1)
​
 ，即前
x
x 个正整数和。
sum[i] 是
T
T 的前缀和
即
sum
[
i
]
=
∑
k
=
1
i
T
(
k
)
=
∑
k
=
1
i
k
(
k
+
1
)
2
sum[i]=∑
k=1
i
​
 T(k)=∑
k=1
i
​

2
k(k+1)
二分求出满足
T
(
i
)
<
x
T(i)<x 的最大
i
i（即
i
(
i
+
1
)
2
<
x
2
i(i+1)
​
 <x 的最大整数
i
i）。
返回
x
⋅
(
i
+
1
)
−
sum
[
i
]
x⋅(i+1)−sum[i]
求
∑
t
=
0
i
(
x
−
T
(
t
)
)
=
(
i
+
1
)
x
−
∑
t
=
1
i
T
(
t
)
∑
t=0
i
​
 (x−T(t))=(i+1)x−∑
t=1
i
​
 T(t)。它等价于把
x
x 表示成三角数相关的"拆分成最小步数总和"的收益。
标准 Tarjan 算法，对每个节点算出其所在 SCC 编号 b[u]，总 SCC 数为 scc。
主函数对每个未访问点调用，得到整张图的 SCC 划分
若一条边
u
→
v
u→v 两端在同一个 SCC：这条边可以在 SCC 内反复走，把它的收益（经过 find 处理后）‍累加到该 SCC 的总收益 w[scc]。
若两端在不同 SCC：缩点后作为 DAG 的一条有向边（f[u_scc].push({v_scc, w})）
dfs(u) = 从 SCC
u
u 出发能获得的最大总收益。
对每条出边
(
v
,
w
)
(v,w)：
w
+
d
f
s
(
v
)
w+dfs(v) 取最大。
最后加上本 SCC 的内部回收收益 w[u]（环内反复走累积的）。记忆化避免重复计算

这是一个强连通分量 + 缩点 + DAG 最长路 DP的综合题：用 Tarjan 求 SCC；把环内边的收益用 find(x)（关于三角数的一个求和函数，具体为
x
(
i
+
1
)
−
sum
[
i
]
x(i+1)−sum[i]，其中
i
i 是满足
T
(
i
)
<
x
T(i)<x 的最大整数）累加到该 SCC 的 w；把跨 SCC 边建成 DAG。最后记忆化搜索求从起点所在 SCC 出发的最大总收益：dis(u)=w[u]+max(边权+dis(后继))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e6+5, M = 1e4+5e3;

struct edge { int u, v, w; } e[N];
inline int T(int x) { return (x*(x+1))>>1; }

int sum[M];
inline int find(int x) {
    int l = 1, r = M, i = 0;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (T(mid) < x) i = mid, l = mid+1;
        else r = mid-1;
    }
    return x*(i+1) - sum[i];
}

int dfn[N], low[N], tim, st[N], top, in[N], scc, b[N];
vector<int> G[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim, st[++top] = u, in[u] = 1;
    for (int v : G[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (in[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        scc++;
        while (st[top] != u) in[st[top]] = 0, b[st[top]] = scc, top--;
        in[st[top]] = 0, b[st[top]] = scc, top--;
    }
}

int dis[N], w[N];
vector<ii> f[N];
int dfs(int u) {
    if (dis[u]) return dis[u];
    for (auto [fst, snd] : f[u])
        dis[u] = max(dis[u], snd + dfs(fst));
    dis[u] += w[u];
    return dis[u];
}

int n, m, bg;
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= M-1; ++i) sum[i] = sum[i-1] + T(i);
    for (int i = 1, u, v, ww; i <= m; ++i) {
        cin >> u >> v >> ww;
        G[u].push_back(v); e[i] = {.u = u, .v = v, .w = ww};
    }
    cin >> bg;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; ++i) {
        if (b[e[i].u] == b[e[i].v]) w[b[e[i].u]] += find(e[i].w);
        else f[b[e[i].u]].emplace_back(b[e[i].v], e[i].w);
    }
    cout << dfs(b[bg]) << '\n';
    return 0;
}