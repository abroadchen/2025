//
// Created by Psy.C on 2026/10/15.
//
/**
读入 n 和每个 a[i]，同时把 ans 初始化为 -Σa[i]。
之后只要再把 Σf[i] 加进 ans，就得到 Σ(f[i]-a[i])（总增量
从最右往左处理。
f[i] 至少是 a[i]（不能低于原值）。
同时受右边邻居约束：f[i] ≥ f[i+1] - 1 —— 即左边元素最多比右边低 1（因为从左到右每步最多 +1，反过来右边比左边最多高 1，也就是左边不能比右边小超过 1）。
于是 f[i] = max(a[i], f[i+1]-1) 保证在只考虑右侧约束时，每个位置都能取到满足"非递减 + 每步+1限速"的最小可行下界
注意：这一步之后 f[i] 已经满足"从右向左"的连续性要求，但还没处理"从左向右"的单调下限（f[i] 不能小于左边的 f[i-1]）
从左往右扫描，做前缀单调修正：f[i] = max(f[i], f[i-1])，强制 f 非递减（每个位置至少等于左边）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5;

ll n, a[N], ans, f[N];
int main() {
    fast;
    cin >> n;
    for (ll i = 1; i <= n; ++i) { cin >> a[i]; ans -= a[i]; }
    for (ll i = n; i >= 1; --i) f[i] = max(a[i], f[i+1]-1);
    for (ll i = 1; i <= n; ++i) {
        f[i] = max(f[i], f[i-1]);
        ans += f[i];
    }
    cout << ans << '\n';
    return 0;
}