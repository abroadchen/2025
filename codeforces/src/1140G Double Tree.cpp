//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
li	Dijkstra 优先队列的元素：{dist, node}
ii	查询记录：{目标点w, 查询编号id}（简写为 ii）
N	点数上限（拆点后 2n）
inf / INF	极大值，INF 用于距离，inf 用于找重心
edge{v,w}	一条带权边
e[N]	原图的邻接表（带权）
add(u,v,w)	加一条双向带权边
注意：e（带权图）与后面 G（分治树，不带权）是两套不同结构。
rt, mx	找重心时记录根节点、当前最小最大子树
sz[N]	子树大小（找重心 + 分大小）
vis[N]	点分治标记：已作为重心被删的点
col[N]	标记当前递归块内的点（是否"激活"参与最短路）
inq[N]	Dijkstra 的"已在堆中/已出队"标记
G[N]	树结构，跑点分治用（不带权）
d1,d2	分别从重心 rt 和 rt+n 出发的最短路
ans[N]	每个查询的答案（取所有重心下的最小值）
Q[v]	起点为 v 的查询列表，元素 {终点, 查询id}
u：当前递归块内某个点；ver：当前块的大小（点数）。
作用：对以 u 为代表的连通块做一次点分治
rt=0, mx=inf	初始化重心候选
sz[u]=1	当前节点子树大小初始为 1
now=0	记录"去掉 u 后，最大连通块大小"
遍历 G[u] 中的儿子	只走未访问 !vis[v]、非父 v!=fat 的点
递归后 sz[u]+=sz[v]	累加子节点子树大小
now = max(now,sz[v])	now 取各子树的最大
now = max(now, ver-sz[u])	还要考虑"父亲那一侧"的大小（ver 是整块大小）
if (mx>now) mx=now, rt=u	更新最小最大连通块 → 这个点就是重心候选
这是标准找重心：选一个点，删掉它后剩下的最大连通块最小

seq	存当前块内所有点（用于 Dijkstra 的范围限制）
col[u]=col[u+n]=1	标记 u 和 u+n 都被"激活"，Dijkstra 只在这些点上跑
sz[u]=1	重算子树大小
递归收集	把块内所有点加入 seq，并累加 sz
dfs2(dfs2,rt,0)	从重心触发收集
col 是关键：Dijkstra 只处理 col[v] 为真的点，避免跑到块外
dijkstra(S, dis)	从起点 S 跑最短路，结果写入数组 dis
初始化	把 seq 内所有点（及其拆点+n）距离设为 INF，inq 清 0
优先队列	小根堆 {dist,node}，起点 S 距离 0
出队判断	若已处理过（inq[u]）则跳过
松弛	对 col[v] 激活的邻居做 dis[v] > dis[u]+w 的松弛
结尾清 inq	恢复标记供下次使用
两次调用	dijkstra(rt,d1) 和 dijkstra(rt+n,d2)：分别从原重心点和重心拆点出发
跑两次最短路是因为查询跨越层的路径需要从两个拆点角度考虑
第一层遍历 seq	每个点 v（原层）
第二层遍历 Q[v]	所有以 v 为起点的查询 {w:id}
if (col[w])	只处理终点 w 也在当前块内的查询
ans[id] = min(...)	用"过重心的路径"更新答案
点分治的核心更新：一条最短路径若经过当前重心，则它 = 起点到重心的最短路 + 重心到终点的最短路。用 min(d1[起点]+d1[终点], d2[起点]+d2[终点]) 取小的那一种（走原层或拆点层）。第二段对 Q[v+n] 的处理同理，是处理以拆点为起点的查询

_rt = rt	保存重心编号（后面 rt 可能被改）
vis[rt]=1	标记重心已作为分治中心被删
清空 col	把这个块所有点取消激活，供下一层递归重新标记
遍历重心的邻居	对每个未访问的块 solve(v,sz[v]) 递归分治
递归深度 O(log n)，把大问题切成多块分而治之，最终每个查询在每一层都能尝试一次最优路径 → 取全局最小
add(i, i+n, w)	给点 i 和它的拆点 i+n 之间加边（w 权）
rep(i,n)	对每个点处理
每个节点 i 变成两个点，通过权 w 的边连接——这形成了两套平行层，点带权切换就是"层间转移"

