//
// Created by Psy.C on 2026/10/7.
//
/***
f：需要完成的总任务量。
T：总时间上限。
t0：普通模式每单位任务的耗时。
两类"加速方案"，每种有三参数：a[i]（每组能"生产/处理"多少单位）、t[i]（每组对应的单位耗时）、p[i]（每组的价格/花费）。
t[0] 应比 t0 快（更省时），t[1] 是另一种方案
枚举用方案 0 的组数 i（受 i*t[0]<=T 时间限制）。
rf = f - i：剩余还需用"方案1 + 普通"覆盖的任务量（假设每 i 组覆盖 i 单位，即方案0每组覆盖 1 单位任务）。
rt = T - i*t[0]：剩余时间
如果 t[1] >= t0（方案1不更快），那方案1没有意义（直接用普通模式），只用方案0 + 普通。
若总耗时（方案0 + 普通覆盖剩余 rf）不超 T，则更新花费（方案0 的组数向上取整乘单价）
这里目标是：在剩余 rf 单位任务中，用 x 单位走方案1（快，耗时 t[1]），剩余 rf-x 单位走普通（耗时 t0）。要求 x*t[1] + (rf-x)*t0 <= rt。
因为 t[1] < t0，左端项越小总耗时越小，所以 x 越大越好，但还要满足时间约束。这个表达式关于 x 单调（x 增大时用快方案多、耗时减少），所以 x*t[1]+(rf-x)*t0 随 x 增大而单调递减——找到满足 <= rt 的最大 x 即可。
用 35 次二分在 [l,r]=[0,rf] 里逼近满足条件的 x，最后得到 r（倾向于给最大可行 x）
i % a[0] 与 r % a[1]：校验组数能整除（方案0 每组处理 a[0] 个、方案1 每组处理 a[1] 个，组数必须是倍数，否则剩下零头没被覆盖 → 无意义跳过）。
最终校验该分配不超时间。
花费 = 方案0 组数（i 向上取整到 a[0] 的倍数）单价 + 方案1 组数（r 向上取整到 a[1] 倍数）单价，取最小
若 ans 仍为 inf（没有可行方案）输出 -1，否则输出最小花费
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr ll inf = 1e18;
ll f, T, t0, a[2], t[2], p[2];
int main() {
    fast;
    cin >> f >> T >> t0;
    for (int i = 0; i < 2; ++i) cin >> a[i] >> t[i] >> p[i];
    ll ans = inf;
    for (int i = 0; i*t[0] <= T; ++i) {
        int rf = f - i, rt = T - i*t[0];
        int l = 0, r = rf;
        if (t[1] >= t0) {
            if (i*t[0] + rf*t0 <= T)
                ans = min(ans, (i+a[0]-1)/a[0]*p[0]);
            continue;
        }
        for (int j = 0; j < 35; ++j) {
            int mid = (l+r)>>1;
            if (mid*t[1]+(rf-mid)*t0 <= rt) r = mid;
            else l = mid;
        }
        if (i%a[0] && r%a[1]) continue;
        if (r*t[1]+(rf-r)*t0 > rt) continue;
        ll cost = (i+a[0]-1)/a[0]*p[0]+(r+a[1]-1)/a[1]*p[1];
        ans = min(ans, cost);
    }
    cout << (ans == inf ? -1 : ans) << '\n';
    return 0;
}