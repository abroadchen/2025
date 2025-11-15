//
// Created by Psy.C on 2025/11/14.
//
/*
 *节点数 n、边数 m 和两个起始节点 a, b（转成从 0 开始编号）
 *如果起点等于终点，则输出概率分布：只有起点位置为 1，其余为 0
*建立邻接表形式的无向图 g[n]。
每条边连接两个顶点并双向添加到邻接表中
 *输入每个节点的停留概率 p[i]
 *
*初始化转移矩阵 T，其中 T[i][j] 表示从节点 i 转移到节点 j 的概率。
对于每一个节点 i：
自身保留概率 p[i]
其余 (1 - p[i]) 平均分配给其邻居节点
 *
*计算所有不同节点组合的数量 M = n*(n-1)
创建映射数组：
i2s: 线性索引 → 节点对 (u,v)
s2i: 节点对 (u,v) → 线性索引（若相同则不记录）
 *
 *初始化增广矩阵 A[M][M+n]，用于解线性方程组
*遍历每一对不同的节点 (u,v)：
设置当前行为单位阵元素 A[i][i] = 1
右侧列 A[i][M+k] 存储 T[u][k]*T[v][k]
遍历所有可能转移到的状态 (u2,v2)，更新矩阵元素
 *
*实现高斯-约旦消元法处理增广矩阵 A
找主元进行行交换
归一化主行
清除其他行对应列元素
 *
*查找初始状态 (a,b) 在线性索引下的编号 si
输出第 si 行后半部分的结果（即解得的概率分布）
 *
*以概率p[i]停留在当前节点i
以概率(1-p[i])移动到相邻节点，均匀随机选择
将(1-p[i])/度数分配给所有邻居
 *
对于所有可能的下一个状态(u2,v2)：
如果它们不同且有效，则从适当矩阵元素中减去转移概率乘积
这建立了方程：f(u,v) = Σ T[u][u2] * T[v][v2] * f(u2,v2) +
T[u][u2] * T[v][v2]（当u2=v2时）
 *
*fac = A[i][col]:
fac 是当前行 i 在主元列 col 的元素值
这是我们想要消除的系数
A[col][j]:
这是主元行在第 j 列的元素值
fac * A[col][j]:
这是主元行的每个元素乘以系数 fac
A[i][j] -= fac * A[col][j]:
从当前行 i 的第 j 个元素中减去 fac * A[col][j]
这相当于执行了行变换：Row[i] = Row[i] - fac * Row[col]
 *
*两个游走者从状态 (u,v) 出发
他们分别以概率 T[u][u2] 和 T[v][v2] 移动到新状态 (u2,v2)
如果 u2 ≠ v2，他们会继续移动，贡献 T[u][u2] * T[v][v2] * f(u2,v2) 到 f(u,v)
如果 u2 = v2，他们在此处相遇，贡献 T[u][u2] * T[v][v2] 到相遇概率
 *
*i 是当前方程的索引，对应状态 (u,v)
j 是变量索引，对应状态 (u2,v2) （其中 u2 ≠ v2）
T[u][u2] * T[v][v2] 是从状态 (u,v) 转移到状态 (u2,v2) 的联合概率
负号 来自将这些项移到方程左边时的符号变化
 *
 *
 *
 *
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#define rep(i,n) for(int i=0;i<(n);++i)
#define sz(x) ((int)(x).size())
using namespace std;
const double eps = 1e-9;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, a, b; cin >> n >> m >> a >> b; a--; b--;
    if (a == b) {
        rep(i,n) cout<<fixed<<setprecision(10)<<
            (i == a ? 1. : 0.)<<" "; return 0;
    }
    vector<vector<int>> g(n);
    rep(i,m) {
        int u, v; cin >> u >> v; u--; v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    vector<double> p(n);
    rep(i,n) cin >> p[i];
    vector<vector<double>> T(n, vector<double>(n, 0.));
    rep(i,n) {
        int deg = sz(g[i]); T[i][i] = p[i];
        for (int x : g[i]) T[i][x] += (1. - p[i]) / deg;
    }
    int M = n * n - n;//计算不同节点有序对的总数（可能的状态数）
    vector<pair<int,int>> i2s(M);
    vector<vector<int>> s2i(n, vector<int>(n, -1));
    int idx = 0;
    rep(u,n) rep(v,n) {//填充双向映射，将线性索引与不同节点的有序对关联
        if (u != v) {
            i2s[idx] = {u, v};
            s2i[u][v] = idx;
            idx++;
        }
    }
    vector<vector<double>> A(M, vector<double>(M + n, 0.));//M个方程和M+n列
    rep(i,M) {
        int u = i2s[i].first, v = i2s[i].second;
        A[i][i] = 1.;//对于每个状态(u,v)，初始化对角线元素为1
        rep(k,n) A[i][M+k] = T[u][k] * T[v][k];//设置右侧值，表示立即相遇的概率
        rep(u2,n) {
            if (T[u][u2] == 0.) continue;
            rep(v2,n) {
                if (T[v][v2] == 0.) continue;
                if (u2 == v2) continue;
                int j = s2i[u2][v2];
                if (j == -1) continue;
                A[i][j] -= T[u][u2] * T[v][v2];
            }
        }
    }
    rep(col,M) {
        int pivotr = col;
        for (int r = col + 1; r < M; ++r) {//找到当前列中绝对值最大的行
            if (fabs(A[r][col]) > fabs(A[pivotr][col])) pivotr = r;
        }
        if (fabs(A[pivotr][col]) < eps) continue;//如果主元元素接近零则跳过
        swap(A[col], A[pivotr]);//将当前行与主元行交换
        double pivotv = A[col][col];
        for (int j = col; j < M + n; ++j) A[col][j] /= pivotv;//标准化主元行，使主元元素变为1
        rep(i,M) {//使用主元行消除所有其他行中的列条目
            if (i == col) continue;
            double fac = A[i][col];
            for (int j = col; j < M + n; ++j) A[i][j] -= fac * A[col][j];
        }
    }
    int si = s2i[a][b];//找到初始状态(a,b)的线性索引
    rep(k,n) cout<<fixed<<setprecision(10)<<A[si][M+k]<<" ";//输出解决方案值（已求解矩阵行的最后n列）
    return 0;
}