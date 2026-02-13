//
// Created by Psy.C on 2026/2/13.
//
/**
n：数组总长度
m：滑动窗口大小
k：最多选择的窗口数量
g[M]：输入的原始数组
sum[N]：长度为m的连续子数组和
f[i][j]：前i个位置选择j个窗口的最大和

f[i][j]：考虑前i个位置，选择j个长度为m的不重叠窗口的最大和
初始：f[i][j] = f[i-1][j]（不选择以i结尾的窗口）
转移：如果i >= m，可以选择以i结尾的窗口：
f[i][j] = max(f[i][j], f[i-m][j-1] + sum[i])
即：当前最优 = max(不选当前窗口, 选当前窗口)

时间复杂度：O(n*k)
空间复杂度：O(n*k)

f[i-m][j-1]：覆盖范围是1到i-m
sum[i]：覆盖范围是i-m+1到i
两者刚好衔接，没有重叠也没有空隙
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 5005
#define M 1000005
using namespace std;

int n, m, k, g[M];
ll sum[N], f[N][N];

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> g[i];
        if (i <= m) sum[i] = sum[i - 1] + g[i];
        //从位置i-m+1到i的连续m个元素的和
        if (i > m) sum[i] = sum[i - 1] - g[i - m] + g[i];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j) {
            f[i][j] = f[i-1][j];
            if (i >= m && f[i-m][j-1] != -1)
                f[i][j] = max(f[i][j], f[i-m][j-1] + sum[i]);
        }
    cout << f[n][k] << '\n';//前n个位置选择k个窗口的最大和
    return 0;
}