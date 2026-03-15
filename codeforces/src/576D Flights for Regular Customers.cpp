//
// Created by Psy.C on 2026/3/15.
//
/**
起点u、终点v、权重d
使用bitset优化的邻接矩阵
a[i][j] = 1 表示从节点i到节点j可达
构造函数初始化所有位置为0

如果x.a[i][j]=1，则ret.a[i] |= y.a[j]
相当于布尔矩阵乘法，表示路径的连接关系
|= y.a[j] 表示将y中第j行的所有连接关系传递给结果矩阵的第i行
初始化单位矩阵A，A.a[i][i] = 1表示每个节点到自身可达

遍历每条边
构建矩阵B，包含权重小于当前边的所有边的连接关系
计算权重差值
使用二进制快速幂算法
A = A * B^y，表示在当前权重下更新可达性
初始化距离矩阵
设置已处理边的距离为1
运行Floyd-Warshall算法计算最短路径
检查A.a[1][i]，看是否存在从节点1到达节点i的路径
如果可达，则更新答案：当前边权重 + 从i到n的最短距离

O(m * n³ * log(max_weight))，其中m是边数，n是节点数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 152, inf = 0x3f3f3f3f;

struct node {
    int u, v, d;
    bool operator<(const node &o) const {
        return d < o.d;
    }
} e[N];

int n;
struct mat {
    bitset<N> a[N];
    mat() {
        for (int i = 1; i <= n; ++i) a[i].reset();
    }
    friend mat operator*(const mat &x, const mat &y) {
        mat ret;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (x.a[i][j]) ret.a[i] |= y.a[j];
        return ret;
    }
} A;

int m, dis[N][N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> e[i].u >> e[i].v >> e[i].d;
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; ++i) A.a[i][i] = 1;
    int ans = inf;
    for (int x = 1; x <= m; ++x) {
        mat B;
        for (int i = 1; i < x; ++i) B.a[e[i].u][e[i].v] = 1;
        int y = e[x].d - e[x-1].d;
        while (y) {
            if (y&1) A = A * B;
            B = B * B;
            y >>= 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) dis[i][j] = inf;
            dis[i][i] = 0;
        }
        for (int i = 1; i <= x; ++i) dis[e[i].u][e[i].v] = 1;
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
        for (int i = 1; i <= n; ++i)
            if (A.a[1][i]) ans = min(ans, e[x].d+dis[i][n]);
    }
    if (ans < inf) cout << ans << '\n';
    else cout << "Impossible\n";
    return 0;
}