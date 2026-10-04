//
// Created by Psy.C on 2026/10/4.
//
/**
nxt/head/to 存边结构，g 为费用（权值），fl 为容量。
add 一次建两条边：正向边 (x→y, 费用w, 容量flow) 和反向边 (y→x, 费用-w, 容量0)，用于费用流的"反悔"。
cnt=1 起，配合 x^1 成对取反边（因为每次连两条边，索引相邻互异）。注意这里 add 内 cnt 从 1 起，每加一条边自增，所以正向边索引为偶数、反向边为奇数时 ^1 才配对——实际上第一条正向边索引 2、反向 3 配对（2^1=3）
SPFA 跑最短路（因为费用 g 可为负——反向边），求源 s 到汇 t 的最小费用路径。
dis[v] = 到 v 的最小费用距离；mn[v] = 路径上最小剩余容量（瓶颈流量）。
now[v] = 记录 v 是从哪条边松弛来的（前驱边），用于回溯增广路径。
松弛前提：剩余容量 fl[i]>0 且能缩短距离。
返回是否有可行增广路（dis[t] < inf）。
vis 是 SPFA 的队列标记（用于加速）。
double w = g[i]; 这里类型写成了 double，但 g 是 int，实际是 int 赋值，无实质影响（代码中费用均为整数）
L[i] 初始为 1，R[i] 初始为 n（默认每位置可取 1..n）。
处理 q 个约束：op=1 表示属于 [l,r] 的位置取值必须 ≥ v（下界），更新 L[i]=max(L[i],v)；op=2 表示取值必须 ≤ v（上界），更新 R[i]=min(R[i],v)。
这样就为每个位置确定了取值区间 [L[i], R[i]]
构造一个分层图网络：

第 1 层（位置节点）‍：s → i，容量 1（每个位置选一个值），费用 0。
第 2 层（数值候选）‍：i → j+n，容量 1，费用 0——表示位置 i 可以选数值 j（仅当 L[i]≤j≤R[i]）。
第 3 层：i+n → i+2*n，费用 2j-1，容量 1。这是费用累积点——第 j 个数值对应的费用为奇数 2j-1。
汇点：i+2*n → t，容量 inf，费用 0。
关键设计：数值 j 被选中时，需要通过费用 2j-1 的边。由于前 j 条"第3层"边容量各为1，若数值 j 被使用，那么数值 1,2,...,j 都会被使用（因为容量链式累积），费用总和为：

(
1
)
+
(
3
)
+
⋯
+
(
2
j
−
1
)
=
j
2
(1)+(3)+⋯+(2j−1)=j
2

这正是平方和
∑
(
取值
)
2
∑(取值)
2
  的最小化建模——这是费用流的经典 trick（用奇数和模拟平方，把"选到数值 j"的费用线性化）。

若 L[i] > R[i]（区间为空，无法赋值），直接输出 -1。
while (spfa())：不断找最小费用增广路并增广，直到无路可增（最大流跑满，即所有位置都赋到值）。
a1：累计总流量（最大流值，应为 n）。
a2：累计总费用 = mn[t] × dis[t]（瓶颈流量 × 该路单单位费用）。
回溯增广：从汇点沿 now 前驱边回到源点，更新正向/反向边容量（x^1 取反向边，to[now[x]^1] 找到前一个节点）。
最终输出 a2（最小总费用）。
当无法给所有位置赋值（某些位置无可行取值导致最大流 < n）时，理论上应输出 -1，但此处代码只判断了 L[i]>R[i]，若约束内部冲突可能仍会输出部分费用——这属于实现细节
SPFA 每次 O(VE)，增广次数 = 流量 = n，总 O(n·VE)。节点数 3n+2，边数较多但都在 M 内
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 55, M = 1e6+5, inf = 2e9;

int nxt[M], cnt = 1, head[N*3], to[M], g[M], fl[M];
inline void add(int x, int y, int w, int flow) {
    to[++cnt] = y, g[cnt] = w, fl[cnt] = flow, nxt[cnt] = head[x], head[x] = cnt;
    to[++cnt] = x, g[cnt] = -w, fl[cnt] = 0, nxt[cnt] = head[y], head[y] = cnt;
}

int dis[N*3], mn[N*3], s, t, now[N*3];
bool vis[N*3];
inline bool spfa() {
    for (int i = s; i <= t; ++i) dis[i] = inf, vis[i] = 0;
    dis[s] = 0, mn[s] = inf, vis[s] = 1;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            double w = g[i];
            if (fl[i] && dis[v] > dis[u] + w) {
                now[v] = i;
                dis[v] = dis[u] + w;
                mn[v] = min(mn[u], fl[i]);
                if (!vis[v]) vis[v] = 1, q.push(v);
            }
        }
    }
    if (dis[t] < inf) return 1;
    return 0;
}

int L[N], R[N];
int main() {
    fast;
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; ++i) L[i] = 1, R[i] = n;
    s = 0, t = 3*n+1;
    while (q--) {
        int op, l, r, v; cin >> op >> l >> r >> v;
        for (int i = l; i <= r; ++i) {
            if (op == 1) L[i] = max(L[i], v);
            else R[i] = min(R[i], v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (L[i] > R[i]) return cout << "-1", 0;
        add(s, i, 0, 1);
        for (int j = L[i]; j <= R[i]; ++j) add(i, j+n, 0, 1);
        for (int j = 1; j <= n; ++j) add(i+n, i+2*n, 2*j-1, 1);
        add(i+2*n, t, 0, inf);
    }
    int a1 = 0, a2 = 0;
    while (spfa()) {
        a1 += mn[t]; a2 += (double)mn[t]*dis[t];
        int x = t;
        while (x != s) {
            fl[now[x]] -= mn[t], fl[now[x]^1] += mn[t];
            x = to[now[x]^1];
        }
    }
    cout << a2;
    return 0;
}