//
// Created by Psy.C on 2026/9/27.
//
/**
N：点数上限（1e3）。
M：边数上限（301）。
K：存边的边表数组大小（链式前向星存边数组，含正反两条）。
inf："无穷大"= 1e6，用作容量上界（本题中表示"可选/不限"的极大容量
ver[i]：第 i 条弧的终点；e[i]：容量；nxt[i]：下一条弧编号；head[u]：点 u 的弧链表头。
tot 从 1 开始递增，是为了利用 i^1 取反向弧的技巧（1 和 2 成对、3 和 4 成对……）。
add(u,v,w)：加入正向边（容量 w）和反向边（容量 0）各一条。凑成一对，索引分别为 tot 和 tot-1
dep[] 记录每个点的层次（到源点的距离）。
标准 BFS 分层。只走剩余容量 e[i] > 0 的边。
一旦到达 t 立即返回 true（Dinic 中只要本次 BFS 存在到汇点的路就继续找增广路）
cur[] 当前弧优化：cur[x] 从上次推进位置继续，避免重复扫描。
递归沿分层图推进，k 是从子结点返回的实际增广量。
若 k==0，说明该子结点在此分层中不可再贡献，置 dep=0 做剪枝。
e[i]-=k, e[i^1]+=k：正向边减、反向边加（可回退）。
返回 flow-res，即本次 DFS 实际放行多少流量
从源点沿残量网络（还有剩余容量的边）遍历，vis 标记从 s 可达的顶点。
用于判定最小割：残量网络中源侧可达点集 S（vis=1）与汇侧 T（vis=0）之间的边就是割边候选

读数：n 个点、m 条边、源点 s、汇点 t
读 m 条边 (a[i], b[i], g[i])：

若 g[i]==1（某种"可断/关键类型"边）：加入容量 1 的正向边，再加一条容量为 inf 的反向边 add(b,a,inf)——表示反向容量为 inf（即这条边"反向不可随便断/必须存在某条路径"）。
若 g[i]==0（普通边）：只加一条容量为 inf 的正向边，表示不可切断（容量极大）。
所以模型设计：容量 1 的边 = 最小割要考虑的"切割代价为 1"的边；容量 inf 的边表示不可被割（容量极大）
标准 Dinic 主循环：反复 BFS 分层 + 多次 DFS 增广直到 BFS 失败。mx 累加得到最大流值 = 最小割值（割掉"容量 1 边"的最少条数）。
从 s 沿残量网络 DFS，标记 vis（得到源侧集合 S）。
输出最小割值 mx
清空图（head 归 0、边计数 tot 重置为 1、mx 归 0），为第二阶段重建图。
add(t,s,inf)：在原汇 t 与源 s 之间加一条容量 inf 的反向边——这是关键技巧：把"原 t，s 之路"封成不可断大容量，强制后续从新源 s' 到新汇 t' 的割必须经过原图"关键边"。
重新定义源/汇为 s=0（新超源）、t=n+1（新超汇）
对每条关键边 g[i]==1 构造第二阶段网络：

add(a[i],b[i],inf-1)：重新加原方向边，容量改为 inf-1（略小于 inf，形成"逼割"容量）。
add(s, b[i], 1)：从新源 s 连到 b[i]，容量 1（给 b 侧送 1 单位）。
add(a[i], t, 1)：a[i] 连到新汇 t，容量 1。
es[i]=tot-4：记录这条关键边对应的正向弧在边表中的索引（因为每次 add 会插入两个 tot，4 次 add = 8 条弧，减 4 得第一条正向边索引）——留待输出容量。
（第二阶段思路：通过超源超汇对每条 g=1 边"加压"，让其成为新的最小割边，从而用最终残量判断每条边能否/必须被割。）
第二次 Dinic 求最大流 mx（此时网络结点编号为 0..n+1）
针对每条边输出答案区间 [L, R]：

普通边 g[i]==0：输出 0 1000000，表示该边"从不被割到不可割"，区间 [0, 1e6]。
关键边 g[i]==1：
e[es[i]]+1：残量网络上该正向弧的剩余容量 +1，作为装载量下限 L。
若 vis[a[i]] != vis[b[i]]（a 在源侧、b 在汇侧，即这条边当前正被割断）→ 输出 L L（上下界相等，该边必须恰好割掉 L）。
否则输出 L 1000000（下界 L、上界 inf，允许范围）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e3+1, M = 301, K = 3e4+1, inf = 1e6;

int ver[K], tot(1), head[M], e[K], nxt[K];
void add(int u, int v, int w) {
    ver[++tot] = v, e[tot] = w, nxt[tot] = head[u], head[u] = tot;
    ver[++tot] = u, e[tot] = 0, nxt[tot] = head[v], head[v] = tot;
}

int dep[M], s, t;
queue<int> q;
bool bfs() {
    memset(dep, 0, sizeof(dep));
    while (!q.empty()) q.pop(); q.push(s); dep[s] = 1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i]) {
            if (e[i] && !dep[ver[i]]) {//有剩余容量且未被分层
                q.push(ver[i]);
                dep[ver[i]] = dep[x] + 1;
                if (ver[i] == t) return true;//早停：只要到汇点就认为有增广路
            }
        }
    }
    return false;
}

int cur[M];
int dinic(int x, int flow) {
    if (x == t) return flow;
    int res = flow, k;
    for (int i = cur[x]; i&&res; i = nxt[i]) {
        cur[x] = i;
        if (e[i]&&dep[ver[i]] == dep[x] + 1) {//只走分层图中下一层
            k = dinic(ver[i], min(e[i],res));
            if (!k) dep[ver[i]] = 0;//该点无增广贡献，剪枝
            res -= k; e[i] -= k; e[i^1] += k;//更新边与反向边容量
        }
    }
    return flow - res;//实际增广量
}

int vis[M];
void dfs(int x) {
    vis[x] = 1;
    for (int i = head[x]; i; i = nxt[i])
        if (!vis[ver[i]]&&e[i])//只沿剩余容量>0 的边走
            dfs(ver[i]);
}

int n, m, a[N], b[N], g[N], flow, mx, es[N];
int main() {
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a[i],&b[i],&g[i]);
        if(g[i]) add(a[i],b[i],1),add(b[i],a[i],inf);
        else add(a[i],b[i],inf);
    }
    while(bfs()){
        for(int i=1;i<=n;i++) cur[i]=head[i];
        while((flow=dinic(s,inf))) mx+=flow;
    }
    dfs(s);
    printf("%d\n",mx);
    for(int i=1;i<=n;i++) head[i]=mx=0,tot=1;
    add(t,s,inf);
    s=0,t=n+1;
    for(int i=1;i<=m;i++){
        if(g[i]){
            add(a[i],b[i],inf-1);
            add(s,b[i],1);
            add(a[i],t,1);
            es[i]=tot-4;
        }
    }
    while(bfs()){
        for(int i=0;i<=n+1;i++) cur[i]=head[i];
        while((flow=dinic(s,inf))) mx+=flow;
    }
    for(int i=1;i<=m;i++){
        if(g[i]){
            if(vis[a[i]]!=vis[b[i]]) printf("%d %d\n",e[es[i]]+1,e[es[i]]+1);
            else printf("%d 1000000\n",e[es[i]]+1);
        }
        else printf("0 1000000\n");
    }
    return 0;
}