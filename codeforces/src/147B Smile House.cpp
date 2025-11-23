//
// Created by Psy.C on 2025/11/21.
//
/*
*dp[s][i][j]表示从节点i走2^s步到节点j的最大权值和
dp[0][i][j]存储原始边的权值
通过倍增递推计算所有dp[s][i][j]
 *
 *
*预处理：O(n³ log n)
单次查询：O(n³ log n)
总体：O(n³ log² n)
 *
 *从节点i到节点j的最大权值路径 = max(已有路径, 从i到k的路径 + 从k到j的路径)
*普通矩阵乘法：C[i][j] = Σ(A[i][k] × B[k][j])
这里是"max-plus"半环：C[i][j] = max(A[i][k] + B[k][j])
 *
*ans[0][N][N]：一个缓冲区
ans[1][N][N]：另一个缓冲区
 *
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long double ld;
const int N = 305, M = 20, inf = 0x3f3f3f3f;
int n, m, t, dp[M][N][N], ans[2][N][N];

void maxx(int& a, const int& b) { a = max(a, b); }

void init() {
    t = (int)floor(log2((ld)n));//用于倍增
    for (int s = 0; s <= t; ++s) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) dp[s][i][j] = -inf;
            dp[s][i][i] = 0;//自己到自己的距离为0
        }
    }
}

void clr(int x) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) ans[x][i][j] = -inf;
        ans[x][i][i] = 0;
    }
}

bool ok(int x) {//检查是否存在长度为x的环
    int z = 0; clr(z);
    for (int s = 0; s <= t; ++s) {
        if (((x >> s) & 1) == 0) continue;//x的第s位是0
        z ^= 1; clr(z);
        for (int k = 1; k <= n; ++k) {//矩阵乘法：计算走2^s步后的最大距离
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j)
                    maxx(ans[z][i][j],//当前结果数组
                        ans[z^1][i][k] + dp[s][k][j]);//上一轮结果数组
            }
        }
    }
    for (int i = 1; i <= n; ++i) if (ans[z][i][i] > 0) {//对角线元素大于0
        return true;//存在正环
    }
    return false;
}

int main() {
    while (~scanf("%d %d", &n, &m)) {
        init();
        for (int i = 1, u, v, a, b; i <= m; ++i) {
            scanf("%d %d %d %d", &u, &v, &a, &b);
            dp[0][u][v] = a, dp[0][v][u] = b;//有向边u->v权值a，v->u权值b
        }
        for (int s = 1; s <= t; ++s) {
            for (int k = 1; k <= n; ++k) {
                for (int i = 1; i <= n; ++i) {
                    if (dp[s-1][i][k] == -inf) continue;
                    for (int j = 1; j <= n; ++j)
                        maxx(dp[s][i][j],
                            dp[s-1][i][k]+dp[s-1][k][j]);
                }
            }
        }
        int l = 2, r = n + 1, mid;//二分搜索最小的环长度
        while (l <= r) {
            mid = (l + r) >> 1;
            if (ok(mid)) r = mid - 1;//存在长度为mid的环，尝试更小值
            else l = mid + 1;//不存在长度为mid的环，尝试更大值
        }
        if (l >= n + 1) l = 0;//说明不存在环
        printf("%d\n", l);
    }
    return 0;
}