//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
总共有 n 个数，m 次操作：每次操作要么删掉一个数，要么给某个数 +k。
最优策略必然是：
删掉最小的一些数（因为删小的不亏平均值）；
把剩下的 k 全部加给最大的那个数（最大化平均值时 +k 应集中给最大值）
情况 0：一个都不删
剩余 n 个数，全保留。
可用加的次数是 m，但每个数最多只能被 +k 一次（题目通常约定"每个数至多加 k 一次"），所以能加的总量是 min(m, n)*k，即代码里 min(k*n, m)（k*n = n 个数每个 +k，m 是操作次数上限）
枚举"删 i 个"
i = 删除的个数，从 1 到 n-1（不能删光，至少留 1 个）。
if (i > m) break：删 i 个需要 i 次操作，剩下用于加的操作是 m-i，一旦删除所需超过总操作 m 就停止枚举。
sum -= a[i-1]：因前面 sort(a, a+n) 升序，a[i-1] 恰是当前剩余元素中的最小者。删第 i 个（本轮最小）时从总和中减掉它。因为 i 从 1 递增，a[0]....a[i-1] 依次被减掉，正好是删掉前 i 个最小数。
剩余个数 = n-i。
可加的量 = min(k*(n-i), m-i)：剩余 n-i 个数、每个最多 +k（总量 k*(n-i)），且加的操作次数不超过 m-i。
平均值 =（剩余和 + 可加量）/ 剩余个数，与当前最优 res 取 max
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define db double
using namespace std;

constexpr int N = 2e5+5;

ll sum, n, k, m;
int a[N];
db solve() {
    db res = (db)(sum+min(k*n,m))/n;
    rep(i,n-1) {
        if (i > m) break;
        sum -= a[i-1];
        res = max(res, (db)(sum+min(k*(n-i),m-i))/(n-i));
    }
    return res;
}

int main() {
    fast;
    cin >> n >> k >> m;
    for (int i = 0; i < n; ++i) { cin >> a[i]; sum += a[i]; }
    sort(a, a+n);
    printf("%lf\n", solve());
    return 0;
}