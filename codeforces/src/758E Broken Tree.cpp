//
// Created by Psy.C on 2026/9/4.
//
/**
N = 1e6+5：最大节点数。
struct node { dep, id }：堆里元素，id 是哪个节点的能力可被削减，dep 是它的深度（用于堆序）。
operator<：按 dep 比较，用来对 priority_queue<node>（默认大顶堆，< 表示"更小"）排序。这里用 dep 决定优先级。
g[u]：邻接表（有向树边，父→子）。
sum[u]：
u
u 子树内所有
a
a 之和（未调整前）。
a[v]：节点
v
v 的"需求/能力值"。
b[v]：节点
v
v 的"容量"。
sc[u]：
u
u 子树内可"让渡"的总容量（后面解释）。
ca[v]：节点
v
v 能额外贡献的容量上界。
X[i], Y[i]：边
(
X
i
,
Y
i
)
(X
i
​
 ,Y
i
​
 )。
q[u]：每个节点维护一个可并堆（用 priority_queue 合并）‍，堆里存的是"子树内还可被削减的候选节点"

递归遍历每个儿子
v
v（先深度优先，深度 dep+1）。
sum[u] += sum[v] + a[v]：累加子树的
a
a 总和。注意 sum[v] 已经是
v
v 整棵子树去掉
v
v 自身的和？实际上 sum[u] 表示"
u
u 子树内除了
u
u 自己之外的
a
a 之和"——因为后面 if (u==1) return 前才处理
u
u 自身，且加的是 sum[v]+a[v]。所以 sum[u] = 所有后代（不含 u）的
a
a 和。
sc[u] += sc[v]：合并子树的"让渡容量"总和。
可并堆合并：为把儿子
v
v 的候选堆并入父亲
u
u，采用小堆并入大堆（启发式合并）：若 q[v].size() > q[u].size() 先 swap（把大的换给 q[u]），然后把 q[v] 里元素一个个弹入 q[u]。这保证总复杂度约 O(N log N)
根节点不处理"自身削减"（根没有父边做约束），直接返回（但它的 sum 已经累计了

核心贪心削减：只要
u
u 子树的需求和 sum[u] 超过其容量 b[u]，就需要从子树里"削掉"多余的
a
a。
从堆顶 q[u] 取一个可削减的候选节点
x
x。
mn = min(sum[u]-b[u], ca[x.id])：本次最多削减的量 = 缺口（sum[u]-b[u]）与
x
x 可削减上限 ca[x.id] 的较小者。
削减时同时对
a
[
x
.
i
d
]
a[x.id] 和
b
[
x
.
i
d
]
b[x.id] 都减去
m
n
mn（两个权值一起降，保持平衡），并更新
x
x 的剩余可削减 ca[x.id]。
同步更新 sum[u]（需求减少）和 sc[u]。
若
x
x 还能再削减（ca[x.id] > 0），把它放回堆。
循环直到 b[u] >= sum[u]；若过程中堆为空仍不够削 → 无解输出 -1

把
u
u 自身加入候选堆（它自己也能被削减，供祖先使用），记录其深度 dep。
计算
u
u 能最大贡献给祖先的容量 ca[u]：
a[u]-1：
a
u
a
u
​
  至少要保留 1（不能减到 0）→ 可削减上限。
b[u]-sum[u]+sc[u]：
u
u 满足自身约束后剩余容量，加上自己子树内"让渡"来的 sc[u]，是它能向上提供的容量。
两者取小。
sc[u] += ca[u]：把这部分额外可让渡容量并入
s
c
[
u
]
sc[u]，传给父亲（表示祖先还能再从这里挤出容量）

读入
n
n 和
n
−
1
n−1 条边：父 X[i]、子 Y[i]，以及子节点的初始
a
[
Y
[
i
]
]
a[Y[i]]、
b
[
Y
[
i
]
]
b[Y[i]]。
dfs(1,0) 从根开始做整棵树处理。
若无解，dfs 里已 exit(0) 并输出 -1。
有解则输出
n
n，然后按原边顺序输出每条边的新
a
,
b
a,b（已被调整过），完成答案输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+5;

struct node { int dep, id; };
bool operator<(node a, node b) { return a.dep < b.dep; }

vector<int> g[N];
int sum[N], a[N], sc[N], b[N], ca[N], X[N], Y[N];
priority_queue<node> q[N];
void dfs(int u, int dep) {
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i]; dfs(v, dep+1);
        sum[u] += sum[v] + a[v]; sc[u] += sc[v];
        if (q[v].size() > q[u].size()) swap(q[u], q[v]);
        while (!q[v].empty()) {
            q[u].push(q[v].top());
            q[v].pop();
        }
    }
    if (u == 1) return;
    while (b[u] < sum[u]) {
        if (q[u].empty()) { puts("-1"); exit(0); }
        node x = q[u].top(); q[u].pop();
        int mn = min(sum[u] - b[u], ca[x.id]);
        a[x.id] -= mn, b[x.id] -= mn; ca[x.id] -= mn;
        sum[u] -= mn, sc[u] -= mn;
        if (ca[x.id] > 0) q[u].push(x);
    }
    if (b[u] < sum[u]) { puts("-1"); exit(0); }
    q[u].push({.dep = dep, .id = u});
    ca[u] = min(a[u]-1, b[u]-sum[u]+sc[u]);
    sc[u] += ca[u];
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n;
signed main() {
    fast;
    n = rd();
    for (int i = 1; i < n; ++i) {
        X[i] = rd(), Y[i] = rd();
        g[X[i]].push_back(Y[i]);
        a[Y[i]] = rd(), b[Y[i]] = rd();
    }
    dfs(1, 0);
    cout << n << '\n';
    for (int i = 1; i < n; ++i)
        cout << X[i] << ' ' << Y[i] << ' ' << a[Y[i]] << ' ' << b[Y[i]] << '\n';
    return 0;
}