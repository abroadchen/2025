//
// Created by Psy.C on 2025/12/2.
//
/*N=62（节点数上限），M=100005（操作数上限）
*n: 节点数量
m: 操作/图层数量
r: 查询数量
 *
*a[N][N][N]: 三维数组，a[op][i][j]表示第op层图中节点i到节点j的距离
q[M][3]: 查询数组，存储查询请求
mx: 最大查询距离
dp[N][N][N]: 动态规划数组，dp[i][j][k]表示从节点i到节点j经过最多k步的最短距离
 *
*读取m个图层的距离矩阵
对于每个图层k，读取n×n的距离矩阵
*读取r个查询请求，每个查询包含起点、终点和最大步数
同时记录最大的查询步数mx
 *限制最大步数不超过节点数n（因为超过n步没有意义）
 *
*对每个图层运行Floyd算法，计算所有点对之间的最短路径
这是经典的Floyd-Warshall算法的三维版本
 *
*初始化dp[i][j][0]：从节点i到节点j经过0步转换（即在同一图层内）的最短距离
取所有图层中的最小值
 *
*对于每个步数k（从1到mx）：
首先继承前一状态：dp[i][j][k] = dp[i][j][k-1]
然后尝试通过中间节点l进行优化：
dp[i][j][k] = min(dp[i][j][k], dp[i][l][k-1] + dp[l][j][0])
这表示从i到j经过k步转换的最短路径
 *
*
处理每个查询：
限制查询步数不超过mx
输出从起点到终点经过最多指定步数的最短距离
 *
 *
*Floyd预处理：O(m × n³)
DP状态转移：O(mx × n³)
查询处理：O(r)
总体：O(m × n³ + mx × n³)
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 62, M = 1e5+5;
int n, m, r;
int a[N][N][N], q[M][3], mx, dp[N][N][N];

int main() {
    fast;
    cin >> n >> m >> r;
    rep(k,m) rep(i,n) rep(j,n) cin >> a[k][i][j];
    rep(i,r) { cin >> q[i][0] >> q[i][1] >> q[i][2]; mx = max(mx, q[i][2]); }
    mx = min(mx, n);
    rep(op,m) rep(k,n) rep(i,n) rep(j,n) {
        a[op][i][j] = min(a[op][i][j], a[op][i][k] + a[op][k][j]);
    }
    memset(dp, 127, sizeof(dp));
    rep(op,m) rep(i,n) rep(j,n) dp[i][j][0] = min(dp[i][j][0], a[op][i][j]);
    rep(k,mx+1) {
        rep(i,n) rep(j,n) dp[i][j][k] = dp[i][j][k-1];
        rep(l,n) rep(i,n) rep(j,n) {
            dp[i][j][k] = min(dp[i][j][k], dp[i][l][k-1] + dp[l][j][0]);
        }
    }
    rep(i,r) {
        q[i][2] = min(q[i][2], mx);
        cout << dp[q[i][0]][q[i][1]][q[i][2]] << '\n';
    }
    return 0;
}