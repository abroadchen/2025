//
// Created by Psy.C on 2025/9/20.
//
/*
*c[N][N]: 组合数表，c[i][j]表示C(i,j)
dp[N][N][N]: 动态规划状态数组
n, m: 输入参数，n表示总球数，m表示颜色数
a[N]: 存储每种颜色的球数上限
 *
*初始化组合数：c[i][0] = 1（任何数选0个都为1）
使用递推公式计算组合数：c[i][j] = c[i-1][j] + c[i-1][j-1]
这是基于组合数的帕斯卡三角形性质
 *
*初始化DP状态：dp[i][0][0] = 1
表示从前i种颜色中选0个球，且有0个球是最后一种颜色的方案数为1
 *
*三层循环遍历DP状态：
i: 当前考虑的颜色种类数（1到m）
j: 当前选取的球总数（1到n）
k: 最后一种颜色选取的球数（0到j）
计算区间范围：[l, r]表示第i种颜色选k个球时的数量范围
 *
*第一部分转移：
从前i-1种颜色中选j-p个球，其中最后一种颜色选w个球
从剩余的球中选p个第i种颜色的球
累加方案数
 *
*第二部分转移：
从前i-1种颜色中选j-p个球，其中最后一种颜色选k个球
从剩余的球中选p个第i种颜色的球（数量少于l）
累加方案数
 *
 *计算期望值：将每种情况下的球数乘以其对应的方案数并求和
 *将结果除以m，得到平均值
 *
 *
 */
#include <algorithm>
#include <cstdio>
#define N 110
#define rep(a,b,c) for(int a=b;a<=c;++a)
using namespace std;

double c[N][N]={0}, dp[N][N][N]={0};
int n, m, a[N];


int main() {
    scanf("%d%d", &n, &m);
    rep (i, 1, m) scanf("%d", a+i);
    rep (i, 0, n + m) c[i][0] = 1;

    rep (i, 1, n + m)
        rep (j, 1, i)
            c[i][j] = c[i-1][j] + c[i-1][j-1];

    rep (i, 0, m) dp[i][0][0] = 1;
    rep (i, 1, m)
        rep (j, 1, n)
            rep (k, 0, j) {
                int l = max(a[i] * (k - 1) + 1, 0), r = a[i] * k;
                rep (w, 0, k)
                    rep (p, l, min(r, j))
                        dp[i][j][k] += dp[i-1][j-p][w]*c[n-j+p][p];
                rep (p, 0, min(l - 1, j))
                    dp[i][j][k] += dp[i-1][j-p][k]*c[n-j+p][p];
            }

    double ans = 0;
    rep (i, 1, n) ans += dp[m][n][i] * i;
    rep (i, 1, n) ans /= (double)m;

    printf("%.10lf\n", ans);

    return 0;
}