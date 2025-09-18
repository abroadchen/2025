//
// Created by Psy.C on 2025/9/17.
//
/*
 *
 *如果j==k则跳过（相邻颜色不能相同）
 *
 *如果不是第一行，先递归打印前一行
 *
*对于每一行的每种颜色组合(j,k)
枚举前一行的颜色组合(p,q)
约束条件：相邻行相同位置的颜色不能相同(p!=j, q!=k)
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include <cstdio>
#include <cstring>
#include <utility>

#define maxn 500
#define maxc 26
#define inf 0x3f3f3f3f
using namespace std;


int n, m, dp[maxn + 5][maxc + 5][maxc + 5], cost[maxn + 5][maxc + 5][maxc + 5];
char color[maxn + 5][maxn + 5];
pair<int, int> pre[maxn + 5][maxc + 5][maxc + 5];

void Init() {
    memset(dp, 0x3f, sizeof(dp));
    memset(cost, 0x3f, sizeof(cost));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= maxc; ++j) {
            for (int k = 1; k <= maxc; ++k) {
                if (j == k) continue;
                cost[i][j][k] = 0;
                for (int p = 1; p <= m; p += 2) cost[i][j][k] += (color[i][p] != ('a' + j - 1));
                for (int p = 2; p <= m; p += 2) cost[i][j][k] += (color[i][p] != ('a' + k - 1));
            }
        }
    }
    for (int i = 1; i <= maxc; ++i)
        for (int j = 1; j <= maxc; ++j)
            dp[1][i][j] = cost[1][i][j];
}

void Print(int i, int color1, int color2) {
    if (i > 1) Print(i - 1, pre[i][color1][color2].first, pre[i][color1][color2].second);
    for (int i = 1; i <= m; ++i) {
        if (i & 1) putchar('a' + color1 - 1);
        else putchar('a' + color2 - 1);
    }
    putchar('\n');
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", color[i] + 1);
    Init();

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= maxc; ++j)
            for (int k = 1; k <= maxc; ++k)
                for (int p = 1; p <= maxc; ++p)
                    for (int q = 1; q <= maxc; ++q)
                        if (p != j && q != k)
                            if (dp[i][j][k] > dp[i - 1][p][q] + cost[i][j][k]) {
                                pre[i][j][k] = make_pair(p, q);
                                dp[i][j][k] = dp[i - 1][p][q] + cost[i][j][k];
                            }
    int ans = inf, ci, cj;
    for (int i = 1; i <= maxc; ++i)
        for (int j = 1; j <= maxc; ++j)
            if (ans > dp[n][i][j]) ans = dp[n][ci=i][cj=j];
    printf("%d\n", ans);
    Print(n, ci, cj);
    return 0;
}