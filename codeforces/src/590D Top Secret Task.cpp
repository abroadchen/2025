//
// Created by Psy.C on 2026/3/18.
//
/**
n: 元素个数
K: 选择的元素个数
s: 某种限制参数
a[N]: 输入数组
f[i][j]: 使用前i个元素选择j个的最小代价
g[i][j]: 临时数组，用于转移

外层循环处理第i个元素
memset(g[0], 0, sizeof g[0]): 重置临时数组
三层循环：
j: 选择的元素个数
k: 某种代价指标
g[j][k] = f[j][k]: 不选择第i个元素的情况
if (k >= i - j): 如果可以选择第i个元素
g[j][k] = min(g[j][k], f[j-1][k-(i-j)] + a[i]): 选择第i个元素
将临时结果从g转移到f
mn = min(s, n*(n-1)/2): 计算最大可能的代价（最多n*(n-1)/2个逆序对）
遍历所有可能的代价k，找出选择K个元素的最小代价
算法时间复杂度约为O(n³)，空间复杂度约为O(n³)，适用于小规模数据的组合优化问题
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 155, inf = 1e18;
int n, K, s, a[N], f[N][N*N], g[N][N*N];
signed main() {
    fast;
    cin >> n >> K >> s;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(f, 0x3f, sizeof f); memset(g, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        memset(g[0], 0, sizeof g[0]);
        for (int j = 1; j <= i; ++j)
            for (int k = 0; k <= i*j; ++k) {
                g[j][k] = f[j][k];
                if (k >= i - j)
                    g[j][k] = min(g[j][k], f[j-1][k-(i-j)] + a[i]);
            }
        for (int j = 1; j <= i; ++j)
            for (int k = 0; k <= i*j; ++k)
                f[j][k] = g[j][k];
    }
    int mn = min(s, n*(n-1)/2), ans = inf;
    for (int k = 0; k <= mn; ++k) ans = min(ans, f[K][k]);
    cout << ans;
    return 0;
}