//
// Created by Psy.C on 2026/9/26.
//
/**
点的数量上限为
2555
2555
x[i], y[i]：第
i
i 个点的坐标
dis[i][j]：第
i
i 个点与第
j
j 个点的欧氏距离
所有点围成一个环（模
n
n），pre 是前一个点，nxt 是后一个点
dp[i][j][k]：当前已覆盖的区间为
[
i
,
j
]
[i,j]（环上的连续区间），当前在区间的左端点（
k
=
0
k=0，即 now=i）或右端点（
k
=
1
k=1，即 now=j）时，继续走完剩余部分能获得的最大长度
转移只有两种选择（类似"游说/绕圈"问题）：
向左扩展：走到 pre(i)，即 dfs(_p, j, 0) + dis[_p][now]
向右扩展：走到 nxt(j)，即 dfs(i, _n, 1) + dis[now][_n]
每次决策都是取更大值（max），所以这是求最长总路径长度
终止条件 _p == j：左右边界已经相遇，说明整个环都走完了，返回 0
从每个点
i
i 单独出发（区间
[
i
,
i
]
[i,i]），取所有起点的最大值
输出保留 12 位小数

有两个"指针"（当前区间的左右端），初始在同一点，每一步可以任选一端向环外扩展一格，每扩展一格累加对应的欧氏距离，直到两个指针在环上相遇，求能获得的最大总距离。
由于在凸多边形（点在环上）上，dis[now][_n] 等都对应边或弦的长度
状态复杂度
O
(
n
2
)
O(n
2
 )，转移
O
(
1
)
O(1)，总复杂度
O
(
n
2
)
O(n
2
 )
时间复杂度约
O
(
n
2
)
O(n
2
 )，空间
O
(
n
2
)
O(n
2
 )
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2555;
int n;
inline int pre(int x) { return (x+n-1)%n; }
inline int nxt(int x) { return (x+1)%n; }

double dis[N][N], x[N], y[N];
inline void get(int i, int j) {
    dis[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}

double dp[N][N][2];
double dfs(int i, int j, int k) {
    if (dp[i][j][k] >= 0) return dp[i][j][k];
    int now = !k ? i : j, _p = pre(i), _n = nxt(j);
    if (_p == j) return 0;
    return dp[i][j][k] = max(dfs(_p, j, 0)+dis[_p][now],
        dfs(i, _n, 1)+dis[now][_n]);
}

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) get(i, j);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < 2; ++k) dp[i][j][k] = -1;
    double res = 0;
    for (int i = 0; i < n; ++i)
        res = max(res, dfs(i, i, 0));
    printf("%.12f\n", res);
    return 0;
}