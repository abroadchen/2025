//
// Created by Psy.C on 2026/9/17.
//
/**
x[]：n 个服务需求点的位置（坐标）。
p[]：m 个可选建立的服务站，first=位置，second=该站容量（最多能服务几个需求点）。
dp[i][j]：使用前 i 个站点、服务前 j 个需求点的最小总成本。
cnt[]：单调队列优化用的辅助前缀数组。
q[]、sum[]：单调队列 + 容量前缀和
memset(dp, 0x3f)：初始化为很大的数（无穷大）。
需求点和站点都按位置排序——因为最优分配中站点按位置依次服务连续的一段需求点（决策单调性）。
sum[i]：前 i 个站点总容量。
若总容量 < n，无法服务所有需求点 → 输出 -1
边界：无论用几个站点，服务 0 个需求点成本都是 0

状态转移原理：让第 i 个站点服务一段连续的需求点 (k+1 ... j)（因为排序后连续分配最优），那么：

d
p
[
i
]
[
j
]
=
min
⁡
k
{
d
p
[
i
−
1
]
[
k
]
+
cost
(
第
i
站服务
k
+
1..
j
)
}
dp[i][j]=min
k
​
 {dp[i−1][k]+cost(第i站服务k+1..j)}

其中 cost = 每个被服务点的 |p[i].first - x[小标]| 之和。

cnt 数组的关键作用：cnt[j] = cnt[j-1] + |p[i].first - x[j]|，即"第 i 站从开头服务到 j 的累计距离"。那么服务 (k+1..j) 的成本 = cnt[j] - cnt[k]。

于是转移式变成：

d
p
[
i
]
[
j
]
=
min
⁡
k
{
d
p
[
i
−
1
]
[
k
]
−
c
n
t
[
k
]
}
+
c
n
t
[
j
]
dp[i][j]=min
k
​
 {dp[i−1][k]−cnt[k]}+cnt[j]

dp[i-1][k] - cnt[k] 这一项与 j 无关，只与 k 有关 → 这正是单调队列优化的用武之地：维护 dp[i-1][k] - cnt[k] 的最小值。
加上 cnt[j] 即得本状态。
两个 while 的作用：

while (l<=r && j - q[l] > p[i].second) l++; —— 容量约束：第 i 个站点最多服务 p[i].second 个点，所以决策点 k 满足 j - k <= second，即 k >= j - second。队首如果太靠后（j - q[l] > second）就弹出。
while (l<=r && dp[i-1][q[l]]-cnt[q[l]] > dp[i-1][j]-cnt[j]) l++;

计算 cnt[j]（第 i 站从 0 到 j 的累计距离）。
dp[i][j] 先继承"不使用第 i 站" = dp[i-1][j]。
移除容量超限的队首决策。
比较当前 j 与队首 q[l] 的"决策价值" dp[i-1][k]-cnt[k]：若当前 j 的价值更小（更优）则弹出队首 l++——这是单调队列里"若新决策优于队首则队首无望"的剔除。
但标准写法应对队尾 q[r] 做此判断。用 q[l] 且 l++ 等于直接抛弃队首，可能丢失有效决策。这里有简化/潜在 bug，但在很多题解版本里这样做也能过（因为 j 递增时决策价值 dp[i-1][j]-cnt[j] 单调，队首即最优）。
当前 j 入队 q[++r] = j。
用队首最优决策 q[l] 更新：dp[i][j] = min(dp[i][j], dp[i-1][q[l]]-cnt[q[l]]+cnt[j])。
输出用全部 m 个站点（在容量允许下）服务全部 n 个需求点的最小总成本。若无法满足（容量不足）已在前面输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e3+5;

int dp[N][N], x[N], sum[N], q[N], cnt[N];
ii p[N];
signed main() {
    fast;
    memset(dp, 0x3f, sizeof dp);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = 1; i <= m; ++i) cin >> p[i].first >> p[i].second;
    sort(x+1, x+n+1); sort(p+1, p+m+1);
    for (int i = 1; i <= m; ++i) sum[i] = sum[i-1] + p[i].second;
    if (sum[m] < n) { cout << -1; return 0; }
    for (int i = 0; i <= m; ++i) dp[i][0] = 0;
    for (int i = 1; i <= m; ++i) {
        int l = 0, r = 0; q[++r] = 0;
        for (int j = 1; j <= min(sum[i], n); ++j) {
            cnt[j] = cnt[j-1]+abs(p[i].first-x[j]);
            dp[i][j] = dp[i-1][j];
            while (l <= r && j - q[l] > p[i].second) l++;
            while (l <= r && dp[i-1][q[l]] - cnt[q[l]] > dp[i-1][j] - cnt[j]) l++;
            q[++r] = j;
            if (l <= r) dp[i][j] = min(dp[i][j], dp[i-1][q[l]]-cnt[q[l]]+cnt[j]);
        }
    }
    cout << dp[m][n];
    return 0;
}