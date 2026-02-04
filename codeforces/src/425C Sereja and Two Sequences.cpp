//
// Created by Psy.C on 2026/2/4.
//
/**
* n：天数
m：物品总数
s：总预算
e：每天的消耗
a[i]：第i天要收集的物品类型
*g[t]：存储类型为t的物品出现的时间列表
g[t]中的元素按时间顺序递增排列（因为按时间顺序输入）
 *dp[j]：收集j个物品所需的最早时间
 *
 *遍历每一天
 *遍历可能的收集数量（从大到小避免重复计算）
 *在类型为a[i]的物品中找到时间大于dp[j]的第一个位置
 *找到最早可用的a[i]类型物品
 *如果没有可用物品，跳过
 *更新收集j+1个物品的最早时间
 *
*检查是否在预算内
dp[j+1]：收集j+1个物品的最早时间
i：当前天数
e*(j+1)：收集j+1个物品的总消耗
ans = max(ans, j + 1);：更新最大收集数量
 *
*外层循环：O(n)
内层循环：O(s/e)
upper_bound：O(log m)
总体：O(n × (s/e) × log m)
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    int n, m, s, e; cin >> n >> m >> s >> e;
    int a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> g[N];
    for (int i = 1, t; i <= m; ++i) {
        cin >> t;
        g[t].push_back(i);
    }
    int dp[N], ans = 0; memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
    for (int i = 1; i <= n; ++i) for (int j = s/e; j >= 0; --j) {
        auto t = ranges::upper_bound(g[a[i]], dp[j]);
        if (t == g[a[i]].end()) continue;
        dp[j+1] = min(dp[j+1], *t);
        if (dp[j+1] + i + e*(j+1) <= s) ans = max(ans, j + 1);
    }
    cout << ans << '\n';
    return 0;
}