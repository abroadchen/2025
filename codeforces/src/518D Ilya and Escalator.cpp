//
// Created by Psy.C on 2026/3/1.
//
/**
n：状态数或位置数
m：操作次数或轮数
p：概率值
f[N]：动态规划数组
ans：最终答案

执行m轮状态转移
f[0] += f[1]*p：将f[1]的一部分概率转移到f[0]
对于每个位置j：
f[j] = f[j]*(1-p) + f[j+1]*p
这是一个概率转移方程：
保持在当前位置的概率：f[j] * (1-p)
从下一个位置转移过来的概率：f[j+1] * p

计算加权和作为期望值
f[i]是状态i的概率
(n-i)是状态i的权重（可能表示距离或得分）


外层循环（时间维度）
i：表示第几轮操作/时间步
总共进行m轮状态转移
每轮都代表一次完整的概率转移过程
内层循环（空间维度）
j：表示位置/状态
更新所有位置的概率分布
f[j] = f[j]*(1-p) + f[j+1]*p 表示：
f[j]*(1-p)：留在原位置的概率
f[j+1]*p：从下一个位置转移过来的概率

随机游走问题：

从位置n开始
每次有概率p向左移动，概率(1-p)留在原地
或者相反，有概率p向右移动
更准确地说：

f[j] 表示最终到达某个目标状态的概率
初始时在位置n，有100%概率在该位置
每轮操作后，位置j的"影响力"会向左传播

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3+2;
int n, m;
double p, f[N], ans;
int main() {
    fast;
    cin >> n >> p >> m; f[n] = 1;
    for (int i = 1; i <= m; ++i) {
        f[0] += f[1]*p;
        for (int j = 1; j <= n; ++j)
            f[j] = f[j]*(1-p) + f[j+1]*p;
    }
    for (int i = 0; i <= n; ++i)
        ans += f[i]*(n-i);
    printf("%.8lf", ans);
    return 0;
}