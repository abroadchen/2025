//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
v = min(a[i]-(a[i]&1), lst)

lst 是上一格结余下来的可继续用的额度。
a[i]-(a[i]&1)：把当前值抹成偶数（去掉奇偶位），保证和结余配对合理 —— 偶数可直接拆分。
取两者较小 = 本格最多能用的结余数。
a[i] -= v; lst -= v;：把这一格按结余扣掉，同时减少剩余额度。

ans += a[i]/3; a[i] %= 3;：每 3 个单位计 1 个"完整组"（答案 += 整除商），剩下不足 3 的余数（0/1/2）留着。

lst += a[i]*2; ans += a[i];：

把本格余数 a[i] 乘 2 结余给下一格（lst += 2*a[i]）——这是"余数翻倍往下传"的机制。
同时 ans += a[i]：这些余数也直接累加进答案（因为后续会用/结转）
ans 目前包含所有计数（含结余部分），而 lst 是最后还未消费、可能溢出的多余结余。
每种多结余 2 个单位，最终只能折算回 1 组，所以要 减去 lst/2（按 2:1 把没用的结余回退）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e6+5;

int n, a[N];
inline void solve() {
    cin >> n;
    rep(i,n) cin >> a[i];
    int ans = 0, lst = 0;
    rep(i,n) {
        int v = min(a[i]-(a[i]&1), lst);
        a[i] -= v, lst -= v;
        ans += a[i]/3, a[i] %= 3;
        lst += a[i]*2, ans += a[i];
    }
    cout << ans - lst/2 << '\n';
}

signed main() {
    fast;
    solve();
    return 0;
}