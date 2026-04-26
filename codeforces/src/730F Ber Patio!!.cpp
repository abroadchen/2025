//
// Created by Psy.C on 2026/4/25.
//
/**
dp[2][M]：动态规划数组，使用滚动数组优化空间
fa[N][M]：记录路径，用于回溯方案
n：数组长度
a[N]：输入数组
m：某个限制值

o为滚动数组的索引，每次循环异或1切换
循环读取数组元素，计算可能的最大收益值x
清空当前行的dp值
遍历前一行的有效状态
w：当前状态下已花费的资源
h：当前可用的资源量
t：当前物品最多可以减少的数量（取可用资源和a[i]/2的最小值）
枚举当前物品减少的数量k
nw：新的花费值
nj：新的收益值
更新dp表和路径记录表
累加当前元素到总和

找到最优解和对应的收益值
从后往前回溯，构建最优方案
通过fa数组记录的信息重构路径
反转结果数组
输出最优解
输出每个元素的最终值（原值减去减少的量）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5007, M = 1e4+7, inf = 0x3f3f3f3f;

int dp[2][M], fa[N][M], n, a[N], m;
void get() {
    memset(dp, inf, sizeof dp);
    memset(fa, 0, sizeof fa); dp[0][0] = 0;
    int o = 1;
    for (int i = 1, sum = 0; i <= n; ++i, o^=1) {
        cin >> a[i];
        int x = (sum + a[i])/10;
        for (int j = 0; j <= x; ++j) dp[o][j] = inf;
        for (int j = 0; j <= x; ++j) if (dp[o^1][j] != inf) {
            int w = dp[o^1][j], h = m + j - (sum - w), t = min(h, a[i]/2);
            for (int k = 0; k <= t; ++k) {
                int nw = w + a[i] - k, nj = j + (a[i]-k)/10;
                if (dp[o][nj] > nw) {
                    dp[o][nj] = nw;
                    fa[i][nj] = a[i] - k;
                }
            }
        }
        sum += a[i];
    }
    int ans = inf, pos = 0;
    for (int i = 0; i < M; ++i)
        if (ans > dp[o^1][i]) {
            ans = dp[o^1][i];
            pos = i;
        }
    vector<int> res;
    for (int i = n; i >= 1; --i) {
        res.push_back(fa[i][pos]);
        pos -= fa[i][pos]/10;
    }
    ranges::reverse(res);
    cout << ans << '\n';
    for (int i = 0; i < n; ++i)
        cout << a[i+1] - res[i] << (i<n-1 ? ' ' : '\n');
}

int main() {
    while (cin >> n >> m) get();
    return 0;
}
