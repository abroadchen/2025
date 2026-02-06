//
// Created by Psy.C on 2026/2/6.
//
/**
maxn: 最大节点数
top: 一个很大的数，用于构造网络流图
inf: 无穷大值，表示无限容量
edge: 边结构体，包含目标节点、下一条边索引、边权重
nd[maxn]: 存储所有边
h[maxn]: 链式前向星的头指针数组
cnt: 边的计数器
添加单向边的函数：将u到v的边加入邻接表
添加双向边（残余网络）：正向边容量w，反向边容量0

T: 测试用例数
s, t: 源点和汇点
now: 当前最大节点编号
n, m: 节点数和边数
cur[maxn]: 当前弧优化数组
d[maxn]: 分层图距离数组
que[maxn]: BFS队列
hd, ta: 队列头尾指针
sum: 总流量
从汇点t开始反向BFS构建分层图
memset(d, 0x3f, ...) 将距离数组初始化为无穷大
que[++ta] = t; d[t] = 0; 从汇点开始
for (int i = h[u]; ~i; i = nd[i].nxt) 遍历所有邻接边
if (d[v] > d[u] + 1 && nd[i ^ 1].w) 检查是否有增广路径且反向边有容量
return d[s] < 1e9; 返回源点是否可达

DFS寻找增广路径，fl为当前路径的剩余容量
if (u == t || !fl) return fl; 到达汇点或无剩余容量时返回
for (int& i = cur[u]; ~i; i = nd[i].nxt) 遍历邻接边（当前弧优化）
if (d[u] != d[nd[i].to] + 1 || !nd[i].w) continue; 检查是否在当前层次
wv = dfs(nd[i].to, min(fl, c)); 递归找增广路
nd[i].w -= wv, nd[i ^ 1].w += wv, fl -= wv 更新边容量
if (fl) d[u] = 1e9; 如果还有剩余流量，标记该点不可达

不断执行BFS构建分层图和DFS找增广路
memcpy(cur, h, sizeof(cur)) 重置当前弧
sum += dfs(s, inf) 累加最大流

a[], b[], c[]: 二次函数系数
l[], r[]: 左右边界数组
id[205][505]: 节点ID映射二维数组
f(i, x): 计算二次函数值


初始化邻接表头指针为-1
读入n(项目数)和m(依赖关系数)
设置源点s=1，汇点t=2，当前最大节点now=2
读入n个项目各自的二次函数系数
读入每个项目的左右边界，并统一加上偏移量100
对每个项目i：
从源点向该项目第一个节点连边，容量无穷大
创建该项目的连续节点，分配ID
从最后一个节点向汇点连边，容量无穷大
项目内部相邻节点间连边，容量为top - f(i, j-100)（这是关键，转换为最小割问题）

处理依赖关系：
读入依赖：项目u的第j天依赖项目v的第j-d天
连接相应节点，容量无穷大

总收益 - 最小割 = 最大收益

当 fl -= wv 结果为0时（即 fl 变成0），!(0) = true（1），此时函数会返回
当 fl -= wv 结果非0时（即还有剩余流量），!(非0) = false（0），继续循环



 */
#include <iostream>
#define rep(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long int ll;
constexpr int maxn = 1e5 + 10;
const ll top = 114514191981000LL, inf = top * 1000;
struct edge { int to, nxt; ll w; } nd[maxn]; int h[maxn], cnt = 0;
inline void add(int u, int v, ll w) { nd[cnt].nxt = h[u], nd[cnt].to = v, nd[cnt].w = w, h[u] = cnt++; }
inline void addE(int u, int v, ll w) { add(u, v, w); add(v, u, 0); }
int T, s, t, now, n, m, cur[maxn], d[maxn], que[maxn], hd = 1, ta = 0; ll sum = 0;
inline int bfs() {
	memset(d, 0x3f, (now + 1) * sizeof(int));
	hd = 1, ta = 0; que[++ta] = t; d[t] = 0;
	while (hd <= ta) {
		int u = que[hd++];
		for (int i = h[u]; ~i; i = nd[i].nxt) {
			int v = nd[i].to;
			if (d[v] > d[u] + 1 && nd[i ^ 1].w) d[v] = d[u] + 1, que[++ta] = v;
		}
	}
	return d[s] < 1e9;
}
ll dfs(int u, ll fl) {
	if (u == t || !fl) return fl; ll nw = fl;
	for (int& i = cur[u]; ~i; i = nd[i].nxt) {
		if (d[u] != d[nd[i].to] + 1 || !nd[i].w) continue;
		ll c = nd[i].w, wv = dfs(nd[i].to, min(fl, c));
		if (!(nd[i].w -= wv, nd[i ^ 1].w += wv, fl -= wv)) return nw;
	}
	if (fl) d[u] = 1e9;
	return nw - fl;
}
inline void Dinic() { while (bfs()) memcpy(cur, h, sizeof(cur)), sum += dfs(s, inf); }
ll a[maxn], b[maxn], c[maxn], l[maxn], r[maxn]; int id[205][505];
ll f(int i, int x) { return a[i] * x * x + b[i] * x + c[i]; }
int main() {
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m); s = 1, t = now = 2;
	rep(i, 1, n) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	rep(i, 1, n) scanf("%lld%lld", &l[i], &r[i]), l[i] += 100, r[i] += 100;
	rep(i, 1, n) {
		addE(s, now + 1, inf);
		rep(j, l[i], r[i] + 1) id[i][j] = ++now;
		addE(now, t, inf);
		rep(j, l[i], r[i]) addE(id[i][j], id[i][j + 1], top - f(i, j - 100));
	}
	for (int i = 1, u, v, d = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &d);
		rep(j, l[u], r[u]) addE(id[u][j], id[v][j - d], inf);
	}
	Dinic();
	printf("%lld\n", top * n - sum);
	return 0;
}