读 4 个数	x,y 及 w1,w2
add(x,y,w1)	原层边（权 w1）
add(x+n,y+n,w2)	拆点层边（权 w2）
G[x].push_back(y) 等	在分治树上加边（不带权，用于点分治）
注意：G 存的是树结构（用于分治、找重心），而 e 存的是带权图（用于最短路）。两者边集合结构一致但用途不同
输入格式	每个点以 2k-1=原层、2k=拆点层 编码
if (u&1)	u 是奇数 → 在第 1 层，编号换算成 (u+1)/2
else	u 是偶数 → 拆点层，换算成 u/2 + n
Q[u].emplace_back(v,i)	把查询存进双向：Q[u] 加 {v,i}，Q[v] 加 {u,i}
把查询双向存储，是为了在分治时无论从哪端都能命中
memset(ans,0x3f,...)	把 ans 初始化为极大值（0x3f3f3f3f）
solve(1,n)	对整个大小为 n 的块做点分治
rep(i,m) cout	输出每个查询答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
#define ll long long
#define li pair<ll,int>
#define ii pair<int,int>
using namespace std;

constexpr int N = 6e5+10, inf = 1e9;
constexpr ll INF = 1e18;
struct edge { int v; ll w; };

vector<edge> e[N];
void add(int u, int v, ll w) { e[u].push_back({v,w}); e[v].push_back({u,w}); }

int rt, mx, sz[N], vis[N], col[N], n, inq[N];
vector<int> G[N];
ll d1[N], d2[N], ans[N];
vector<ii> Q[N];
void solve(int u, int ver) {
    rt = 0, mx = inf;
    auto dfs = [](auto dfs, int u, int fat, int ver) -> void {
        sz[u] = 1;
        int now = 0;
        for (int v : G[u]) if (v != fat && !vis[v])
            dfs(dfs,v,u,ver), sz[u] += sz[v], now = max(now, sz[v]);
        now = max(now, ver-sz[u]);
        if (mx > now) mx = now, rt = u;
    };
    dfs(dfs,u,0,ver);
    vector<int> seq;
    auto dfs2 = [&](auto dfs2, int u, int fat) -> void {
        sz[u] = 1; col[u] = col[u+n] = 1; seq.push_back(u);
        for (int v : G[u]) if (v != fat && !vis[v])
            dfs2(dfs2,v,u), sz[u] += sz[v];
    };
    dfs2(dfs2,rt,0);
    auto dijkstra = [&](int S, ll *dis) {
        for (int u : seq) dis[u] = dis[u+n] = INF, inq[u] = inq[u+n] = 0;
        priority_queue<li,vector<li>,greater<>> q; q.emplace(dis[S]=0,S);
        while (!q.empty()) {
            int u = q.top().second; q.pop();
            if (inq[u]) continue;
            inq[u] = 1;
            for (auto [v,w] : e[u]) if (col[v])
                if (dis[v] > dis[u]+w) q.emplace(dis[v]=dis[u]+w,v);
        }
        for (int u : seq) inq[u] = inq[u+n] = 0;
    };
    dijkstra(rt,d1); dijkstra(rt+n,d2);
    for (int v : seq) for (auto [w,id] : Q[v]) if (col[w])
        ans[id] = min(ans[id],min(d1[v]+d1[w],d2[v]+d2[w]));
    for (int v : seq) for (auto [w,id] : Q[v+n]) if (col[w])
        ans[id] = min(ans[id],min(d1[v+n]+d1[w],d2[v+n]+d2[w]));
    int _rt = rt; vis[rt] = 1;
    for (int v : seq) col[v] = col[v+n] = 0;
    for (int v : G[_rt]) if (!vis[v]) solve(v,sz[v]);
}

int m;
int main() {
    fast;
    cin >> n; ll w;
    rep(i,n) cin >> w, add(i,i+n,w);
    rep(i,n-1) {
        int x, y; ll w1, w2; cin >> x >> y >> w1 >> w2;
        add(x,y,w1), add(x+n,y+n,w2);
        G[x].push_back(y), G[y].push_back(x);
    }
    cin >> m;
    rep(i,m) {
        int u, v; cin >> u >> v;
        if (u&1) u = (u+1)>>1; else u = (u>>1)+n;
        if (v&1) v = (v+1)>>1; else v = (v>>1)+n;
        Q[u].emplace_back(v,i); Q[v].emplace_back(u,i);
    }
    memset(ans,0x3f,sizeof ans);
    solve(1,n);
    rep(i,m) cout << ans[i] << '\n';
    return 0;
}