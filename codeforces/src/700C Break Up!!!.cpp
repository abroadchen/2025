//
// Created by Psy.C on 2026/4/17.
//
/**
to: 边指向的目标节点
nxt: 链式前向星中的下一条边索引
cost: 边的权重/费用
id: 边的编号
cut: 标记是否为桥（割边）
valid: 标记边是否有效（未被删除）
head[N]: 邻接表头部数组，记录每个节点的第一条边
tot: 边的总数计数器

在节点u和v之间添加权值为w的无向边
将边信息存储到e[tot]中
初始化该边不是桥且有效
更新head[u]并递增tot

dfn[N]: DFS访问时间戳
low[N]: 能回溯到的最小时间戳
tim: 当前时间戳
br: 桥的数量
实现Tarjan算法找图中的桥（割边）
dfn[u] = low[u] = ++tim: 设置当前节点的时间戳
cnt用于处理重边情况
遍历所有邻接点
如果是树边，则递归DFS
如果找到后向边，更新low[u]
如果low[v] > dfn[u]，说明边(u,v)是桥

vis[N]: 访问标记数组
vq: 存储从s到t的路径
dfs: 在图中寻找从u到dest的路径，返回是否存在路径
第二个DFS（用于验证删除边后的连通性）

重置所有边的cut标记为false
重置时间戳和桥计数器
清空dfn数组

s, t: 源点和目标点
检查从s到t是否有路径，如果没有则输出0
对于路径上每条边：
删除这条边，检查是否还有路径
如果没有路径了，这条边就是关键边，更新单边最小值
如果还有路径，运行Tarjan找桥，寻找必须删除的第二条边
如果没找到解，输出-1
如果只需要删除1条边，输出花费、数量1、边ID
如果需要删除2条边，输出花费、数量2、两个边ID



u: 当前访问的节点
pre: 当前节点的父节点（DFS树中的父亲）
dfn[u]: 节点u在DFS搜索中的发现时间
low[u]: 从节点u出发，能通过后向边回到的最早节点的发现时间
++tim: 时间戳递增，确保每个节点有唯一的发现时间
用于处理重边（两个节点之间的多条边）的情况
遍历节点u的所有邻接边
v = e[i].to: 获取邻接节点v
if (!e[i].valid) continue;: 跳过已失效的边
如果邻接节点v是父节点且是第一次遇到，跳过这条边
cnt++防止同一条边的反向边被重复考虑
如果节点v还没有被访问过（即v是u的子节点）
递归调用tarjan访问子节点v
回溯时更新low[u] = min(low[u], low[v])
这表示如果子节点v能回溯到更早的祖先，那么当前节点u也能通过子节点v到达那个祖先
核心判断条件: low[v] > dfn[u]
含义：从子节点v无法回到节点u或u的祖先节点
这意味着边(u,v)是桥（割边），因为删除这条边会使得图不连通
br++: 桥计数器增加
e[i].cut = true; e[i^1].cut = true;: 标记正向边和反向边都是桥
如果节点v已经被访问过（即不是树边，而是后向边）
更新low[u] = min(low[u], dfn[v])
这表示节点u可以通过后向边直接到达节点v（一个更早的节点）



遍历从s到t的原始路径vq中的每条边i
重置第二次DFS的访问标记数组
获取当前边的ID：i.id是边在边数组中的索引
将当前边及其反向边标记为无效：e[id].valid = false; e[id^1].valid = false
这里使用了异或技巧：如果边a的索引是偶数，其反向边b的索引是奇数=a+1，a^1=b，b^1=a
清空辅助路径容器vq2
情况1：删除边后路径不存在
如果删除边i后，从s到t没有路径了（!dfs2(s, t)）
说明这条边是关键边，删除它就能断开连接
如果这条边的代价比当前最优解更小：
f1 = true; f2 = false: 标记只需删除1条边的情况
res = e[id].cost: 更新最小代价
id1 = (id>>1)+1: 记录这条边的原始编号（由于每条原边对应两条实际边，所以id>>1得到原边号，+1转换为1-based编号）
情况2：删除边后仍有路径
如果删除边i后仍存在从s到t的路径
init(); tarjan(s, -1);: 重新初始化并运行Tarjan算法找桥
此时vq2中存储的是删除边i后的新路径上的边
遍历新路径vq2上的每条边j
检查边j是否是桥（e[j.id].cut为true）
如果是桥，那么删除边i和边j就能断开连接
int add = e[id].cost + e[j.id].cost;: 计算删除这两条边的总代价
如果总代价更优：
f1 = false; f2 = true;: 标记需要删除2条边的情况
res = add;: 更新最小总代价
id1 = (id>>1)+1; id2 = (j.id>>1)+1;: 记录两条边的原始编号
恢复刚才删除的边及其反向边的有效性，为下一次循环做准备

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005, M = 6e4+5, inf = 0x3f3f3f3f;

struct edge {
    int to, nxt, cost, id;
    bool cut, valid;
} e[M];

int head[N], tot;
void add(int u, int v, int w) {
    e[tot] = {v, head[u], w, tot},
    e[tot].cut = false, e[tot].valid = true,
    head[u] = tot++;
}

int dfn[N], low[N], tim, br;
void tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim;
    int cnt = 0;
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        int v = e[i].to;
        if (!e[i].valid) continue;
        if (v == pre && cnt == 0) { cnt++; continue; }
        if (!dfn[v]) {
            tarjan(v, u);
            if (low[u] > low[v]) low[u] = low[v];
            if (low[v] > dfn[u]) {
                br++;
                e[i].cut = true; e[i^1].cut = true;
            }
        } else if (low[u] > dfn[v]) low[u] = dfn[v];
    }
}

bool vis[N];
vector<edge> vq;
bool dfs(int u, int dest) {
    if (u == dest) return true;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        if (!vis[e[i].to] && e[i].valid) {
            if (dfs(e[i].to, dest)) {
                vq.push_back(e[i]);
                return true;
            }
        }
    }
    return false;
}

bool vis2[N];
vector<edge> vq2;
bool dfs2(int u, int dest) {
    if (u == dest) return true;
    vis2[u] = true;
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        if (!vis2[e[i].to] && e[i].valid) {
            if (dfs2(e[i].to, dest)) {
                vq2.push_back(e[i]);
                return true;
            }
        }
    }
    return false;
}

void init() {
    for (int i = 0; i < tot; ++i) e[i].cut = false;
    tim = br = 0;
    memset(dfn, 0, sizeof(dfn));
}

int s, t;
void out() {
    memset(vis, 0, sizeof(vis)); vq.clear();
    if (!dfs(s, t)) {
        cout << "0\n0\n";
        return;
    }
    int res = inf<<1; vq2.clear();
    bool f1 = false, f2 = false;
    int id1 = -1, id2 = -1;
    for (auto & i : vq) {
        memset(vis2, 0, sizeof(vis2));
        int id = i.id; e[id].valid = false; e[id^1].valid = false;
        vq2.clear();
        if (!dfs2(s, t)) {
            if (e[id].cost < res) {
                f1 = true; f2 = false; res = e[id].cost;
                id1 = (id>>1)+1;
            }
        } else {
            init(); tarjan(s, -1);
            for (auto & j : vq2) {
                if (e[j.id].cut) {
                    int add = e[id].cost + e[j.id].cost;
                    if (add < res) {
                        f1 = false; f2 = true; res = add;
                        id1 = (id>>1)+1; id2 = (j.id>>1)+1;
                    }
                }
            }
        }
        e[id].valid = true; e[id^1].valid = true;
    }
    if (res == inf<<1) cout << "-1\n";
    else if (f1 == true && f2 == false)
        cout << res << "\n1\n" << id1 << '\n';
    else if (f2 == true && f1 == false)
        cout << res << "\n2\n" << id1 << ' ' << id2 << '\n';
}

int n, m;
int main() {
    fast;
    cin >> n >> m >> s >> t; s--, t--; tot = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c; a--, b--;
        add(a, b, c); add(b, a, c);
    }
    out();
    return 0;
}