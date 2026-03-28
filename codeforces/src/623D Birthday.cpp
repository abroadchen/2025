//
// Created by Psy.C on 2026/3/27.
//
/**
n 表示输入数据的个数
p[M] 存储概率值（转换为小数形式）
g 存储当前所有概率的乘积
dp[M] 存储动态规划状态

读入n个概率值（以百分比形式）
将百分比转换为小数（除以100）
计算初始状态下所有概率的乘积
初始化dp数组，每个位置设置为对应概率值

选择最优索引x：

通过比较公式 (1-dp[x])*p[x]*dp[j] < (1-dp[j])*p[j]*dp[x] 来选择最优的索引
这个比较实际上是在比较增加哪个dp[j]能带来最大的边际效益
计算新的乘积：

k = (dp[x] + (1-dp[x])*p[x])*g/dp[x]
更新dp[x]的值：dp[x] += (1-dp[x])*p[x]
这相当于将dp[x]增加其未达到1的部分乘以p[x]
累加期望值：

ans += i*(k-g) 更新总期望值
g = k 更新当前乘积值


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 105;
int n;
double p[M], g = 1, dp[M];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i]; p[i] /= 100; g *= p[i];
        dp[i] = p[i];
    }
    double ans = n*g;
    for (int i = n+1; i < N; ++i) {
        int x = 0;
        for (int j = 0; j < n; ++j)
            if ((1-dp[x])*p[x]*dp[j] < (1-dp[j])*p[j]*dp[x])
                x = j;
        double k = (dp[x] + (1-dp[x])*p[x])*g/dp[x];
        dp[x] += (1-dp[x])*p[x];
        ans += i*(k-g);
        g = k;
    }
    printf("%.10lf\n", ans);
    return 0;
}