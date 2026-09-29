//
// Created by Psy.C on 2026/9/29.
//
/**
对落在区间 [l, r]（即某个 i 的倍数 j 之前的 i 个数）里的每个数，它都要被加到 r（下一个倍数 j）‍。
增加量 d = r - value。
用操作Y的代价是 d * y。
用操作X的代价是 x（一次性，不管 d 多大）。
所以：当 d*y > x（即增加值太大、乘 y 不划算）时用 X 划算；当 d*y ≤ x 时用 Y 划算。
分界点 d > x/y 用 X。即 value < r - x/y 用 X。
t = r - ceil(x/y) 就是这个分界值。区间 [l, t] 内的数（value 较小，需增加量大于 x/y）用 X；区间 (t, r] 内的数用 Y。
用前缀和加速：

cnt 记录数量前缀和，sum 记录数值总和前缀和。
区间 [l,t] 用 X 的代价 = x * (区间内数的个数)。
区间 (t,r] 用 Y 的代价 = y * Σ(r - value) = y * (个数*r - 数值和)。
遍历所有 i 作为目标模数，取最小总代价 res，更新 ans。

mx==1 特判：所有数都是 1，直接代价 = n*min(x,y)（因为把 1 变掉…实际是操作任一数一次）。

把所有数变成 i 的倍数，只需考虑 i ∈ [2, mx]（i 若 > mx 则 1 不能被整除、无意义；i=1 全部都能整除，代价为 0 但题目/本题枚举从 2 开始）
cnt[v] = 值为 v 的个数；sum[v] = 值为 v 的和。前缀和到 2*mx，用于快速求任意区间内的个数与总和
外层枚举目标模数 i，目标是所有数都变成 i 的倍数。
内层枚举 i 的每个倍数 j（j = i, 2i, 3i, ...），负责处理"要变成 j"的那些数。
落在区间 [l, r] = [j-i+1, j] 的数，离它最近的 i 的倍数是 j，所以这些数都要被加到 j（增加值 d = j - value）。
两种操作的选择（对每个数）：

用 Y（一次减 1，花 y/单位）代价 = d * y
用 X（一次性操作）代价 = x
取较优者：当 d*y > x 即 d > x/y 时用 X 划算；否则用 Y 划算。
分界值 t = j - ceil(x/y)：value ≤ t 的数（增加量 ≥ ceil(x/y)）用 X；value > t 的数用 Y
前缀和加速
[l,t] 内 K 个数 -> K 次 X
(t,r] 内每个数补到 r，总增量 = 个数*r - 数值和
所有数都是 1 时，只需让它们变成 i=2（或其他），每个数只需一次操作（X 或 Y 各一次且 min），共 n 次 × min(x,y)。
内层对每个倍数段做 O(1) 查询，总区间 Σ_{i=2}^{mx} (mx/i) = O(mx · H_{mx}) ≈ O(mx log mx)，非常高效
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e6+5;
constexpr ll inf = 9e18;
int a[N], cnt[N], mx;
ll sum[N], res, ans(inf);
int main() {
    fast;
    int n, x, y; cin >> n >> x >> y;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; ++cnt[a[i]];
        sum[a[i]] += 1ll*a[i];
    }
    mx = *max_element(a+1, a+n+1);
    if (mx == 1) {
        cout << 1ll*n*1ll*min(x,y) << '\n';
        return 0;
    }
    for (int i = 2; i <= mx*2; ++i) {
        cnt[i] += cnt[i-1];
        sum[i] += sum[i-1];
    }
    for (int i = 2; i <= mx; ++i) {
        res = 0;
        for (int j = i; j <= mx+i; j += i) {
            int r = j, l = r-i+1, t = r-(int)(ceil((double)x/(double)y)+0.5);
            if (t >= l) res += 1ll*x*1ll*(cnt[t]-cnt[l-1]);
            else t = l-1;
            res += 1ll*y*(1ll*(cnt[r]-cnt[t])*1ll*r-(sum[r]-sum[t]));
        }
        ans = min(ans, res);
    }
    cout << ans << '\n';
    return 0;
}