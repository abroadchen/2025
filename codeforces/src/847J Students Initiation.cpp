//
// Created by Psy.C on 2026/9/28.
//
/**
N = 5e3+5 = 5005：点相关数组的大小。因为题目最多 n=5000 个点，加上源点 0 和汇点 n+1，节点编号最高到 5001，所以数组开 5005 才不越界（这是上一轮修的关键 bug）。
M = 21111：边相关数组的大小（Dinic 存的是有向弧，一条边要存正向+反向两条弧）。留裕量用。
inf = 1e9：当作"无穷大"用（源点→点 的容量上限足够大的值）
nd：当前图的节点总数。
s：源点，d：汇点。
head[N]：链式前向星（邻接表的数组实现）的头指针数组，head[u] 指向 u 的第一条弧在 ver/nxt/flow 数组里的下标。
e：当前已使用的弧数量（即 ver 等数组的下标游标）
init：清空并重设一张图。每次调用 check(mid) 都要重建流图，所以先重置：记录节点数 nd、记下源 s、汇 d，把每个点的 head 置为 -1（表示没有弧），游标 e 归零
ver[e]：弧 e 指向的终点节点。
flow[e]：弧 e 的剩余容量。
nxt[e]：下一条同源于该起点的弧的下标（链式前向星的"链"）。
add(u, v, c)：加一条 u→v、容量 c 的边（有向弧），并且同时加一条 v→u、容量 0 的反向弧。反向弧用于 Dinic 的"退流/反悔"，初始容量 0。之所以两条弧下标相邻（e 与 e^1），是为了后面用 i^1 快速取到反边（^1 即对偶翻转最低位）
dis[N]：分层号（每个点距源点的"层数"）。q[N]：手写队列。
先把所有点分层号置为 -1（未访问），源点 s 入队并设层 dis[s]=0。
BFS 从源点沿还有剩余容量（flow[i] 非 0）‍的弧走，给没访问过的点标层 dis[u]+1，入队。一旦发现 v==d（到达汇点）提前返回 true（有增广路）。
返回 true 表示"还能从源到汇流得通"，false 表示图已无增广路，最大流求完。
注意：BFS 只在"容量 > 0"的弧上走，保证找的是残量网络里的路
cur[N]：当前弧优化数组，cur[u] 记录 u 已经尝试到哪条弧了，避免反复从链头找（否则会退化）。
dfs(u, exp)：尝试从 u 向汇点推 exp 这么多流量。
走到汇点就返回 exp。
遍历 u 的出弧：只走有容量（flow[i]>0）‍ 且 dis[v]==dis[u]+1（按分层号逐层推进，保证 BFS 找出的最短增广路）且能成功增广（t>0）的弧。
dfs(v, min(exp, flow[i]))：递归到 v，本次最多传 min(exp, flow[i])。
成功后更新残量：正向弧 flow[i] -= t，反向弧 flow[i^1] += t（退流机制）。
返回实际通过的流量 t。
返回 0 表示该点这个方向出不去（会回溯，让上一层尝试别的弧）。
反复 bfs() 分层；只要还能分层成功，就重置所有 cur 为对应 head，然后从源点 dfs(s, inf) 不断增广，累加总流量 ret。
直到 bfs() 返回 false（分层失败、无增广路）时，ret 就是最大流，返回。
in[N]/out[N]：每个点的入度/出度统计。
p[M]：存的 m 条无向边（已保证 first < second，即"小号→大号"为默认方向）
进入 check 先重置 in/out 数组，并 init 一张新图：n+2 个节点，源点 s=0，汇点 d=n+1。
exp 累计"源点需要送出去的总流量"（即必须减少的出度总量）。
遍历每条无向边 (u,v)（已保证 u<v）。
先按默认方向 u→v 记一次：out[u]++（u 出一个）、in[v]++（v 进一个）。
同时往流图里加一条容量 1 的弧 u→v：这条弧的含义是"翻转这条边"——如果这条弧上有 1 单位流量流过，等价于这条边从默认的 u→v 被翻转让 u 少一个出度、v 多一个出度（出度从 u 转移到 v）
对每个点 i：
若 out[i] > mid：说明默认方向下 i 的出度超了，必须至少减少 out[i]-mid 个出度。于是从源点 0 连向 i，容量 out[i]-mid，并把 exp 累加这个值。这代表"必须被转移走这么多单位出度"。
若 out[i] < mid：说明 i 的出度还有富余可接受更多出度，从 i 连向汇点 n+1，容量 mid-out[i]，表示"最多还能接收这么多单位出度"。
那些 out[i]==mid 的点既不连源也不连汇，在二分图两端平衡，只做中转
跑一遍最大流，得到从源点实际能送出的总流量 f。
若 f == exp，说明所有"必须转移的出度"都被成功消化了，即存在一种定向使每个点出度 ≤ mid，返回 true，否则 false。
建模直觉：默认所有边都从"小号"指向"大号"。这样某些点出度过大。我们把"出度过大的点"的多余出度，通过那些还没有被利用的边（容量1→代表翻转）转交给"出度有富余的点"。能全部转完就说明可行。由于所有无向边二选一方向，这本质上是一个"给每条边分派一个方向"的组合判定，能被最大流正确处理。
遍历所有节点的出弧：
if (j&1) continue;：跳过反向弧（正向弧下标是偶数、其配对反向弧是奇数，i^1 的原理，奇偶相邻）。
v < 1 || v > n：过滤掉指向源点 0 或汇点 n+1 的弧（那些是源/汇连接的辅助边，是原本的无向边）。
v < i：跳过同一对 (u,v) 中已经在小号一边处理过的，避免重复输出（因为从小号点出发统一打印）。
if (flow[j])：有流量说明这条弧被用来翻转了 → 边方向仍为默认 i→v，输出 i v。
else：无流量说明这条边保持默认未翻转……等等，这里要细心：

读入 n（点数）、m（边数）。
逐条读无向边 (a,b)，若 a>b 则 swap 保证 a<b，存入 p[i]。统一默认方向为"小号→大号"，方便后面统计和建图
二分答案求最小可行的最大出度。
check(mid) 是单调的：mid 越大越容易可行（上限放宽）。
l=-1（必不可行的下界，出度不能为负）、r=n（出度不可能超过 n，必可行）。
while(r-l>1)：标准二分模板。mid=(l+r)/2。可行则 r=mid（收窄上界），不可行则 l=mid（抬高下界）。
结束时 r 就是最小的可行值（因为所有 ≥r 都可行，所有 ≤l 都不可行，且 l、r 相邻）。
二分结束后：
正常来说 l 是"最后不可行"或 -1，check(l) 应为 false，走 else 输出 r。
if (check(l)) 其实是防御性写法：万一 l 也可行（极特殊情形），输出 l。
else 分支里 check(r) 的作用是用最终答案 r 再跑一次，把流图留在"按 r 定向"的最终状态，这样 print() 才能依据当前的 flow 值输出正确的定向方案。
最后 print() 输出每条边的最终方向
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e3+5, M = 21111, inf = 1e9;

int nd, s, d, head[N], e;
void init(int node, int src, int dst) {
    nd = node; s = src; d = dst;
    for (int i = 0; i < nd; ++i) head[i] = -1;
    e = 0;
}

int ver[M], nxt[M], flow[M];
void add(int u, int v, int c) {
    ver[e] = v, flow[e] = c, nxt[e] = head[u], head[u] = e++;
    ver[e] = u, flow[e] = 0, nxt[e] = head[v], head[v] = e++;
}

int dis[N], q[N];
bool bfs() {
    int i, u, v, l, r(0);
    for (i = 0; i < nd; ++i) dis[i] = -1; dis[q[r++]=s] = 0;
    for (l = 0; l < r; ++l) {
        for (i = head[u=q[l]]; i >= 0; i = nxt[i]) {
            if (flow[i] && dis[v=ver[i]] < 0) {
                dis[q[r++]=v] = dis[u]+1;
                if (v == d) return 1;
            }
        }
    }
    return 0;
}

int cur[N];
int dfs(int u, int exp) {
    if (u == d) return exp;
    for (int& i = cur[u], v, t; i >= 0; i = nxt[i]) {
        if (flow[i] && dis[v=ver[i]] == dis[u]+1 &&
            (t = dfs(v, min(exp, flow[i]))) > 0) {
            flow[i] -= t; flow[i^1] += t;
            return t;
        }
    }
    return 0;
}

int dinic() {
    int i, ret(0), delta;
    while (bfs()) {
        for (i = 0; i < nd; ++i) cur[i] = head[i];
        while ((delta = dfs(s, inf))) ret += delta;
    }
    return ret;
}

int in[N], out[N], n, m;
ii p[M];
bool check(int mid) {
    int exp = 0, i;
    memset(in, 0, sizeof in);
    memset(out, 0, sizeof out);
    init(n+2, 0, n+1);
    for (i = 0; i < m; ++i) {
        int u = p[i].first, v = p[i].second;
        out[u]++; in[v]++;
        add(u, v, 1);
    }
    for (i = 1; i <= n; ++i) {
        if (out[i] > mid) {
            add(0, i, out[i] - mid);
            exp += out[i] - mid;
        }
        if (out[i] < mid) add(i, n+1, mid - out[i]);
    }
    int f = dinic();
    return exp == f;
}

void print() {
    for (int i = 1; i <= n; i++) {
        for (int j = head[i]; j != -1; j = nxt[j]) {
            if (j&1) continue;
            int v = ver[j];
            if (v < 1 || v > n || v < i) continue;
            if (flow[j]) cout << i << ' ' << v << '\n';
            else cout << v << ' ' << i << '\n';
        }
    }
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        p[i] = {a, b};
    }
    int l = -1, r = n;
    while (r - l > 1) {
        int mid = (l+r)/2;
        if (check(mid)) r = mid; else l = mid;
    }
    if (check(l)) cout << l << '\n';
    else {
        check(r);
        cout << r << '\n';
    }
    print();
    return 0;
}