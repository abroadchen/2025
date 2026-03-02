//
// Created by Psy.C on 2026/3/2.
//
/**
g[N]：记录每个位置的起始点
f[N]：动态规划数组，记录到达每个位置所需的最小段数
T：每次查询的目标值

将原数组复制一份到后面，形成长度为2n的数组
a[i]现在表示前i个元素的和
g[i] = i：每个位置的起始点初始化为自己
f[i] = 0：段数初始化为0

j = 1：滑动窗口的左端点
ans = inf：最小段数初始化为无穷大
主循环：for (int i = n+1; i <= 2*n; ++i)

从位置n+1开始处理（即原数组的循环扩展部分）
滑动窗口调整：while (j <= i && a[i] - a[j-1] > T) j++;

保证子数组和a[i] - a[j-1] ≤ T
移动左端点j直到满足条件
状态转移：

f[i] = f[j-1] + 1：到达i的最小段数 = 到达j-1的最小段数 + 1
g[i] = g[j-1]：记录起始位置
更新答案：if (i-g[i] >= n) ans = min(ans, f[i]);

如果覆盖范围≥n（跨越了完整的原数组）
更新最小段数

每次查询：O(n)
总时间复杂度：O(m×n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e6+1, inf = 0x7fffffff;
int n, m, g[N], f[N];
ll a[N], T;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i], a[i+n] = a[i];
    for (int i = 1; i <= 2*n; ++i) a[i] += a[i-1];
    while (m--) {
        for (int i = 1; i <= 2*n; ++i) g[i] = i, f[i] = 0;
        cin >> T;
        int j = 1, ans = inf;
        for (int i = n+1; i <= 2*n; ++i) {
            while (j <= i && a[i] - a[j-1] > T) j++;
            f[i] = f[j-1] + 1; g[i] = g[j-1];
            if (i-g[i] >= n)
                ans = min(ans, f[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}