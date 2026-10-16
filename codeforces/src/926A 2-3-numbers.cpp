//
// Created by Psy.C on 2026/10/15.
//
/**
枚举所有 2^a · 3^b 这种"2、3 光滑数"（幂积），统计有多少个落在 [l, r] 之间
外层 i 枚举 2^k，内层 j 枚举 3^k。
对每个组合算 i*j，判断是否 ∈ [l, r]，是则 ans++。
两层循环次数都很少：2 的幂到 r ≤ 1e9 也就约 30 个（2^30 ≈ 1e9），3 的幂约 19 个，所以总枚举量很小，可以暴力双循环
因为 j 是严格递增的（每次 *=3），所以在固定 i 时，i*j 随 j 单调递增。

一旦发现 i*j > r，那么后面的 j（更大）必然 i*j 更大，全都 > r，可以直接 break 掉内层循环——这就是剪枝点，省去无效枚举。
但注意：i*j < l 时还不能跳，因为后面更大的 j 可能让它落入区间，所以用 if (i*j >= l) 才进入判断，< l 则继续涨 j
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll l, r; cin >> l >> r;
    ll ans = 0;
    for (ll i = 1; i <= r; i *= 2) {
        for (ll j = 1; j <= r; j *= 3) {
            if (i*j >= l) {
                if (i*j <= r) ans++;
                else break;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}