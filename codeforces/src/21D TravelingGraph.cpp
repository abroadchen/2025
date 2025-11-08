//
// Created by Psy.C on 2025/9/18.
//
/*
*maxn = 15: 最大节点数
n, m: 节点数和边数
u, v, w: 边的两个端点和权重
ans: 所有边权重的总和
f[maxn][maxn]: 存储节点间最短距离的邻接矩阵
d[maxn]: 每个节点的度数（连接的边数）
dp[1 << maxn]: 状态压缩DP数组，dp[mask]表示处理某些奇度节点的最小额外代价
 *
 *
 *
 *状态转移：对于当前状态k，选择两个未处理的奇度节点i和j，通过最短路径连接它们
 *
 *
*k < 1<<n: 遍历所有可能的状态（2^n种）
existed检查当前状态是否包含奇度节点
如果不包含奇度节点，说明已经配对完成，代价为0
否则，选择两个未在当前状态中的奇度节点i,j，将它们配对
dp[k|(1<<i)|(1<<j)]表示新状态（添加了节点i和j）
通过最短路径f[i][j]连接这两个节点
 *
 *
 *
 *时间复杂度：O(2^n × n^2)，空间复杂度：O(2^n)
 *
 *
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

static const int maxn = 15;
int n, m, u, v, w, ans;
int f[maxn][maxn], d[maxn];
int dp[1 << maxn];

int main() {

    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i < n; ++i) f[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;//将输入的节点编号转换为数组索引
        f[u][v] = f[v][u] = min(f[u][v], w);
        d[u]++; d[v]++;
        ans += w;
    }

    for (int k = 0; k < n; ++k)//使用Floyd算法计算所有节点对之间的最短距离
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i < n; ++i) {
        if (d[i] && f[0][i] == 0x3f3f3f3f) {//如果某个节点有边连接但与节点0不连通，则图不连通，输出-1
            puts("-1");
            return 0;
        }
    }

    for (int k = 0; k < 1<<n; ++k) {
        bool existed = false;
        for (int i = 0; i < n; ++i)
            if ((d[i] & 1) && (k >> i & 1)) existed = true;
        if (!existed) dp[k] = 0;

        for (int i = 0; i < n; ++i)
            if ((d[i] & 1) && !(k >> i & 1))
                for (int j = i + 1; j < n; ++j)
                    if ((d[j] & 1) && !(k >> j & 1))
                        dp[k|(1<<i)|(1<<j)] = min(dp[k|(1<<i)|(1<<j)], dp[k]+f[i][j]);
    }

    if (dp[(1<<n)-1] >= 0x3f3f3f3f) puts("-1");
    else printf("%d\n", ans + dp[(1<<n)-1]);
    return 0;
}