//
// Created by Psy.C on 2025/11/1.
//
/*
*N = 50: 最大节点数
M = 10: 预留的数组大小
*Edge 结构体存储每条边的约束条件：
l: 最小流量
h: 最大流量
w: 额外权重
e[N][N]: 边的二维数组，e[i][j] 表示从节点i到节点j的边
n: 节点数量
ans: 最终答案
f[M]: 记录每个节点当前的流量
 *
*u: 当前处理的起始节点
v: 当前处理的目标节点
flow: 从节点u可分配的流量
cost: 当前累计的成本
 *
*终止条件：如果处理完所有节点(u == n)，更新最大成本
节点切换：如果目标节点超出范围(v > n)且当前节点流量分配完(!flow)，则处理下一个节点
流量分配：在合法范围内(i <= e[u][v].h && i <= flow)尝试分配流量i
递归处理：更新目标节点流量，递归处理下一个目标节点
回溯：恢复目标节点流量状态
 *
*输入处理：读取节点数和所有边的信息
初始化：设置答案初始值为-1
枚举初始流量：从0到5*(n-1)枚举初始分配给第一个节点的流量
搜索求解：每次重新初始化状态数组，调用DFS搜索最优解
结果输出：找到非负解则输出，否则输出-1 -1
 *
*u + 1: 下一个要处理的起始节点
u + 2: 下一个起始节点对应的第一个目标节点
 *v + 1: 下一个要处理的目标节点
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 50, M = 10;
struct Edge { int l, h, w; } e[N][N];
int n, ans, f[M];

void dfs(int u, int v, int flow, int cost) {
    if (u == n) {
        ans = max(ans, cost);
        return;
    }
    if (v > n) {
        if (!flow) dfs(u + 1, u + 2, f[u + 1], cost);
    } else {
        for (int i = e[u][v].l; i <= e[u][v].h && i <= flow; ++i) {
            f[v] += i;
            dfs(u, v + 1, flow - i, cost + i * i + (!i ? 0 : e[u][v].w));
            f[v] -= i;
        }
    }
}


int main() {
    scanf("%d",&n);
    int s, ff, l, h, a;
    for (int i = 1; i <= n*(n-1)/2; ++i) {
        scanf("%d%d%d%d%d",&s,&ff,&l,&h,&a);
        e[s][ff].l = l; e[s][ff].h = h;
        e[s][ff].w = a;
    }
    ans = -1;
    for (int i = 0; i <= 5*(n-1); ++i) {
        memset(f,0,sizeof(f));
        dfs(1, 2, i, 0);
        if (ans >= 0) {
            printf("%d %d\n", i, ans);
            return 0;
        }
    }
    printf("-1 -1\n");
    return 0;
}