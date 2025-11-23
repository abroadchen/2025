//
// Created by Psy.C on 2025/11/22.
//
/*
 *sum:前缀和数组, a:当前组的价值数组, dp:动态规划数组
 *读取组数n和背包容量m
 *
 *从前k个物品中选取 + 从后面选取(j-k)个物品
 *sum[k]: 前k个物品的和
 *sum[num] - sum[num + k - j]: 后(j-k)个物品的和
 *
 *从后往前更新避免重复使用
 *dp[j-k]: 使用j-k容量时的最大价值
 *a[k]: 从第i组选取k个物品的价值
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 105, M = 10005;
int sum[N], a[N], dp[M];

int main() {
    int n, m; scanf("%d %d", &n, &m);
    for (int i = 1, num; i <= n; ++i) {//处理每一组物品
        scanf("%d", &num);//读取第i组物品的数量
        for (int j = 1, t; j <= num; ++j) {//读取第i组每个物品的价值，并计算前缀和
            scanf("%d", &t);//读取第j个物品的价值
            sum[j] = sum[j - 1] + t;
        }
        memset(a, 0, sizeof(a));
        for (int j = 0; j <= num; ++j) {//计算从第i组中选取j个物品能获得的最大价值
            for (int k = 0; k <= j; ++k)//k表示从前面选取的物品数量
                a[j] = max(a[j],
                    sum[k] + sum[num] - sum[num + k - j]);
        }
        printf("\n");
        for (int j = m; j >= 1; --j) {//当前背包容量
            for (int k = 1; k <= min(j, num); ++k)//从第i组选取k个物品
                dp[j] = max(dp[j], dp[j - k] + a[k]);
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}