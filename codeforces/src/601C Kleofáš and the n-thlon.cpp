//
// Created by Psy.C on 2026/3/21.
//
/**
n, m: 骰子数量和面数
c[N]: 每个骰子的面数
s: 所有骰子面数之和
l, r: 区间边界
pre, now: 滚动数组索引，now=1, pre=0
d: 概率系数 1/(m-1)
f[2][N*M]: DP状态数组
sum[N*M]: 前缀和数组
ans: 最终答案
f[0][0]=1，表示0个骰子得到0的概率为1
时间复杂度：O(n²m²)，空间复杂度：O(nm)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105, M = 1005;
int n, m, c[N], s, l, r, pre, now = 1;
double d, f[2][N*M], sum[N*M], ans;
int main() {
    fast;
    cin >> n >> m; d = 1./(m-1);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i]; s += c[i];
    }
    f[0][0] = sum[0] = 1;
    for (int i = 1; i <= n; ++i) {//遍历第i个骰子
        for (int j = i; j <= i*m; ++j) {//遍历可能的和值
            l = max(i-1, j-m), r = min((i-1)*m, j-1);//计算有效区间
            f[now][j] = d * sum[r];//从前面状态转移
            if (l) f[now][j] -= d * sum[l-1];//减去超出范围的部分
            if (l <= j - c[i] && j - c[i] <= r)
                f[now][j] -= d * f[pre][j-c[i]];//排除无效情况
        }
        for (int j = 1; j <= i*m; ++j)
            sum[j] = sum[j-1] + f[now][j];//更新前缀和
        swap(now, pre);//交换滚动数组索引
    }
    for (int j = n; j < s; ++j) ans += f[pre][j];//累加概率
    printf("%.16lf", ans*(m-1)+1);
    return 0;
}