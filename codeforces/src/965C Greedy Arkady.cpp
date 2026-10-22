//
// Created by Psy.C on 2026/10/21.
//
/**
i 从 0 到 d-1 枚举。这里的逻辑是在考虑"能取多少天"：当取款 i+1 天时（i=0 即取 1 天，i=1 取 2 天……），每次允许取的上限推导为 n / (i*k + 1)。
推导思路（典型题面）：每天取 x，手续费 k，开销为 每天x·k……总之通过平衡方程得到每天可取 n/(i*k+1)，这样 i+1 天恰好能清空/最大化。
if (x == 0) break;：若算出的 x 已为 0（天数太多取不到任何东西），直接终止循环，后面天数更不可能有正收益。
if (x > m) x = m;：每天取款有上限 m，取 min(x, m)。
ans = max(ans, x*(i+1));：这 i+1 天的总收益为 x*(i+1)，更新最优答案
n/m：每天取上限 m 时能取的天数（整除）。
n/m/k：再除以 k，得到"最大化每天都取满 m"所需的天数估计。
if (n/m % k != 0) cnt += 1;：若不整除则向上取整（多算一天）。
if (cnt > d) cnt = d;：天数不能超过 d，钳制。
ans = max(ans, cnt*m);：这种情况下每天取满 m、共 cnt 天的总收益 cnt*m，再与第一段结果取最大。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, m, d, ans;
int main() {
    fast;
    cin >> n >> k >> m >> d;
    for (ll i = 0; i < d; i++) {
        ll x = n/(i*k+1);
        if (x == 0) break;
        if (x > m) x = m;
        ans = max(ans, x*(i+1));
    }
    ll cnt = n/m/k;
    if (n/m%k != 0) cnt += 1;
    if (cnt > d) cnt = d;
    ans = max(ans, cnt*m);
    cout << ans << '\n';
    return 0;
}