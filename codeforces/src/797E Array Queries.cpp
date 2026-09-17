//
// Created by Psy.C on 2026/9/17.
//
/**
N = 100005，M = 325：这接近 √N ≈ 316，用于根号分治
a[i]：从位置 i 出发可以向右跳 a[i] 格（即下一步到 i + a[i]）。
dp[i][j]：当步长固定为 j 时，从位置 i 跳到越界（> n）所需的总步数。

读入 n 和 a[1..n]。dp 清零
M 是阈值（约 325）。当查询的步长 y ≤ M 时，用预处理好的 dp 直接回答。
dp[i][j]：步长为 j 时，从位置 i 开始，跳到最后（越界）要多少步。
这里的"跳法"不是单纯的 i → i+a[i]，而是：
i
→
a
[
i
]
i
+
a
[
i
]
→
+j
i
+
a
[
i
]
+
j
i
a[i]
​
 i+a[i]
+j
​
 i+a[i]+j。

关键：这个 DP 的跳法是"双步"——每轮先跳 a[i]（到 i+a[i]），再额外加 j。让我核对递推公式：

若 i + a[i] + j > n（下一个"落点" i+a[i]+j 越界了）→ 那只需要 1 步就结束（跳完这次就到界外）。
否则 → 等于从下一个位置 i+a[i]+j 继续、步数 +1：dp[i][j] = dp[i+a[i]+j][j] + 1。
所以 dp[i][j] 实际统计的是：以 j 为"惩罚系数/附加步长"时的跳跃步数
每个查询给位置 x 和"参数" y。
当 y 较小（y ≤ M-5）‍：直接用预处理好的 dp[x][y] 回答，O(1)。
当 y 较大（y > M-5）‍：因为 y 大，每步跳跃 p += a[p]+y 移动距离大，总步数最多 n/y ≈ n/M ≈ 316 步，直接暴力循环模拟，复杂度 O(n/y) ≤ O(√n)，可接受。
这就是经典的分块/根号分治：小参数用 DP 表 O(1) 查，大参数用暴力 O(√n) 模拟，使整体均摊可接受
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 325;

int a[N], dp[N][M];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(dp, 0, sizeof(dp));
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= M; ++j) {
            if (i + a[i] + j > n) dp[i][j] = 1;
            else dp[i][j] = dp[i+a[i]+j][j]+1;
        }
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        if (y <= M-5) cout << dp[x][y] << '\n';
        else {
            int ans = 0;
            for (int p = x; p <= n; p += a[p]+y) ans++;
            cout << ans << '\n';
        }
    }
    return 0;
}