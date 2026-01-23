//
// Created by Psy.C on 2026/1/23.
//
/**
 * F[u][i][j]表示在节点u的子树中，以颜色i开始，选j个节点的最小代价
 * G[u][i]表示节点u子树中选择i个节点的最小代价
*Dis[N + 1][N + 1]: 距离矩阵，存储任意两点间最短距离
head[N + 1]: 邻接表头指针
Size[N + 1]: 每个节点子树的大小
Cost[N + 1]: 每个节点的成本
num, Sum, n, m: 边数、总成本、节点数、最大距离
 *
 *终点vet、下一条边next、权重val
*edge[num].next = head[u];: 插入到u的邻接表头部
head[u] = num;: 更新u的邻接表头
 *
*u 是当前节点
v 是u的一个子节点
i 是颜色编号（也代表节点i）
k 是总共要选择的节点数
l 是在v子树中选择的节点数
k-l 是在u子树中选择的节点数
*F[u][i][k - l + 1]
在u的子树（除了v子树外）中选择 k-l+1 个节点的最小代价
注意这里是 k-l+1 而不是 k-l，多了一个1
使用颜色i（即节点i的颜色）作为连接
F[v][i][l]
在v的子树中选择 l 个节点的最小代价
同样使用颜色i（节点i的颜色）
(1 - Cost[i])
这是要减去的重复计算部分
Cost[i] 是节点i的成本值
1 - Cost[i] 表示使用节点i作为连接点的净收益
 *
*F[u][i][k - l + 1] 中包含了节点i的信息（因为要选择k-l+1个节点，比原来多1）
F[v][i][l] 中也包含了节点i的信息
由于两个子树都要通过节点i连接，所以节点i被重复计算了一次
因此要减去 (1 - Cost[i]) 来消除重复
为什么加1？
k-l+1 中的+1是因为：

当两个子树都使用相同的颜色i作为连接时
节点i在两个子树的计算中都被视为"必须包含"的节点
所以实际在u子树部分要多计算一个节点i
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define sqz main
#define ll long long
#define reg register int
#define rep(i, a, b) for (reg i = a; i <= b; i++)
#define per(i, a, b) for (reg i = a; i >= b; i--)
#define travel(i, u) for (reg i = head[u]; i; i = edge[i].next)
const int N = 500, INF = 0x3f3f;
ll read(){
    ll x = 0; int zf = 1; char ch;
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();//跳过非数字和负号字符
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();//读取数字字符并构建数值
    return x * zf;
}
short F[N + 1][N + 1][N + 1], G[N + 1][N + 1];
int Dis[N + 1][N + 1], head[N + 1], Size[N + 1], Cost[N + 1], num = 0, Sum = 0, n, m;
struct node
{
    int vet, next, val;
}edge[2 * N + 5];
void add(int u, int v, int w)
{
    edge[++num].vet = v;
    edge[num].next = head[u];
    edge[num].val = w;
    head[u] = num;
}
void dp(int u, int fa)
{
    travel(i, u)
    {
        int v = edge[i].vet;
        if (v == fa) continue;
        dp(v, u);
    }
    rep(i, 1, n)
    {
        if (Dis[u][i] > m) continue;
        Size[u] = 1;  F[u][i][1] = 1 - Cost[i];//初始化单个节点的状态
        travel(j, u)
        {
            int v = edge[j].vet;
            if (v == fa) continue;
            per(k, min(Size[u] + Size[v], Sum), 0)//从大到小枚举合并后节点数
            {
                int now = INF, First = max(k - Size[u], 0);//计算v子树至少需要选择的节点数
                ///u子树选k-l个，v子树选l个
                ///两棵子树都用同一种颜色连接
                rep(l, First, min(k, Size[v])) now = min(now,
                    min(F[u][i][k - l] + G[v][l],
                        l == First ? INF : F[u][i][k - l + 1] + F[v][i][l] - (1 - Cost[i])));
                F[u][i][k] = now;
            }
            Size[u] += Size[v];
        }
    }
    rep(i, 1, min(Sum, Size[u]))
        rep(j, 1, n) G[u][i] = min(G[u][i], F[u][j][i]);
}
int sqz()
{
    memset(Dis, INF, sizeof Dis); memset(F, INF, sizeof F); memset(G, INF, sizeof G);
    n = read(), m = read();
    rep(i, 1, n) Cost[i] = read(), Sum += Cost[i];
    rep(i, 1, n - 1)
    {
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
        Dis[u][v] = Dis[v][u] = w;
    }
    rep(i, 1, n) Dis[i][i] = 0;
    rep(k, 1, n)
        rep(i, 1, n)
            rep(j, 1, n)
                Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);//所有点对间的最短距离
    dp(1, 0);
    printf("%d\n", G[1][Sum] == INF ? -1 : G[1][Sum]);
    return 0;
}