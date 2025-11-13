//
// Created by Psy.C on 2025/11/13.
//
/*
*n：节点数
m：边数
in[N]：每个节点的入度节点（前驱）
ot[N]：每个节点的出度节点（后继）
otc[N]：边的权重/成本
r[N][3]：存储结果的二维数组
cnt：结果计数器
x[N]：访问标记数组
 *
*定义深度优先搜索函数dfs，参数u为当前节点：
标记节点u已访问
获取节点u的后继节点v
如果v为0（无后继），返回{无穷大, u}
递归调用dfs处理后继节点v
返回：当前边权重与后续路径结果的较小值
 *
*读入m条边的信息：
x：起点
y：终点
z：边的权重
建立图结构：in[y]=x（y的前驱是x），ot[x]=y（x的后继是y），otc[x]=z（x出发的边权重为z）
 *
*遍历所有节点：
如果节点i没有前驱（in[i]==0）但有后继（ot[i]!=0），说明是起点
记录起点到r[cnt][0]
从该起点开始DFS搜索
如果DFS返回无效结果则跳过
记录终点和最小权重
增加计数器
*输出路径数量
输出每条路径的信息：起点、终点、最小权重
 */
#include <algorithm>
#include <cstdio>
using namespace std;

typedef pair<int, int> ii;
const int N = 1010, inf = 1e9;
int n, m,
in[N], ot[N], otc[N],
r[N][3], cnt,
x[N];


ii dfs(int u) {
    x[u] = 1;
    int v = ot[u];
    if (v == 0) return {inf, u};
    ii w = dfs(v);
    return min(make_pair(otc[u], w.second), w);
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0, x, y, z; i < m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        in[y] = x; ot[x] = y; otc[x] = z;
    }
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0 && ot[i] != 0) {
            r[cnt][0] = i;
            ii d = dfs(i);
            if (d.second == 0) continue;
            r[cnt][1] = d.second;
            r[cnt][2] = d.first;
            ++cnt;
        }
    }
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i)
        printf("%d %d %d\n", r[i][0], r[i][1], r[i][2]);
    return 0;
}