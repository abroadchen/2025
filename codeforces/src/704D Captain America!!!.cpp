//
// Created by Psy.C on 2026/4/19.
//
/**
e[M]: 边的终点数组
tot: 边的总数（从1开始）
t[M]: 链式前向星的next指针
head[N]: 邻接表头节点
add: 添加边，同时添加反向边（容量为0）
构建层次图，只有容量>0的边才能通过
hi[N]: 当前弧数组
处理上下界网络流问题
d[i]: 节点i的供需量
n: 点的数量
m: 限制数量
b[2]: 红色和蓝色的代价
c[2]: 颜色字符
p[N]: 点坐标
cx, cy: 每个x/y坐标上的点数
fx, fy: 坐标到节点编号的映射
dx, dy: x/y坐标的限制值
输入点数、限制数、两种颜色的代价
确保b[0] ≤ b[1]（红色代价较小）
统计每个坐标上的点数
复制限制值
为坐标分配连续编号
每个点连接其x坐标节点和y坐标节点，流量[0,1]
o=1: x坐标限制
o=2: y坐标限制
更新最小限制值
c: 该坐标上的点数
d: 限制值
l, r: 计算流量的下界和上界
l = (c-d)/2+((c^d)&1): 确保满足限制条件的最小红色点数
r = (c+d)/2: 最大红色点数

x: 起始节点
y: 目标节点
z: 边的容量
o: 是否添加反向边（默认为1）
执行过程:
++tot: 边编号递增
e[tot] = y: 设置边的终点
f[tot] = z: 设置边的容量
t[tot] = head[x]: 设置next指针
head[x] = tot: 更新邻接表头
if (o) add(y, x, 0, 0): 添加反向边，容量为0，不递归添加反向边
功能: 构建层次图（BFS）
返回: 是否存在从源点到汇点的增广路径
执行过程:
初始化距离数组d
从源点S开始BFS
只遍历容量>0且未访问的节点
如果到达汇点T，返回true
功能: DFS增广（当前弧优化）
参数:
x: 当前节点
nwf: 当前路径的最小剩余容量
返回: 实际增广的流量
执行过程:
如果到达汇点，返回剩余容量
遍历当前节点的邻接边（当前弧优化）
只走满足层次图条件且有剩余容量的边
递归增广，更新残量图
如果增广量为0，标记节点不可达
功能: Dinic算法主函数
执行过程:
循环直到无法建立层次图
每次建立层次图后，重置当前弧
不断进行增广直到当前层次图无增广路
累加最大流

功能: 添加有上下界的边
参数:
x, y: 起终点
l, r: 流量下界和上界
执行过程:
添加容量为r-l的边（主要流量）
d[y] += l, d[x] -= l: 记录供需关系
功能: 检查上下界网络流可行性
返回: 是否存在可行流
执行过程:
添加超级源点和超级汇点
对于正需求节点，从超级源点连边
对于负需求节点，连向超级汇点
检查最大流是否等于总需求

功能: 求有源汇上下界最大流
返回: 是否成功
执行过程:
添加汇点到源点的无限容量边
检查可行性
重新设置源汇点，求最大流


1. 节省空间
坐标值可能很大（比如10^9），但实际不同的坐标数量很少
解决方案: 将原始坐标映射到连续的小整数
2. 便于建图
网络流算法需要连续的节点编号
用离散化后的编号可以方便地创建节点和边
避免使用巨大的稀疏矩阵
3. 提高算法效率
网络流的时间复杂度与节点数相关
节点数从10^9降到10^5，效率大幅提升
4. 维护对应关系
map<int, int> fx, fy;  // 原坐标 -> 节点编号
map<int, int> cx, cy;  // 原坐标 -> 点的数量
保留了原坐标的语义信息
便于处理针对特定坐标的限制
5. 简化限制处理
限制仍然作用在原始坐标上
但实际建图使用离散化后的编号
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+7, M = 1e6+7;
constexpr ll inf = 1e18;
namespace Dinic {
    int e[M], tot=1, t[M], head[N];
    ll f[M];
    void add(int x, int y, ll z, int o=1) {
        e[++tot] = y, f[tot] = z, t[tot] = head[x], head[x] = tot;
        if (o) add(y, x, 0, 0);
    }
    int d[N], n, S, T;
    bool bfs() {
        for (int i = 1; i <= n; ++i) d[i] = 0;
        queue<int> q; q.push(S), d[S] = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = head[x]; i; i = t[i]) {
                int y = e[i]; ll z = f[i];
                if (d[y] || !z) continue;
                q.push(y), d[y] = d[x] + 1;
                if (y == T) return 1;
            }
        }
        return 0;
    }
    int hi[N];
    ll dinic(int x, ll nwf) {
        if (x == T) return nwf;
        ll rst = nwf;
        for (int& i = hi[x]; i; i = t[i]) {
            int y = e[i]; ll z = f[i];
            if (d[y] != d[x] + 1 || !z) continue;
            ll k = dinic(y, min(z, rst));
            if (!k) d[y] = 0;
            else f[i] -= k, f[i^1] += k, rst -= k;
            if (!rst) break;
        }
        return nwf - rst;
    }
    ll mxf;
    void main() {
        while (bfs()) {
            for (int i = 1; i <= n; ++i) hi[i] = head[i];
            ll now;
            while ((now=dinic(S, inf))) mxf += now;
        }
    }
}

namespace no_ {
    ll d[N], s;
    void add(int x, int y, ll l, ll r) {
        Dinic::add(x, y, r-l), d[y] += l, d[x] -= l;
    }
    bool main() {
        Dinic::S = Dinic::n+1, Dinic::T = Dinic::n+2;
        for (int i = 1; i <= Dinic::n; ++i) {
            if (d[i] > 0) Dinic::add(Dinic::S, i, d[i]), s += d[i];
            else if (d[i] < 0) Dinic::add(i, Dinic::T, -d[i]);
        }
        Dinic::n += 2, Dinic::main(), Dinic::n -= 2;
        return Dinic::mxf == s;
    }
}
namespace yes_ {
    int S, T;
    bool main() {
        no_::add(T, S, 0, inf);
        if (!no_::main()) return 0;
        Dinic::S = S, Dinic::T = T, Dinic::mxf = 0;
        return Dinic::main(), 1;
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, m, b[2], t;
char c[2];
ii p[N];
map<int, int> cx, cy, fx, fy, dx, dy;
int main() {
    fast;
    rd(n), rd(m), rd(b[0]), rd(b[1]);
    c[0] = 'r', c[1] = 'b';
    if (b[0] > b[1]) swap(b[0], b[1]), swap(c[0], c[1]);
    for (int i = 1; i <= n; ++i) {
        rd(p[i].first), rd(p[i].second);
        ++cx[p[i].first], ++cy[p[i].second];
        fx[p[i].first] = fy[p[i].second] = 0;
    }
    //坐标离散化
    for (auto [fst, snd] : cx) dx[fst] = snd;
    for (auto [fst, snd] : cy) dy[fst] = snd;
    for (const auto key: fx | views::keys) fx[key] = ++t;
    for (const auto key: fy | views::keys) fy[key] = ++t;
    //建图：点与坐标的连接
    for (int i = 1; i <= n; ++i)
        no_::add(fx[p[i].first], fy[p[i].second], 0, 1);
    //处理限制
    for (int i = 1, o, x, y; i <= m; ++i) {
        rd(o), rd(x), rd(y);
        if (o == 1 && dx.contains(x)) dx[x] = min(dx[x], y);
        if (o == 2 && dy.contains(x)) dy[x] = min(dy[x], y);
    }
    //计算每个坐标的流量限制
    for (auto [fst, snd] : fx) {
        int c = cx[fst], d = dx[fst],
        l = (c-d)/2+((c^d)&1), r = (c+d)/2;
        if (l > r) return write(-1), 0;
        no_::add(t+1, snd, l, r);
    }
    for (auto o : fy) {
        int c = cy[o.first], d = dy[o.first],
        l = (c-d)/2+((c^d)&1), r = (c+d)/2;
        if (l > r) return write(-1), 0;
        no_::add(o.second, t+2, l, r);
    }
    //求解和输出
    yes_::S = ++t, yes_::T = ++t, Dinic::n = t;
    if (!yes_::main()) return write(-1), 0;
    ll ans = 0;
    string s;
    for (int i = 1, j = 2; i <= n; ++i, j += 2)
        ans += b[Dinic::f[j]], s += c[Dinic::f[j]];
    cout << ans << '\n' << s;
    return 0;
}