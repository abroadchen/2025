//
// Created by Psy.C on 2026/4/18.
//
/**
d: 总距离
k: 车辆耐久度（可连续行驶距离）
a: 开车单位距离成本
b: 步行单位距离成本
t: 更换车辆所需时间/成本
ans: 最终的最小成本
分支1：开车成本优于更换车辆成本
k*a: 连续开车k距离的成本
k*a + t: 开车k距离+更换车辆的总成本
k*b: 步行k距离的成本
如果开车+换车比步行k距离便宜，则优先开车
情况1.1：总距离能被k整除
d/k: 需要开车的轮次数
d/k*(k*a+t): 开车k距离+换车的总成本（最后一次不用换车）
-t: 减去最后一次多余的换车成本
情况1.2：总距离不能被k整除
d >= k: 总距离超过k
d/k*(k*a+t)-t: 完整k段的开车+换车成本
min(d%k*b, t+d%k*a): 剩余距离的最优选择（步行 vs 开车+换车）
d < k: 总距离小于k，直接开车

分支2：步行比开车+换车更经济
先开车min(d, k)距离（最多k距离）
剩余距离全部步行
ans = min(d, k)*a: 前段开车成本
d = d - min(d, k): 更新剩余距离
ans += d*b: 后段步行成本
O(1): 直接计算，无需循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll d, k, a, b, t, ans;
int main() {
    fast;
    cin >> d >> k >> a >> b >> t;
    if (k*a + t <= k*b) {
        if (d%k == 0) ans = d/k*(k*a+t)-t;
        else {
            if (d >= k) {
                ans = d/k*(k*a+t)-t;
                ans += min(d%k*b, t+d%k*a);
            } else ans = d*a;
        }
    } else {
        ans = min(d, k)*a;
        d = d - min(d, k);
        ans += d*b;
    }
    cout << ans << '\n';
    return 0;
}