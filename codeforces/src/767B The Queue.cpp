//
// Created by Psy.C on 2026/9/7.
//
/**
n, m, k, q：四个输入参数。
x[N]：q 个给定位置。
dp[N]：DP 到达时间数组
有 q 个"给定关键位置" x[i]，
k 表示每次移动能前进的距离/每次可用能量，或"补一次能量的间隔"，
需要找一个"服务站/加油站/充电站"放置位置 ans，使得到达目标时间尽量小
tim = inf：记录"最优（最早到达目标）对应的时间"。
ans = n：答案位置初始化为 n

dp[i] 表示"在不额外放置服务站的前提下，走到位置 x[i] 时累计的某种余额/延迟"。

k 是"每经过一段能获得的额度"（比如能量/时间补偿），
- (x[i]-x[i-1]) 是"从上一个关键点到这个关键点消耗的量"，
与 0 取 max（不能为负）。
初始 dp[0] = max(0, n - x[0])——从起点 n 走到第一个关键点 x[0] 的距离。
对每一对相邻关键点 (x[i-1], x[i])（不同点时），尝试在 x[i]-1 处放一个服务站，计算放后到达 x[i] 的时间 tmp = dp[i-1] + k - (x[i]-x[i-1])（clamped 到 0）。
若这个 tmp 更小，且位置合法（x[i]-1 < m，且 x[i]-1+tmp < m 不会越界），则记录更优解 ans = x[i]-1
情况 1：尝试把服务站放在 x[0]-1（第一个关键点的前一格），对应"从起点 n 出发，先到第一个关键点之前放站再前进"的路径，时间 n - x[0] + 1，同样做合法性检查。
情况 2：tmp = x[q-1] + dp[q-1] + k——从最后一个关键点再走 k 到终点附近的位置；若剩余的 m - tmp >= k 说明终点前还能再走 k 的距离，就把答案改为 tmp（放得更远

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = 1e13;

ll n, m, k, q, x[N], dp[N];
int main() {
    fast;
    cin >> n >> m >> k >> q;
    for (int i = 0; i < q; ++i) cin >> x[i];
    ll tim = inf, ans = n;
    for (int i = 0; i < q; ++i) {
        if (i == 0) dp[i] = max(0ll, n-x[i]);
        else dp[i] = max(dp[i-1]+k-(x[i]-x[i-1]), 0ll);
        if (i && x[i] != x[i-1]) {
            ll tmp = max(0ll, dp[i-1]+k-(x[i]-x[i-1]));
            if (tmp < tim && x[i]-1 < m && x[i]-1+tmp < m) {
                tim = tmp; ans = x[i]-1;
            }
        }
    }
    if (q) {
        ll tmp = max(0ll, n-x[0]+1);
        if (tmp < tim && x[0]-1 < m && x[0]-1+tmp < m) {
            tim = tmp; ans = x[0]-1;
        }
        tmp = x[q-1]+dp[q-1]+k;
        if (m - tmp >= k) ans = tmp;
    }
    cout << ans << '\n';
    return 0;
}