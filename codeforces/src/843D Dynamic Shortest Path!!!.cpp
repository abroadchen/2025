//
// Created by Psy.C on 2026/9/27.
//
/**
若 b < a，把 a 更新为 b 并返回 1（表示发生了更新），否则返回 0。注意 a = b, 1 是逗号表达式，返回 1
若 a < b，把 a 更新为 b，返回是否更新。用于维护"最大"（下方 lmt）
N：点数上限（1e5 多一点）。
inf：极大值，用作"无穷大"。16 进制 0x3f3f3f3f3f3f3f3f 是经典的"大但相加不溢出 long long"的无穷大（约 4.6e18，而 2e5×边长不会爆）
链式前向星数组：

v[i]：第 i 条边的终点；
w[i]：第 i 条边的权值;
nxt[i]：下一条边的编号（链表指针）;
cnt：当前已用边数；
head[u]：以 u 为起点的第一条边编号（每点链表的头）
加边函数：新建一条边（终点 _v，权 _w），头插法挂到 head[u] 链上。cnt 先自增再使用
dis[N]：全局最短距离数组（下面被多次维护）。
dij() 内用静态局部变量：q 是一个小根堆（greater<>），存 <距离, 顶点>；vis[N] 标记已确定最短路的点。用 static 避免每次调用重新分配、内存复用
memset(dis, 63, sizeof(dis))：把 dis 每个字节填 0x63，即把每个 long long 置为 0x63636363... = 0x6363636363636363，恰是你定义的 inf。所以这行等价于把 dis 初始化为 inf。
q.emplace(0, 1)：以源点 1、距离 0 入堆。
dis[1] = 0：源点到自己的距离为 0
取出堆顶 (距离, 顶点 u)，弹出。
if (vis[u]) continue;：若 u 已被确认最短，跳过（惰性删除重复项）。
vis[u] = 1：u 的最短路已确定
遍历 u 的所有出边 (v[i], w[i])。
chkmin(dis[终点], dis[u]+w[i])：若经 u 到终点更短则更新；更新成功则把新距离入堆
q[N]：一个桶数组，q[i] 是距离增量为 i 的顶点队列（Dial 算法用桶）。
f[N]：增量数组——在边权加完后，f[i] 表示"从源点到 i，相对原 dis 额外增加的代价"
n 点数、m 边数、qs 查询次数。
静态变量：读入用的临时变量 uu,vv,ww；lmt 记录当前桶用到的最远下标；op,x 存操作类型和参数
读入 m 条边（有向图，只加一次），建图。
跑一次标准 Dijkstra 得到初始 dis
每轮读操作 op 和参数 x
op == 1：查询点 x 的当前最短距离。
若 dis[x] < inf（可达），输出 dis[x]；否则输出 -1（不可达）
op == 2：读取 x 条边的编号，把对应边权 w[i] 各 +1（++w[编号]）。这是"批量给若干条边权值加 1"
初始化本轮重算：
q[0].push(1)：源点放入第 0 号桶（源点增量 0）。
f 全部设为 inf（memset 63），源点 f[1]=0。
lmt = 0：当前桶最高下标为 0
外层遍历桶 0..lmt（Dial 扫描）；内层处理当前桶所有顶点。
u 出队。if (f[u] < i) continue;：若 u 的实际增量已小于桶号（可能被更优更新过），跳过（类似惰性删除）
遍历 u 的每条出边 (v[j], w[j])。
计算 t = f[u] - dis[v[j]] + dis[u] + w[j]，这是关键势能式：
dis[u]+w[j] 是走这条边从 u 的"实际新距离候选"；
减去 dis[v[j]] 后即为相对原最短路的增量；
再加上 f[u]（u 自己的增量）。
也就是说：t = "终点 v[j] 的增量候选"（基于原 dis 势能的 Johnson 式重标号）。
若 f[v[j]] > t，则更新终点的增量
更新 f[v[j]] = t。
若 t 不超过 min(x, n-1)（增量不可能超过"改动的边数和/或最短路最多经过 n-1 条边"的上界），把终点放入第 t 号桶，并更新 lmt 为最大桶下标（chkmax）。
（min(x, n-1) 是增量理论上界：每次 +1 共 x 条边，且一条最短路至多 n-1 条边，故增量 ≤ min(x, n-1)。超过该上界的桶无需建立。）
桶扫描结束后，对每个点 2..n：把原最短距离 dis[i] 加上增量 f[i]，得到新的最短距离；用 min(inf, ...) 防溢出成超过 inf（或保持不可达）。
源点 1 到 1 距离恒为 0，不更新。
至此一轮 op==2 完成，dis 已更新为边权修改后的新最短路
 */
#include <bits/stdc++.h>
#define ll long long
#define li pair<ll, int>
using namespace std;

template<typename T>
bool chkmin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<typename T>
bool chkmax(T& a, T b) {
    return a < b ? a = b, 1 : 0;
}


constexpr int N = 1e5+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
int v[N], nxt[N], w[N], cnt, head[N];
inline void add(int u, int _v, int _w) {
    v[++cnt] = _v, w[cnt] = _w, nxt[cnt] = head[u], head[u] = cnt;
}

ll dis[N];
void dij() {
    static priority_queue<li, vector<li>, greater<>> q;
    static int vis[N];
    memset(dis, 63, sizeof(dis)); q.emplace(0, 1); dis[1] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
            if (chkmin(dis[v[i]], dis[u]+w[i]))
                q.emplace(dis[v[i]], v[i]);
        }
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

queue<int> q[N];
int f[N];
int main() {
    int n = rd(), m = rd(), qs = rd();
    static int uu, vv, ww, lmt, op, x;
    for (int i = 1; i <= m; ++i) {
        uu = rd(), vv = rd(), ww = rd();
        add(uu, vv, ww);
    }
    dij();
    while (qs--) {
        op = rd(), x = rd();
        if (op == 1) {
            if (dis[x] < inf)
                printf("%lld\n", dis[x]);
            else puts("-1");
        } else {
            for (int i = 1; i <= x; ++i) ++w[rd()];
            q[0].push(1);
            memset(f, 63, sizeof(f)); f[1] = 0; lmt = 0;
            for (int i = 0; i <= lmt; ++i) {
                while (!q[i].empty()) {
                    int u = q[i].front(); q[i].pop();
                    if (f[u] < i) continue;
                    ll t;
                    for (int j = head[u]; j; j = nxt[j]) {
                        if (f[v[j]] > (t=(ll)f[u]-dis[v[j]]+dis[u]+w[j])) {
                            f[v[j]] = t;
                            if (t <= min(x, n-1))
                                q[t].push(v[j]), chkmax(lmt, (int)t);
                        }
                    }
                }
            }
            for (int i = 2; i <= n; ++i)
                dis[i] = min(inf, dis[i] + f[i]);
        }
    }
    return 0;
}